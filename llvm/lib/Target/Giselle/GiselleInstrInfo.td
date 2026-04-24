include "GiselleInstrFormats.td"


let Pattern = [(set (i32 GPR32:$rd), (add (i32 GPR32:$rs1),
                                           (i32 GPR32:$rs2)))] in
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
