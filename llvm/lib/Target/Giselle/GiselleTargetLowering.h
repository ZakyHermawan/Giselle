#pragma once

#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class GiselleSubtarget;
class GiselleTargetMachine;

class GiselleTargetLowering : public TargetLowering {
public:
  explicit GiselleTargetLowering(const TargetMachine &TM,
                                 const GiselleSubtarget &STI);
};

} // namespace llvm
