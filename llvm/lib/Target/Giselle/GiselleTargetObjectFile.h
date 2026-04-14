#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {

/// This implementation is used for Giselle ELF targets (Linux in particular).
class GiselleElfTargetObjectFile : public TargetLoweringObjectFileELF {
public:
  GiselleElfTargetObjectFile();
};

/// This TLOF implementation is used for Darwin.
class GiselleMachoTargetObjectFile : public TargetLoweringObjectFileMachO {
public:
  GiselleMachoTargetObjectFile();
};

} // end namespace llvm
