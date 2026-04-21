#pragma once

#include "llvm/CodeGen/TargetInstrInfo.h"
#include "GiselleRegisterInfo.h"
#include "GiselleSubtarget.h"

#define GET_INSTRINFO_HEADER
#include "GiselleGenInstrInfo.inc"

namespace llvm {

class GiselleInstrInfo : public GiselleGenInstrInfo {
  GiselleRegisterInfo RegInfo;

public:
  explicit GiselleInstrInfo(const GiselleSubtarget &STI);
};

} // namespace llvm
