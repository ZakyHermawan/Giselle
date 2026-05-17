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
  const LLT P0 = LLT::pointer(0, 32);
  const LLT S1 = LLT::scalar(1);
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
  getActionDefinitionsBuilder({TargetOpcode::G_LOAD, TargetOpcode::G_SEXTLOAD,
                               TargetOpcode::G_ZEXTLOAD, TargetOpcode::G_STORE})
      .legalForTypesWithMemDesc({{S8, P0, S8, 8},
                                 {S16, P0, S8, 8}, // anyext/truncstore
                                 {S16, P0, S16, 16},
                                 {S32, P0, S16, 16},
                                 {S32, P0, S32, 32},
                                 {P0, P0, P0, 8}})
      .clampScalar(0, S16, S32);

  // Pointer-handling.
  getActionDefinitionsBuilder(TargetOpcode::G_FRAME_INDEX).legalFor({P0});
  getActionDefinitionsBuilder(TargetOpcode::G_PTR_ADD).legalFor({{P0, S32}});

  // Arithmetic.
  getActionDefinitionsBuilder(TargetOpcode::G_ADD)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_SUB)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_XOR)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_OR)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_AND)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_SHL)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_LSHR)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_ASHR)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_ICMP)
      .legalFor({S16, S32})
      .clampScalar(0, S16, S32);

  getActionDefinitionsBuilder(TargetOpcode::G_BRCOND)
      .legalFor({S1})
      .minScalar(0, S1);

    getActionDefinitionsBuilder(TargetOpcode::G_MUL)
        .libcallFor({S32})
        .widenScalarToNextPow2(0)
        .clampScalar(0, S32, S32);

    getActionDefinitionsBuilder({TargetOpcode::G_SMULH, TargetOpcode::G_UMULH}).lowerFor({S32});

    getActionDefinitionsBuilder({TargetOpcode::G_UDIV, TargetOpcode::G_SDIV, TargetOpcode::G_UREM, TargetOpcode::G_SREM})
        .libcallFor({S32})
        .clampScalar(0, S32, S32)
        .widenScalarToNextPow2(0);

  getActionDefinitionsBuilder(TargetOpcode::G_SELECT)
    .libcallFor({S32});

  getLegacyLegalizerInfo().computeTables();
}
