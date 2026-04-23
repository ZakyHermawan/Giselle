
#include "GiselleLegalizerInfo.h"
#include "llvm/CodeGen/GlobalISel/LegalizerHelper.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/Register.h"
#include "llvm/CodeGen/TargetOpcodes.h"
#include "llvm/CodeGenTypes/LowLevelType.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "giselle-legalinfo"

using namespace llvm;
using namespace LegalizeActions;

GiselleLegalizerInfo::GiselleLegalizerInfo(const GiselleSubtarget &ST) {
  const LLT P0 = LLT::pointer(0, 16);
  const LLT S8 = LLT::scalar(8);
  const LLT S16 = LLT::scalar(16);
  const LLT S32 = LLT::scalar(32);

  // Constants
  getActionDefinitionsBuilder(
      {TargetOpcode::G_CONSTANT, TargetOpcode::G_IMPLICIT_DEF})
      .legalFor({P0, S16, S32})
      .widenScalarToNextPow2(0)
      .clampScalar(0, S16, S32);

  // Load and store.
  getActionDefinitionsBuilder({TargetOpcode::G_LOAD, TargetOpcode::G_STORE})
      .legalForTypesWithMemDesc({{S8, P0, S8, 8},
                                 {S16, P0, S8, 8}, // anyext/truncstore
                                 {S16, P0, S16, 8},
                                 {S32, P0, S32, 8}})
      .clampScalar(0, S16, S32);

  // Pointer-handling.
  getActionDefinitionsBuilder(TargetOpcode::G_FRAME_INDEX).legalFor({P0});
  getActionDefinitionsBuilder(TargetOpcode::G_PTR_ADD).legalFor({{P0, S16}});

  // Arithmetic.
  getActionDefinitionsBuilder(TargetOpcode::G_ADD).legalFor({S16});

  getActionDefinitionsBuilder(TargetOpcode::G_ADD)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getLegacyLegalizerInfo().computeTables();
}
