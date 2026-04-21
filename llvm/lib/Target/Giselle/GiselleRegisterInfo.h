#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#define GET_INSTRINFO_OPERAND_ENUM
#include "GiselleGenRegisterInfo.inc"

namespace llvm {

struct GiselleRegisterInfo : public GiselleGenRegisterInfo {

  GiselleRegisterInfo();

  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  Register getFrameRegister(const MachineFunction &MF) const override;
};

} // namespace llvm
