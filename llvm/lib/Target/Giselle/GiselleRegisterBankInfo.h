#pragma once

#include "MCTargetDesc/GiselleMCTargetDesc.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGenTypes/LowLevelType.h"

#define GET_REGBANK_DECLARATIONS
#include "GiselleGenRegisterBank.inc"

namespace llvm {
class TargetRegisterInfo;

class GiselleGenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "GiselleGenRegisterBank.inc"
};

class GiselleRegisterBankInfo final : public GiselleGenRegisterBankInfo {
public:
  GiselleRegisterBankInfo(const TargetRegisterInfo &TRI);

  const InstructionMapping &
  getInstrMapping(const MachineInstr &MI) const override;
  const RegisterBank &getRegBankFromRegClass(const TargetRegisterClass &RC,
                                             LLT Ty) const override;
};

} // namespace llvm
