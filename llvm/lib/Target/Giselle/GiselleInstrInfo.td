include "GiselleInstrFormats.td"

def ADDi32rr : GiselleInstruction<"add", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;
