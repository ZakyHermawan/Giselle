#pragma once

#include "GiselleTargetLowering.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"

namespace llvm {

class TargetMachine;
class Triple;

class GiselleSubtarget : public TargetSubtargetInfo {
  virtual void anchor();
  GiselleTargetLowering TLInfo;

public:
  GiselleSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                   const TargetMachine &TM);
  const GiselleTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const TargetRegisterInfo *getRegisterInfo() const override {
    return nullptr; // TODO: Implement this.
  }

};

} // namespace llvm
