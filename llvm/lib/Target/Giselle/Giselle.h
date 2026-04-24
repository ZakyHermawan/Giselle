#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"

namespace llvm {

class GiselleTargetMachine;
class GiselleSubtarget;
class GiselleRegisterBankInfo;
class InstructionSelector;

namespace Giselle {

InstructionSelector *createInstructionSelector(const GiselleTargetMachine &,
                                               const GiselleSubtarget &,
                                               const GiselleRegisterBankInfo &);

} // namespace Giselle

} // namespace llvm
