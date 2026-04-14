include "llvm/Target/Target.td"

include "GiselleRegisterInfo.td"

// Just to remove warning: zero size arrays are an extension
def : ProcessorModel<"generic", NoSchedModel, /*Features=*/[]>;

def GiselleInstrInfo : InstrInfo;

def Giselle : Target {
  let InstructionSet = GiselleInstrInfo;
}
