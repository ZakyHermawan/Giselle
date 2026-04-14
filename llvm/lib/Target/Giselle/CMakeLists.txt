add_llvm_component_group(Giselle)

set(LLVM_TARGET_DEFINITIONS Giselle.td)
tablegen(LLVM GiselleGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM GiselleGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM GiselleGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM GiselleGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM GiselleGenAsmMatcher.inc -gen-asm-matcher)
add_public_tablegen_target(GiselleCommonTableGen)

add_llvm_target(GiselleCodeGen
  GiselleTargetObjectFile.cpp
  GiselleTargetLowering.cpp
  GiselleTargetMachine.cpp
  GiselleSubtarget.cpp

  LINK_COMPONENTS
  GiselleDesc
  GiselleInfo

  Analysis
  CodeGen
  Core
  Support
  Target
  MC
  SelectionDAG
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  Giselle
)

add_subdirectory(AsmParser)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
