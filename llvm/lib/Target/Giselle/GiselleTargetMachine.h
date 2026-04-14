//===----------------------------------------------------------------------===//
//
// This file declares the Giselle specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once
#include "GiselleSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"

#include <optional>
#include <memory>

namespace llvm {

class GiselleTargetMachine : public CodeGenTargetMachineImpl {
  mutable std::unique_ptr<GiselleSubtarget> SubtargetSingleton;
public:
  GiselleTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  ~GiselleTargetMachine() override;

  const GiselleSubtarget *getSubtargetImpl(const Function &F) const override;
};

} // namespace llvm
