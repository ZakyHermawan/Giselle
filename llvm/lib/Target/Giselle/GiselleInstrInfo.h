#pragma once

#include "llvm/CodeGen/TargetInstrInfo.h"
#include "GiselleRegisterInfo.h"

#define GET_INSTRINFO_HEADER
#include "GiselleGenInstrInfo.inc"

namespace llvm {

class GiselleSubtarget;

class GiselleInstrInfo : public GiselleGenInstrInfo {
  GiselleRegisterInfo RegInfo;

public:
  explicit GiselleInstrInfo(const GiselleSubtarget &STI);
};

} // namespace llvm
