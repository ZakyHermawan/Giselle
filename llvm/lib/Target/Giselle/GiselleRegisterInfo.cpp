#include "GiselleRegisterInfo.h"

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

using namespace llvm;

GiselleRegisterInfo::GiselleRegisterInfo() : GiselleGenRegisterInfo(Register()) {}

const MCPhysReg *
GiselleRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return nullptr;
}

BitVector GiselleRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}

bool GiselleRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  return false;
}

Register GiselleRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return Register();
}
