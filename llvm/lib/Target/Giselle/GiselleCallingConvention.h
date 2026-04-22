//===----------------------------------------------------------------------===//
//
// This file declares the entry points for Giselle calling convention analysis.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/CallingConvLower.h"

namespace llvm {

bool CC_Giselle_Common(unsigned ValNo, MVT ValVT, MVT LocVT,
                       CCValAssign::LocInfo LocInfo, ISD::ArgFlagsTy ArgFlags,
                       Type *OrigTy, CCState &State);
bool RetCC_Giselle_Common(unsigned ValNo, MVT ValVT, MVT LocVT,
                          CCValAssign::LocInfo LocInfo,
                          ISD::ArgFlagsTy ArgFlags, Type *OrigTy,
                          CCState &State);

} // namespace llvm
