//===----------------------------------------------------------------------===//
//
// Implements the interfaces that Giselle uses to lower LLVM code
// into a selection DAG.
//
//===----------------------------------------------------------------------===//

#include "GiselleTargetLowering.h"
#include "GiselleSubtarget.h"

using namespace llvm;

#define DEBUG_TYPE "giselle-lowering"

GiselleTargetLowering::GiselleTargetLowering(const TargetMachine &TM, const GiselleSubtarget &STI)
    : TargetLowering(TM, STI) {}
