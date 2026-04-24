//===----------------------------------------------------------------------===//
//
// Implements the Giselle specific subclass of TargetSubtarget.
//
//===----------------------------------------------------------------------===//

#include "Giselle.h"
#include "GiselleTargetMachine.h"
#include "GiselleSubtarget.h"
#include "GiselleCallLowering.h"
#include "GiselleLegalizerInfo.h"
#include "GiselleRegisterBankInfo.h"
#include "llvm/Target/TargetMachine.h"

using namespace llvm;

#define DEBUG_TYPE "giselle-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "GiselleGenSubtargetInfo.inc"

// Pin the vtable to this file.
void GiselleSubtarget::anchor() {}

GiselleSubtarget::GiselleSubtarget(const Triple &TT, StringRef CPU,
                                   StringRef FS, const TargetMachine &TM)
    : GiselleGenSubtargetInfo(TT, CPU, /*TuneCPU=*/"", FS),
      FrameLowering(*this),
      InstrInfo(*this),
      TLInfo(TM, *this) {
  CallLoweringInfo.reset(new GiselleCallLowering(*getTargetLowering()));
  Legalizer.reset(new GiselleLegalizerInfo(*this));
  RegBankInfo.reset(new GiselleRegisterBankInfo(*getRegisterInfo()));
  auto *RBI = new GiselleRegisterBankInfo(*getRegisterInfo());
  RegBankInfo.reset(RBI);
  InstrSelector.reset(Giselle::createInstructionSelector(
      *static_cast<const GiselleTargetMachine *>(&TM), *this, *RBI));
}
