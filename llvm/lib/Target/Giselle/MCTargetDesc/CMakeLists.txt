add_llvm_component_library(LLVMGiselleDesc
  GiselleMCTargetDesc.cpp

  LINK_COMPONENTS
  Support
  GiselleInfo
  MC

  ADD_TO_COMPONENT
  Giselle
)
