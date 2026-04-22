#pragma once
#include "GiselleTargetLowering.h"

#include "llvm/CodeGen/GlobalISel/CallLowering.h"

namespace llvm {

class GiselleTargetLowering;

class GiselleCallLowering : public CallLowering {
public:
  GiselleCallLowering(const GiselleTargetLowering &TLI);
};

} // namespace llvm
