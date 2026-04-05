//===--- Giselle.h - Declare Giselle target feature support -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares Giselle TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/Support/Compiler.h" // For LLVM_LIBRARY_VISIBILITY.
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

// Giselle class
class LLVM_LIBRARY_VISIBILITY GiselleTargetInfo : public TargetInfo {
public:
  GiselleTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    resetDataLayout(
        // Little-endian.
        "e-"
        // ELF mangling
        "m:e-"
        // Pointers are 32-bit with 32-bit alignment
        "p:32:32-"
        // Native integer widths are 32 bits
        "n32-"
        // i64 are aligned on 64, i32 on 32, i16 on 16 and i1 on 8.
        "i64:64-i32:32-i16:16-i8:8-"
        // f32 aligned on 32-bit, f64 aligned on 64-bit
        "f32:32-f64:64-"
        // Aggregate alignment
        "a:0:32-"
        // 128-bit vectors are 128-bit aligned
        "v128:128");
  }

  /// Appends the target-specific \#define values for this
  /// target set to the specified buffer.
  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  /// Return information about target-specific builtins for
  /// the current primary target, and info about which builtins are non-portable
  /// across the current set of primary and secondary targets.
  llvm::SmallVector<Builtin::InfosShard> getTargetBuiltins() const override {
    return {};
  }

  /// Returns the kind of __builtin_va_list type that should be used
  /// with this target.
  BuiltinVaListKind getBuiltinVaListKind() const override {
    return CharPtrBuiltinVaList;
  }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    return false;
  }

  /// Returns a string of target-specific clobbers, in LLVM format.
  std::string_view getClobbers() const override { return ""; }

  ArrayRef<const char *> getGCCRegNames() const override { return {}; }
  ArrayRef<GCCRegAlias> getGCCRegAliases() const override { return {}; }
};
} // namespace targets
} // namespace clang
