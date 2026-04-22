#include "GiselleRegisterInfo.h"
#include "GiselleFrameLowering.h"
#include "MCTargetDesc/GiselleMCTargetDesc.h" // For the enum of the regclasses.
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "GiselleGenRegisterInfo.inc"


using namespace llvm;

GiselleRegisterInfo::GiselleRegisterInfo()
    : GiselleGenRegisterInfo(Giselle::X1, /*DwarfFlavour*/ 0, /*EHFlavour*/ 0,
                             /*PC*/ 0,  /*HwMode*/ 0) {}

const MCPhysReg *
GiselleRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
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
