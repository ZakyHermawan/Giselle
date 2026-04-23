#include "GiselleRegisterBankInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "giselle-reg-bank-info"

#define GET_TARGET_REGBANK_IMPL
#include "GiselleGenRegisterBank.inc"

using namespace llvm;

GiselleRegisterBankInfo::GiselleRegisterBankInfo(const TargetRegisterInfo &TRI)
    : GiselleGenRegisterBankInfo() {}
