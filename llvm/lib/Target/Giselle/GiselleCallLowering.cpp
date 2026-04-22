#include "GiselleTargetLowering.h"
#include "GiselleCallLowering.h"

#include "llvm/CodeGen/GlobalISel/CallLowering.h"

#define DEBUG_TYPE "giselle-call-lowering"

using namespace llvm;

GiselleCallLowering::GiselleCallLowering(const GiselleTargetLowering &TLI)
    : CallLowering(&TLI) {}

namespace {

// Assign location to arguments that will be used for lowering formal arguments
// from the callee's perspective
struct GiselleIncomingValueAssigner : public CallLowering::IncomingValueAssigner {
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

} // namespace
