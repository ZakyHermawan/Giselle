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

let Pattern = [(set (i32 GPR32:$rd), (sub (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def SUB : GiselleRType<"sub", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b000,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (xor (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def XOR : GiselleRType<"xor", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b100,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (or (i32 GPR32:$rs1),
                                         (i32 GPR32:$rs2)))] in
def OR : GiselleRType<"or", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b110,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (and (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def AND : GiselleRType<"and", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b111,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (shl (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def SLL : GiselleRType<"sll", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b001,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (srl (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def SRL : GiselleRType<"srl", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b101,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (sra (i32 GPR32:$rs1),
                                          (i32 GPR32:$rs2)))] in
def SRA : GiselleRType<"sra", "$rd, $rs1, $rs2",
                                /*func7=*/0b0100000,
                                /*func3=*/0b101,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (setcc (i32 GPR32:$rs1),
                                            (i32 GPR32:$rs2),
                                            SETLT))] in
def SLT : GiselleRType<"slt", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b010,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

let Pattern = [(set (i32 GPR32:$rd), (setcc (i32 GPR32:$rs1),
                                            (i32 GPR32:$rs2),
                                            SETULT))] in
def SLTU : GiselleRType<"sltu", "$rd, $rs1, $rs2",
                                /*func7=*/0b0000000,
                                /*func3=*/0b011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, GPR32:$rs2)>;

// ===----------------------------------------------------------------===//
// I-TYPE
// ===----------------------------------------------------------------===//

let Pattern = [(set (i32 GPR32:$rd), (add (i32 GPR32:$rs1),
                                          (s32imm12:$imm)))] in
def ADDI : GiselleIType<"addi", "$rd, $rs1, $imm",
                                /*func3=*/0b000,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

let Pattern = [(set (i32 GPR32:$rd), (xor (i32 GPR32:$rs1),
                                          (s32imm12:$imm)))] in
def XORI : GiselleIType<"xori", "$rd, $rs1, $imm",
                                /*func3=*/0b100,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

let Pattern = [(set (i32 GPR32:$rd), (or (i32 GPR32:$rs1),
                                         (s32imm12:$imm)))] in
def ORI : GiselleIType<"ori", "$rd, $rs1, $imm",
                                /*func3=*/0b110,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

let Pattern = [(set (i32 GPR32:$rd), (and (i32 GPR32:$rs1),
                                          (s32imm12:$imm)))] in
def ANDI : GiselleIType<"andi", "$rd, $rs1, $imm",
                                /*func3=*/0b111,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

let Pattern = [(set (i32 GPR32:$rd), (shl (i32 GPR32:$rs1),
                                          (i32 uimm5:$shamt)))] in
def SLLI : GiselleShift<0b0000000, 0b001, "slli">;

let Pattern = [(set (i32 GPR32:$rd), (srl (i32 GPR32:$rs1),
                                          (i32 uimm5:$shamt)))] in
def SRLI : GiselleShift<0b0000000, 0b101, "srli">;

let Pattern = [(set (i32 GPR32:$rd), (sra (i32 GPR32:$rs1),
                                          (i32 uimm5:$shamt)))] in
def SRAI : GiselleShift<0b0100000, 0b101, "srai">;

let Pattern = [(set (i32 GPR32:$rd), (setcc (i32 GPR32:$rs1),
                                            (i32 s32imm12:$imm),
                                            SETLT))] in
def SLTI : GiselleIType<"slti", "$rd, $rs1, $imm",
                                /*func3=*/0b010,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

let Pattern = [(set (i32 GPR32:$rd), (setcc (i32 GPR32:$rs1),
                                            (i32 s32imm12:$imm),
                                            SETULT))] in
// SLTIU takes a signed immediate in assembly,
// the hardware just treats it as unsigned during the comparison
def SLTIU : GiselleIType<"sltiu", "$rd, $rs1, $imm",
                                /*func3=*/0b011,
                                /*opcode=*/0b0010011,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

def LB : GiselleIType<"lb", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b000,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s32imm12:$imm)>;

def LH : GiselleIType<"lh", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b001,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s32imm12:$imm)>;

def LW : GiselleIType<"lw", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b010,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s32imm12:$imm)>;

def LBU : GiselleIType<"lbu", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b100,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s32imm12:$imm)>;

def LHU : GiselleIType<"lhu", "$rd, ${imm}(${rs1})",
                              /*func3=*/0b101,
                              /*opcode=*/0b0000011,
                              (outs GPR32:$rd),
                              (ins GPR32:$rs1, s32imm12:$imm)>;

def JALR : GiselleIType<"jalr", "$rd, ${imm}(${rs1})",
                                /*func3=*/0b000,
                                /*opcode=*/0b1100111,
                                (outs GPR32:$rd),
                                (ins GPR32:$rs1, s32imm12:$imm)>;

// ===----------------------------------------------------------------===//
// J-TYPE
// ===----------------------------------------------------------------===//

def JAL : GiselleJType<"jal">;

// ===----------------------------------------------------------------===//
// S-TYPE
// ===----------------------------------------------------------------===//

def SB : GiselleSType<"sb", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b000,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s32imm12:$imm)>;

def SH : GiselleSType<"sh", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b001,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s32imm12:$imm)>;

def SW : GiselleSType<"sw", "$rs2, ${imm}(${rs1})",
                              /*func3=*/0b010,
                              (outs),
                              (ins GPR32:$rs2, GPR32:$rs1, s32imm12:$imm)>;

// ===----------------------------------------------------------------===//
// B-TYPE
// ===----------------------------------------------------------------===//

def BEQ  : GiselleBType<"beq",  0b000>;
def BNE  : GiselleBType<"bne",  0b001>;
def BLT  : GiselleBType<"blt",  0b100>;
def BGE  : GiselleBType<"bge",  0b101>;
def BLTU : GiselleBType<"bltu", 0b110>;
def BGEU : GiselleBType<"bgeu", 0b111>;

// ===----------------------------------------------------------------===//
// U-TYPE
// ===----------------------------------------------------------------===//

def LUI   : GiselleUType<"lui",   0b0110111>;
def AUIPC : GiselleUType<"auipc", 0b0010111>;

// ===----------------------------------------------------------------===//
// GlobalISel Pseudo Instructions
// ===----------------------------------------------------------------===//

// Return
let isReturn = 1, isTerminator = 1, isBarrier = 1, isCodeGenOnly = 1 in {
  def RET_PSEUDO : GisellePseudoInstruction<(outs), (ins), []>,
                  PseudoInstExpansion<(JALR X0, X1, 0)>;
}

// Call
let isCall = 1, Defs = [X1], isCodeGenOnly = 1 in {
  def CALL_PSEUDO : GisellePseudoInstruction<(outs), (ins i32imm:$target), []>;
}

// Call Frame Management (Adjust Stack Pointer)
let hasSideEffects = 1, isCodeGenOnly = 1 in {
  let Defs = [X2], Uses = [X2] in {
    def ADJCALLSTACKDOWN : GisellePseudoInstruction<(outs), (ins i32imm:$amt1, i32imm:$amt2), []>;
    def ADJCALLSTACKUP   : GisellePseudoInstruction<(outs), (ins i32imm:$amt1, i32imm:$amt2), []>;
  }
}
