#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"

#include "GiselleTargetMachine.h"
#include "GiselleTargetObjectFile.h"
#include "TargetInfo/GiselleTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"     // For RegisterTargetMachine.
#include "llvm/Support/Compiler.h"      // For LLVM_EXTERNAL_VISIBILITY.

#include <memory>

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeGiselleTarget() {
  // Register the target so that external tools can instantiate it.
  RegisterTargetMachine<GiselleTargetMachine> X(getTheGiselleTarget());
}

static std::unique_ptr<TargetLoweringObjectFile> createTLOF(const Triple &TT) {
  if (TT.isOSBinFormatELF())
    return std::make_unique<GiselleElfTargetObjectFile>();
  if (TT.isOSBinFormatMachO())
    return std::make_unique<GiselleMachoTargetObjectFile>();
  // Other format not supported yet.
  return nullptr;
}

static const char *GiselleDataLayoutStr =
    "e-m:e-p:32:32:32-n32-i64:64:64-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32";

GiselleTargetMachine::GiselleTargetMachine(const Target &T, const Triple &TT,
                                           StringRef CPU, StringRef FS,
                                           const TargetOptions &Options,
                                           std::optional<Reloc::Model> RM,
                                           std::optional<CodeModel::Model> CM,
                                           CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, GiselleDataLayoutStr, TT, CPU, FS, Options,
                               // Use the simplest relocation by default.
                               RM ? *RM : Reloc::Static,
                               CM ? *CM : CodeModel::Small, OL),
      TLOF(createTLOF(getTargetTriple())) {
  initAsmInfo();
}

GiselleTargetMachine::~GiselleTargetMachine() = default;

const GiselleSubtarget *
GiselleTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  StringRef CPU = CPUAttr.isValid() ? CPUAttr.getValueAsString() : TargetCPU;
  StringRef FS = FSAttr.isValid() ? FSAttr.getValueAsString() : TargetFS;

  // Eventually, we'll want to hook up a different subtarget based on at the
  // target feature, target cpu, and tune cpu attached to F, but as of now,
  // the target doesn't support anything fancy so we just have one subtarget
  // for everything.
  if (!SubtargetSingleton)
    SubtargetSingleton =
        std::make_unique<GiselleSubtarget>(TargetTriple, CPU, FS, *this);
  return SubtargetSingleton.get();
}

TargetPassConfig *GiselleTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new GisellePassConfig(*this, PM);
}

bool GisellePassConfig::addIRTranslator() {
  addPass(new IRTranslator(getOptLevel()));
  return false;
}

bool GisellePassConfig::addLegalizeMachineIR() {
  addPass(new Legalizer());
  return false;
}

bool GisellePassConfig::addRegBankSelect() {
  addPass(new RegBankSelect());
  return false;
}

bool GisellePassConfig::addGlobalInstructionSelect() {
  addPass(new InstructionSelect(getOptLevel()));
  return false;
}
