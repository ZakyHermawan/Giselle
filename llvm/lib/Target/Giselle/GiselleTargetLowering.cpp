//===----------------------------------------------------------------------===//
//
// Implements the interfaces that Giselle uses to lower LLVM code
// into a selection DAG.
//
//===----------------------------------------------------------------------===//

#include "GiselleTargetLowering.h"
#include "GiselleCallingConvention.h"
#include "GiselleSubtarget.h"

#include "MCTargetDesc/GiselleMCTargetDesc.h"

using namespace llvm;

#define DEBUG_TYPE "giselle-lowering"

GiselleTargetLowering::GiselleTargetLowering(const TargetMachine &TM,
                                             const GiselleSubtarget &STI)
    : TargetLowering(TM, STI), Subtarget(STI) {
  addRegisterClass(MVT::i32, &Giselle::GPR32RegClass);
  computeRegisterProperties(STI.getRegisterInfo());
}

// Performs prologue and epilogue register management for target,
// specifically handling the saving and restoring of the link register
void GiselleTargetLowering::finalizeLowering(MachineFunction &MF) const {
  // Prevent this method being called twice.
  if (MF.getProperties().hasProperty(
          MachineFunctionProperties::Property::Selected)) {
    return;
  }

  const TargetInstrInfo &TII = *Subtarget.getInstrInfo();
  MachineRegisterInfo &MRI = MF.getRegInfo();

  // A link register (LR) is a special-purpose register used by some
  // architectures to store the return address when a function call is made.
  Register SavedLR = MRI.createVirtualRegister(&Giselle::GPR32RegClass);
  Register LR = Giselle::X1;

  // Prologue: Save LR
  MachineBasicBlock &EntryMBB = MF.front();
  BuildMI(EntryMBB, EntryMBB.begin(), DebugLoc(), TII.get(TargetOpcode::COPY),
          SavedLR)
      .addReg(LR);
  EntryMBB.addLiveIn(LR);

  // Epilogue: Restore LR
  for (MachineBasicBlock &MaybeExitMBB : MF) {
    if (!MaybeExitMBB.succ_empty())
      continue;
    assert(MaybeExitMBB.getFirstTerminator() != MaybeExitMBB.end() &&
           "Exit block must have a terminator");
    assert(MaybeExitMBB.getFirstTerminator()->getOpcode() ==
               Giselle::RET_PSEUDO &&
           "Exit block must end with return");
    BuildMI(MaybeExitMBB, MaybeExitMBB.getFirstTerminator(), DebugLoc(),
            TII.get(TargetOpcode::COPY), LR)
        .addReg(SavedLR);
  }

  TargetLowering::finalizeLowering(MF);
}
