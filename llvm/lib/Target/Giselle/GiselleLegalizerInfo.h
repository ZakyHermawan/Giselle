#pragma once

#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"

namespace llvm {

class GiselleSubtarget;
class MachineIRBuilder;
class GISelChangeObserver;

/// This class provides the information for the Giselle target legalizer for
/// GlobalISel.
class GiselleLegalizerInfo : public LegalizerInfo {
public:
  GiselleLegalizerInfo(const GiselleSubtarget &ST);
};

} // namespace llvm
