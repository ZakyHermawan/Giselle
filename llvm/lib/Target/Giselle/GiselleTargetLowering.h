#pragma once

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class GiselleSubtarget;
class GiselleTargetMachine;

class GiselleTargetLowering : public TargetLowering {
  const GiselleSubtarget &Subtarget;

public:
  explicit GiselleTargetLowering(const TargetMachine &TM,
                                 const GiselleSubtarget &STI);

  /// Perform the last clean-ups after finishing instruction selection.
  void finalizeLowering(MachineFunction &MF) const override;
};

} // namespace llvm
