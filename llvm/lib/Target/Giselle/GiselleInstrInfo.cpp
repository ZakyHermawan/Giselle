#include "GiselleInstrInfo.h"
#include "GiselleSubtarget.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#include "GiselleGenInstrInfo.inc"

using namespace llvm;

GiselleInstrInfo::GiselleInstrInfo(const GiselleSubtarget &STI) : GiselleGenInstrInfo(STI, RegInfo), RegInfo() {}
