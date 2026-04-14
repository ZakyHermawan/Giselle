#pragma once

#define GET_REGINFO_ENUM
#include "GiselleGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "GiselleGenSubtargetInfo.inc"

#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "GiselleGenInstrInfo.inc"
