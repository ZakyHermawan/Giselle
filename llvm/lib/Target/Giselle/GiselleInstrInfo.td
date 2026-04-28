include "GiselleInstrFormats.td"

// ===----------------------------------------------------------------===//
// R-TYPE
// ===----------------------------------------------------------------===//

let Pattern = [(set (i32 GPR32:$rd), (add (i32 GPR32:$rs1),
                                           (i32 GPR32:$rs2)))] in
def ADD : GiselleRType<"add", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b000,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SUB : GiselleRType<"sub", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b000,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def XOR : GiselleRType<"xor", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b100,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def OR : GiselleRType<"or", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b110,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;


def AND : GiselleRType<"and", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b111,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLL : GiselleRType<"sll", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b001,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SRL : GiselleRType<"srl", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b101,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SRA : GiselleRType<"sra", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b101,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLT : GiselleRType<"slt", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b010,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def SLTU : GiselleRType<"sltu", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

def ADDI : GiselleIType<"addi", "$rd, $rs1, $imm",
                                /*func3=*/0b000,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

def XORI : GiselleIType<"xori", "$rd, $rs1, $imm",
                                /*func3=*/0b100,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

// ===----------------------------------------------------------------===//
// I-TYPE
// ===----------------------------------------------------------------===//

def ORI : GiselleIType<"ori", "$rd, $rs1, $imm",
                                /*func3=*/0b110,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

def ANDI : GiselleIType<"andi", "$rd, $rs1, $imm",
                                /*func3=*/0b111,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

def SLLI : GiselleShift<0b0000000, 0b001, "slli">;
def SRLI : GiselleShift<0b0000000, 0b101, "srli">;
def SRAI : GiselleShift<0b0100000, 0b101, "srai">;

def SLTI : GiselleIType<"slti", "$rd, $rs1, $imm",
                                /*func3=*/0b010,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

// SLTIU takes a signed immediate in assembly,
// the hardware just treats it as unsigned during the comparison
def SLTIU : GiselleIType<"sltiu", "$rd, $rs1, $imm",
                                /*func3=*/0b011,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

def LB : GiselleIType<"lb", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b000,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s16imm12:$imm)>;

def LH : GiselleIType<"lh", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b001,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s16imm12:$imm)>;

def LW : GiselleIType<"lw", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b010,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s16imm12:$imm)>;

def LBU : GiselleIType<"lbu", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b100,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s16imm12:$imm)>;

def LHU : GiselleIType<"lhu", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b101,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s16imm12:$imm)>;

def JALR : GiselleIType<"jalr", "$rd, ${imm}(${rs1})",
                                /*func3=*/0b000,
                                /*opcode=*/0b1100111,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s16imm12:$imm)>;

// ===----------------------------------------------------------------===//
// S-TYPE
// ===----------------------------------------------------------------===//

def SB : GiselleSType<"sb", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b000,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s16imm12:$imm)>;

def SH : GiselleSType<"sh", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b001,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s16imm12:$imm)>;

def SW : GiselleSType<"sw", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b010,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s16imm12:$imm)>;

// ===----------------------------------------------------------------===//
// GlobalISel Pseudo Instructions
// ===----------------------------------------------------------------===//

// Return
let isReturn = 1, isTerminator = 1, isBarrier = 1, isCodeGenOnly = 1 in {
  def RET_PSEUDO : GisellePseudoInstruction<(outs), (ins), []>,
                  PseudoInstExpansion<(JALR X0, X1, 0)>;
}

// Call
let isCall = 1, Defs = [X1], Uses = [X2], isCodeGenOnly = 1 in {
  def CALL_PSEUDO : GisellePseudoInstruction<(outs), (ins i32imm:$target), []>;
}

// Call Frame Management (Adjust Stack Pointer)
let hasSideEffects = 1, isCodeGenOnly = 1 in {
  let Defs = [X2], Uses = [X2] in {
    def ADJCALLSTACKDOWN : GisellePseudoInstruction<(outs), (ins i32imm:$amt1, i32imm:$amt2), []>;
    def ADJCALLSTACKUP   : GisellePseudoInstruction<(outs), (ins i32imm:$amt1, i32imm:$amt2), []>;
  }
}
