//===------------------- GiselleTargetMachine.cpp -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Giselle target spec.
//
//===----------------------------------------------------------------------===//

#include "GiselleTargetMachine.h"
#include "TargetInfo/GiselleTargetInfo.h" // For getTheGiselleTarget.
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "llvm/Support/Compiler.h"      // For LLVM_EXTERNAL_VISIBILITY.

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGiselleTarget() {
  // Register the target so that external tools can instantiate it.
  RegisterTargetMachine<GiselleTargetMachine> X(getTheGiselleTarget());
}

static const char *GiselleDataLayoutStr =
    "e-m:e-p:32:32-n32-i64:64-i32:32-i16:16-i8:8-f32:32-f64:64-a:0:32-v128:128";

GiselleTargetMachine::GiselleTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, GiselleDataLayoutStr, TT, CPU, FS, Options,
                               // Use the simplest relocation by default.
                               RM ? *RM : Reloc::Static,
                               CM ? *CM : CodeModel::Small, OL) {}

GiselleTargetMachine::~GiselleTargetMachine() = default;
