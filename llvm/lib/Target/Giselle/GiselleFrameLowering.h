#pragma once

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class GiselleSubtarget;

class GiselleFrameLowering : public TargetFrameLowering {
protected:
  bool hasFPImpl(const MachineFunction &MF) const override;

public:
  explicit GiselleFrameLowering(const GiselleSubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(8), 0) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
};

} // namespace llvm
