add_llvm_component_library(LLVMGiselleInfo
  GiselleTargetInfo.cpp

  LINK_COMPONENTS
  Support

  ADD_TO_COMPONENT
  Giselle
)
