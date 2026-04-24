//===----------------------------------------------------------------------===//
/// \file
/// This file implements the targeting of the InstructionSelector class for
/// Giselle.
//===----------------------------------------------------------------------===//

#include "Giselle.h"
#include "GiselleInstrInfo.h"
#include "GiselleRegisterBankInfo.h"
#include "GiselleSubtarget.h"
#include "GiselleTargetMachine.h"
#include "llvm/CodeGen/GlobalISel/GIMatchTableExecutorImpl.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"

#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "giselle-gisel"

using namespace llvm;

namespace {

#define GET_GLOBALISEL_PREDICATE_BITSET
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATE_BITSET

class GiselleInstructionSelector : public InstructionSelector {
public:
  GiselleInstructionSelector(const GiselleTargetMachine &TM,
                             const GiselleSubtarget &STI,
                             const GiselleRegisterBankInfo &RBI);

  bool select(MachineInstr &I) override;
  static const char *getName() { return DEBUG_TYPE; }

private:
  /// tblgen generated 'select' implementation that is used as the initial
  /// selector for the patterns that do not require complex C++.
  bool selectImpl(MachineInstr &I, CodeGenCoverage &CoverageInfo) const;

  const GiselleInstrInfo &TII;
  const GiselleRegisterInfo &TRI;
  const GiselleRegisterBankInfo &RBI;

#define GET_GLOBALISEL_PREDICATES_DECL
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_DECL

#define GET_GLOBALISEL_TEMPORARIES_DECL
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_DECL
};

} // namespace

#define GET_GLOBALISEL_IMPL
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_IMPL

GiselleInstructionSelector::GiselleInstructionSelector(
    const GiselleTargetMachine &TM, const GiselleSubtarget &STI,
    const GiselleRegisterBankInfo &RBI)
    : TII(*STI.getInstrInfo()), TRI(*STI.getRegisterInfo()), RBI(RBI),
#define GET_GLOBALISEL_PREDICATES_INIT
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_INIT
#define GET_GLOBALISEL_TEMPORARIES_INIT
#include "GiselleGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_INIT
{
}

bool GiselleInstructionSelector::select(MachineInstr &I) {
  if (!isPreISelGenericOpcode(I.getOpcode())) {
    return true;
  }

  if (selectImpl(I, *CoverageInfo)) {
    return true;
  }

  return false;
}

namespace llvm {

namespace Giselle {

InstructionSelector *
createInstructionSelector(const GiselleTargetMachine &TM,
                          const GiselleSubtarget &Subtarget,
                          const GiselleRegisterBankInfo &RBI) {
  return new GiselleInstructionSelector(TM, Subtarget, RBI);
}

} // namespace Giselle

} // namespace llvm
