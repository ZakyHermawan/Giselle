//===---------------------- GiselleTargetInfo.cpp -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "GiselleTargetInfo.h"
#include "llvm/MC/TargetRegistry.h" // For RegisterTarget.
#include "llvm/Support/Compiler.h"  // For LLVM_EXTERNAL_VISIBILITY.
#include "llvm/TextAPI/Target.h"    // For Target class.

using namespace llvm;

Target &llvm::getTheGiselleTarget() {
  static Target TheGiselleTarget;
  return TheGiselleTarget;
}


extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGiselleTargetInfo() {
  RegisterTarget<Triple::giselle, /*HasJIT=*/false> X(
      getTheGiselleTarget(), /*Name=*/"giselle",
      /*Desc=*/"A simple LLVM Backend for RV32I",
      /*BackendName=*/"Giselle");
}
