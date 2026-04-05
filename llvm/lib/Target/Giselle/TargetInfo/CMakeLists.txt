add_llvm_component_library(LLVMGiselleInfo
  GiselleTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  TextAPI

  ADD_TO_COMPONENT
  Giselle
)
