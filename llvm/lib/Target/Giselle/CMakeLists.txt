add_llvm_component_group(Giselle)

add_llvm_target(GiselleCodeGen
  GiselleTargetMachine.cpp

  LINK_COMPONENTS
  GiselleDesc
  GiselleInfo

  Support

  ADD_TO_COMPONENT
  Giselle
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
