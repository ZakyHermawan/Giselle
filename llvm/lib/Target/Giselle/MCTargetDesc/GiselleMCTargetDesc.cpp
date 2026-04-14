//===--------------------- GiselleMCTargetDesc.cpp ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides Giselle specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "GiselleMCAsmInfo.h"
#include "GiselleMCTargetDesc.h"
#include "TargetInfo/GiselleTargetInfo.h" // For getTheGiselleTarget.
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/TargetParser/Triple.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

#define GET_SUBTARGETINFO_MC_DESC
#include "GiselleGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "GiselleGenRegisterInfo.inc"

static MCSubtargetInfo *
createGiselleMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createGiselleMCSubtargetInfoImpl(TT, CPU, /*TuneCPU*/ CPU, FS);
}

static MCRegisterInfo *createGiselleMCRegisterInfo(const Triple &Triple) {
  MCRegisterInfo *X = new MCRegisterInfo();
  // The InitGiselleMCRegisterInfo function takes
  // two arguments: a pointer to the MCRegisterInfo instance to initialize and the enumerator value of
  // the register that was used as the return address for the backend (X1)
  InitGiselleMCRegisterInfo(X, Giselle::X1);
  return X;
}

static MCInstrInfo *createGiselleMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();

  return X;
}

static MCAsmInfo *createGiselleMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TheTriple,
                                       const MCTargetOptions &Options) {
  MCAsmInfo *MAI;
  if (TheTriple.isOSBinFormatMachO())
    MAI = new GiselleMCAsmInfoDarwin(TheTriple, Options);
  else if (TheTriple.isOSBinFormatELF())
    MAI = new GiselleMCAsmInfoELF(TheTriple, Options);
  else
    report_fatal_error("Binary format not supported");

  return MAI;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGiselleTargetMC() {
  Target &TheTarget = getTheGiselleTarget();

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTarget,
                                          createGiselleMCSubtargetInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTarget, createGiselleMCRegisterInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTarget, createGiselleMCInstrInfo);

  // Register the MC asm info.
  RegisterMCAsmInfoFn X(TheTarget, createGiselleMCAsmInfo);
}
