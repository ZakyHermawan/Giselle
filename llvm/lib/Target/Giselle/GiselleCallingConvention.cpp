//===----------------------------------------------------------------------===//
//
// This file contains the table-generated and custom routines for the Giselle
// Calling Convention.
//
//===----------------------------------------------------------------------===//

#include "GiselleCallingConvention.h"
#include "MCTargetDesc/GiselleMCTargetDesc.h" // For Giselle reg enums.

using namespace llvm;

// TableGen provides definitions of the calling convention analysis entry
// points.
#include "GiselleGenCallingConv.inc"
