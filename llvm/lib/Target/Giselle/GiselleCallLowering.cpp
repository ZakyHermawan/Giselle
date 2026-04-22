#include "GiselleTargetLowering.h"
#include "MCTargetDesc/GiselleMCTargetDesc.h"
#include "GiselleCallLowering.h"

#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/GlobalISel/Utils.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"

#define DEBUG_TYPE "giselle-call-lowering"

using namespace llvm;

GiselleCallLowering::GiselleCallLowering(const GiselleTargetLowering &TLI)
    : CallLowering(&TLI) {}

// This handles the implementation during GlobalISel lowering. Even though
// TableGen promoted the value to an i32 container (LocVT), when it comes time
// to actually store that value to the stack, this function forces the compiler
// to only write 1 or 2 bytes (ValVT) rather than writing a full 4 bytes, which
// could overwrite adjacent stack memory
static LLT getStackValueStoreTypeHack(const CCValAssign &VA) {
  const MVT ValVT = VA.getValVT();
  if (ValVT == MVT::i8 || ValVT == MVT::i16)
    return LLT::scalar(ValVT.getSizeInBits());
  return LLT::scalar(VA.getLocVT().getSizeInBits());
}

namespace {

// Assign location to arguments that will be used for lowering formal arguments
// from the callee's perspective.
struct GiselleIncomingValueAssigner
    : public CallLowering::IncomingValueAssigner {
  GiselleIncomingValueAssigner(CCAssignFn *TheAssignFn, CCAssignFn *TheAssignFnVarArg,
                             const GiselleSubtarget &TheSubTarget, bool IsReturn)
      : IncomingValueAssigner(TheAssignFn, TheAssignFnVarArg) {}

  bool assignArg(unsigned ValNo, EVT OrigVT, MVT ValVT, MVT LocVT,
                 CCValAssign::LocInfo LocInfo,
                 const CallLowering::ArgInfo &Info, ISD::ArgFlagsTy Flags,
                 CCState &State) override {
    if (State.isVarArg() || Flags.isByVal())
      return false;

    bool Res = AssignFn(ValNo, ValVT, LocVT, LocInfo, Flags, Info.Ty, State);
    StackSize = State.getStackSize();
    return Res;
  }
};

// Assign location to arguments that will be used for the lowering of the
// arguments of the callee from the caller’s perspective.
struct GiselleOutgoingValueAssigner
    : public CallLowering::OutgoingValueAssigner {
  GiselleOutgoingValueAssigner(CCAssignFn *TheAssignFn, CCAssignFn *TheAssignFnVarArg)
      : OutgoingValueAssigner(TheAssignFn, TheAssignFnVarArg) {}

  bool assignArg(unsigned ValNo, EVT OrigVT, MVT ValVT, MVT LocVT,
                 CCValAssign::LocInfo LocInfo,
                 const CallLowering::ArgInfo &Info, ISD::ArgFlagsTy Flags,
                 CCState &State) override {
    if (State.isVarArg() || Flags.isByVal())
      return false;

    bool Res = AssignFn(ValNo, ValVT, LocVT, LocInfo, Flags, Info.Ty, State);
    StackSize = State.getStackSize();
    return Res;
  }
};

// Materialize the location determined by the GiselleIncomingValueAssigner.
// Generating the Machine IR (MIR) instructions — for values that are entering the current context.
// It is used in two specific scenarios:
// 1. Reading formal parameters at the entry point of the current function.
// 2. Reading the return value immediately after a CALL instruction returns from another function.
struct GiselleIncomingValueHandler : public CallLowering::IncomingValueHandler {
  GiselleIncomingValueHandler(MachineIRBuilder &MIRBuilder, MachineRegisterInfo &MRI)
      : IncomingValueHandler(MIRBuilder, MRI) {}

  /// Provides the memory address for an incoming argument passed on the stack.
  /// Creates a fixed stack object in the MachineFrameInfo and returns a FrameIndex.
  Register getStackAddress(uint64_t Size, int64_t Offset,
                           MachinePointerInfo &MPO,
                           ISD::ArgFlagsTy Flags) override {
    auto &MFI = MIRBuilder.getMF().getFrameInfo();

    int FI = MFI.CreateFixedObject(Size, Offset, /*IsImmutable=*/true);
    MPO = MachinePointerInfo::getFixedStack(MIRBuilder.getMF(), FI);
    auto AddrReg = MIRBuilder.buildFrameIndex(LLT::pointer(0, 32), FI);
    return AddrReg.getReg(0);
  }

  /// Determines the LLT (Low-Level Type) to use for the memory load of an
  /// incoming stack argument, preventing out-of-bounds stack reads for small types.
  LLT getStackValueStoreType(const DataLayout &DL, const CCValAssign &VA,
                             ISD::ArgFlagsTy Flags) const override {
    // For pointers, we just need to fixup the integer types reported in the
    // CCValAssign.
    if (Flags.isPointer())
      return CallLowering::ValueHandler::getStackValueStoreType(DL, VA, Flags);
    return getStackValueStoreTypeHack(VA);
  }

  /// Assigns an incoming argument passed in a physical register to a virtual register.
  /// Carefully marks the physical register as used (live-in/implicit-def) to preserve 
  /// valid control flow liveness and accurate debug information for calls/returns.
  void assignValueToReg(Register ValVReg, Register PhysReg,
                        const CCValAssign &VA) override {
    markPhysRegUsed(PhysReg);
    IncomingValueHandler::assignValueToReg(ValVReg, PhysReg, VA);
  }

  /// Emits a load instruction to read an incoming stack argument from the 
  /// given frame index address into the destination virtual register.
  void assignValueToAddress(Register ValVReg, Register Addr, LLT MemTy,
                            const MachinePointerInfo &MPO,
                            const CCValAssign &VA) override {
    MachineFunction &MF = MIRBuilder.getMF();

    LLT ValTy(VA.getValVT());
    LLT LocTy(VA.getLocVT());

    assert(ValTy == LocTy && "extensions not implemented");

    auto* MMO = MF.getMachineMemOperand(
        MPO, MachineMemOperand::MOLoad | MachineMemOperand::MOInvariant, MemTy,
        inferAlignFromPtrInfo(MF, MPO));
    assert(VA.getLocInfo() != CCValAssign::LocInfo::ZExt &&
           "zero extension not supported");
    assert(VA.getLocInfo() != CCValAssign::LocInfo::SExt &&
           "sign extension not supported");
    MIRBuilder.buildLoad(ValVReg, Addr, *MMO);
  }

  /// How the physical register gets marked varies between formal
  /// parameters (it's a basic-block live-in), and a call instruction
  /// (it's an implicit-def of the BL).
  virtual void markPhysRegUsed(MCRegister PhysReg) = 0;
};

/// Handler for incoming arguments at the entry of a function (formal parameters).
/// Marks the argument's physical registers as live-in to the entry basic block
/// and machine register info. This ensures the register allocator does not
/// overwrite the arguments and preserves accurate liveness for debug information.
struct GiselleFormalArgHandler : public GiselleIncomingValueHandler {
  GiselleFormalArgHandler(MachineIRBuilder &MIRBuilder, MachineRegisterInfo &MRI)
      : GiselleIncomingValueHandler(MIRBuilder, MRI) {}

  void markPhysRegUsed(MCRegister PhysReg) override {
    MIRBuilder.getMRI()->addLiveIn(PhysReg);
    MIRBuilder.getMBB().addLiveIn(PhysReg);
  }
};

/// Handler for return values incoming from a function call.
/// Marks the physical return registers as implicitly defined by the call
/// instruction. This maintains accurate control flow liveness tracking, prevents
/// incorrect dead-code elimination, and preserves valid debug data tracks.
struct CallReturnHandler : public GiselleIncomingValueHandler {
  CallReturnHandler(MachineIRBuilder &MIRBuilder, MachineRegisterInfo &MRI,
                    MachineInstrBuilder MIB)
      : GiselleIncomingValueHandler(MIRBuilder, MRI), MIB(MIB) {}

  void markPhysRegUsed(MCRegister PhysReg) override {
    MIB.addDef(PhysReg, RegState::Implicit);
  }

  MachineInstrBuilder MIB;
};

// Materialize the location determined by the GiselleOutgoingValueAssigner.
// Deals with values that are leaving the current context, meaning it is setting
// up arguments for a CALL instruction or a return value for a RET instruction.
struct GiselleOutgoingValueHandler : public CallLowering::OutgoingValueHandler {
  GiselleOutgoingValueHandler(MachineIRBuilder &MIRBuilder, MachineRegisterInfo &MRI,
                     MachineInstrBuilder MIB)
      : OutgoingValueHandler(MIRBuilder, MRI), MIB(MIB) {}

  /// Computes the stack address for an outgoing argument.
  /// It reads the current Stack Pointer (SP - X2) and adds the required offset.
  /// The SP virtual register is cached to avoid redundantly copying it for every stack argument.
  Register getStackAddress(uint64_t Size, int64_t Offset,
                           MachinePointerInfo &MPO,
                           ISD::ArgFlagsTy Flags) override {
    MachineFunction &MF = MIRBuilder.getMF();
    LLT P0 = LLT::pointer(0, 16);
    LLT S32 = LLT::scalar(32);

    if (!SPReg)
      SPReg = MIRBuilder.buildCopy(P0, Register(Giselle::X2)).getReg(0);

    auto OffsetReg = MIRBuilder.buildConstant(S32, Offset);
    auto AddrReg = MIRBuilder.buildPtrAdd(P0, SPReg, OffsetReg);

    MPO = MachinePointerInfo::getStack(MF, Offset);
    return AddrReg.getReg(0);
  }

  /// We need to fixup the reported store size for certain value types because
  /// we invert the interpretation of ValVT and LocVT in certain cases. This is
  /// for compatability with the DAG call lowering implementation, which we're
  /// currently building on top of.
  LLT getStackValueStoreType(const DataLayout &DL, const CCValAssign &VA,
                             ISD::ArgFlagsTy Flags) const override {
    if (Flags.isPointer())
      return CallLowering::ValueHandler::getStackValueStoreType(DL, VA, Flags);
    return LLT(VA.getLocVT());
  }

  /// Copies an outgoing value from a virtual register into the designated physical register.
  /// Crucially, attaches the physical register as an implicit use on outgoing
  /// control flow instructions (like calls or returns). This preserves caller liveness
  /// and ensures valid debug information across function boundaries.
  void assignValueToReg(Register ValVReg, Register PhysReg,
                        const CCValAssign &VA) override {
    // Attach the phys reg on the instruction itself (call or return
    // instruction).
    MIB.addUse(PhysReg, RegState::Implicit);
    assert(VA.getLocInfo() == CCValAssign::Full && "Extension not supported");
    // Assign the value to the phys reg.
    MIRBuilder.buildCopy(PhysReg, ValVReg);
  }

  /// Emits a store instruction to save an outgoing argument to the stack.
  /// Writes the data from the virtual register into the computed memory address.
  void assignValueToAddress(Register ValVReg, Register Addr, LLT MemTy,
                            const MachinePointerInfo &MPO,
                            const CCValAssign &VA) override {
    MachineFunction &MF = MIRBuilder.getMF();
    auto* MMO = MF.getMachineMemOperand(MPO, MachineMemOperand::MOStore, MemTy,
                                       inferAlignFromPtrInfo(MF, MPO));
    MIRBuilder.buildStore(ValVReg, Addr, *MMO);
  }

  // Builder that points on the outgoing instructions (call or return).
  MachineInstrBuilder MIB;

  // Cache the SP register vreg if we need it more than once in this call site.
  Register SPReg;
};

} // namespace
