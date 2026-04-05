//===------------------- GiselleTargetMachine.h -----------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares the Giselle specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"

#include <optional>

namespace llvm {

class GiselleTargetMachine : public CodeGenTargetMachineImpl {
public:
  GiselleTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  ~GiselleTargetMachine() override;
};

} // namespace llvm
