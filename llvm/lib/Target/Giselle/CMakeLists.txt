add_llvm_component_group(Giselle)

set(LLVM_TARGET_DEFINITIONS Giselle.td)
tablegen(LLVM GiselleGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM GiselleGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM GiselleGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM GiselleGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM GiselleGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM GiselleGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM GiselleGenCallingConv.inc -gen-callingconv)
tablegen(LLVM GiselleGenRegisterBank.inc -gen-register-bank)
tablegen(LLVM GiselleGenGlobalISel.inc -gen-global-isel)
tablegen(LLVM GiselleGenMCPseudoLowering.inc -gen-pseudo-lowering)
add_public_tablegen_target(GiselleCommonTableGen)

add_llvm_target(GiselleCodeGen
  GiselleTargetObjectFile.cpp
  GiselleTargetLowering.cpp
  GiselleTargetMachine.cpp
  GiselleSubtarget.cpp
  GiselleFrameLowering.cpp
  GiselleRegisterInfo.cpp
  GiselleInstrInfo.cpp
  GiselleAsmPrinter.cpp
  GiselleCallingConvention.cpp
  GiselleCallLowering.cpp
  GiselleLegalizerInfo.cpp
  GiselleRegisterBankInfo.cpp
  GiselleInstructionSelector.cpp

  LINK_COMPONENTS
  GiselleDesc
  GiselleInfo

  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  GlobalISel
  MC
  Passes
  Support
  Target
  SelectionDAG
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  Giselle
)

add_subdirectory(AsmParser)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
