include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_component_library(LLVMGiselleAsmParser
  GiselleAsmParser.cpp

  LINK_COMPONENTS
  GiselleDesc
  GiselleInfo
  CodeGenTypes
  MC
  MCParser
  Support
  TargetParser

  ADD_TO_COMPONENT
  Giselle
  )
