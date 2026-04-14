//===----------------------------------------------------------------------===//
//
// This file declares the Giselle specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#pragma once
#include "GiselleSubtarget.h"
#include "llvm/CodeGen/CodeGenTargetMachineImpl.h"
#include "llvm/Target/TargetLoweringObjectFile.h"

#include <optional>
#include <memory>

namespace llvm {

class GiselleTargetMachine : public CodeGenTargetMachineImpl {
  mutable std::unique_ptr<GiselleSubtarget> SubtargetSingleton;
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
public:
  GiselleTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
  ~GiselleTargetMachine() override;

  const GiselleSubtarget *getSubtargetImpl(const Function &F) const override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // namespace llvm
