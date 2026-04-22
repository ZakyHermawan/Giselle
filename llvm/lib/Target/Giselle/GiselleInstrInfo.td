include "GiselleInstrFormats.td"

def ADDi32rr : GiselleRType<"add", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b000,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SUBi32rr : GiselleRType<"sub", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b000,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def XORi32rr : GiselleRType<"xor", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b100,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def ORi32rr : GiselleRType<"or", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b110,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;


def ANDi32rr : GiselleRType<"and", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b111,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLLi32rr : GiselleRType<"sll", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b001,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SRLi32rr : GiselleRType<"srl", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b101,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SRAi32rr : GiselleRType<"sra", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b101,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLTi32rr : GiselleRType<"slt", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b010,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLTUi32rr : GiselleRType<"sltu", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b011,
                                /*opcode=*/0b0110011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def JALR : GiselleIType<"jalr", "$rd, ${imm}(${rs1})",
                                /*func3=*/0b000,
                                /*opcode=*/0b1100111,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, u16imm12:$imm)>;
