include "GiselleInstrFormats.td"

def ADDi32rr : GiselleInstruction<"add", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SUBi32rr : GiselleInstruction<"sub", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def XORi32rr : GiselleInstruction<"xor", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def ORi32rr : GiselleInstruction<"or", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def ANDi32rr : GiselleInstruction<"and", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SLLi32rr : GiselleInstruction<"sll", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SRLi32rr : GiselleInstruction<"srl", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SRAi32rr : GiselleInstruction<"sra", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SLTi32rr : GiselleInstruction<"slt", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

def SLTUi32rr : GiselleInstruction<"sltu", "$dst, $src0, $src1",
                                (outs GPR32:$dst),
                                (ins GPR32:$src0, GPR32:$src1)>;

