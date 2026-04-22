#include "GiselleTargetLowering.h"
#include "GiselleCallLowering.h"

#include "llvm/CodeGen/GlobalISel/CallLowering.h"

#define DEBUG_TYPE "giselle-call-lowering"

using namespace llvm;

GiselleCallLowering::GiselleCallLowering(const GiselleTargetLowering &TLI)
    : CallLowering(&TLI) {}
