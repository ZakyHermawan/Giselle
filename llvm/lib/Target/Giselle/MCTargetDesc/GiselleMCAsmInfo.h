//===----------------------------------------------------------------------===//
//
/// Declaration of the Giselle MCAsmInfos.
//
//===----------------------------------------------------------------------===//

#pragma once

#include "llvm/MC/MCAsmInfoDarwin.h"
#include "llvm/MC/MCAsmInfoELF.h"
namespace llvm {

class Triple;

class GiselleMCAsmInfoELF : public MCAsmInfoELF {
public:
  explicit GiselleMCAsmInfoELF(const Triple &TT, const MCTargetOptions &Options);
};

class GiselleMCAsmInfoDarwin : public MCAsmInfoDarwin {
public:
  explicit GiselleMCAsmInfoDarwin(const Triple &TT,
                                const MCTargetOptions &Options);
};

} // namespace llvm
