//===----------------------------------------------------------------------===//
//
// Implements the Giselle specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "GiselleSubtarget.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;
// Pin the vtable to this file.
void GiselleSubtarget::anchor() {}

GiselleSubtarget::GiselleSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                                   const TargetMachine &TM)
    : TargetSubtargetInfo(TT, CPU, /*TuneCPU=*/"", FS, /*PN=*/{}, /*PF=*/{},
                          /*PD=*/{},
                          /*WPR=*/nullptr,
                          /*WL=*/nullptr,
                          /*RA=*/nullptr, /*IS=*/nullptr,
                          /*OC=*/nullptr, /*FP=*/nullptr),
      TLInfo(TM, *this) {}
