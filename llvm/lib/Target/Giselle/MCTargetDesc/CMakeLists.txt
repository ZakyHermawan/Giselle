add_llvm_component_library(LLVMGiselleDesc
  GiselleMCAsmInfo.cpp
  GiselleMCTargetDesc.cpp
  GiselleInstPrinter.cpp

  LINK_COMPONENTS
  Support
  GiselleInfo
  MC

  ADD_TO_COMPONENT
  Giselle
)
