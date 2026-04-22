include "llvm/Target/Target.td"
include "GiselleRegisterInfo.td"
include "GiselleInstrInfo.td"
include "GiselleCallingConvention.td"

// Just to remove warning: zero size arrays are an extension
def : ProcessorModel<"generic", NoSchedModel, /*Features=*/[]>;

def GiselleInstrInfo : InstrInfo;

def GiselleAsmParser : AsmParser {
  let ShouldEmitMatchRegisterAltName = 1;
}

def Giselle : Target {
  let InstructionSet = GiselleInstrInfo;
  let AssemblyParsers = [GiselleAsmParser];
}

defm : RemapAllTargetPseudoPointerOperands<GPR32>;
