class AsmImmRange<int Low, int High> : AsmOperandClass {
  string StrLow = !if(!lt(Low, 0), "N" # !mul(Low, -1), "" # Low);
  let Name = "Imm" # StrLow # "_" # High;
  let DiagnosticType = "InvalidImm" # StrLow # "_" # High;
  let RenderMethod = "addImmOperands";
  let PredicateMethod = "isImmInRange<" # Low # "," # High # ">";
}

def s16imm12 : Operand<i16>, ImmLeaf<i16, [{return Imm >= -2048 && Imm < 2048;}]> {
  let ParserMatchClass = AsmImmRange<-2048, 2047>;
}

def u16imm12 : Operand<i16>, ImmLeaf<i16, [{return Imm >= 0 && Imm < 4096;}]> {
  let ParserMatchClass = AsmImmRange<0, 4095>;
}

def uimm5 : Operand<i16>, ImmLeaf<i16, [{return Imm >= 0 && Imm < 32;}]> {
  let ParserMatchClass = AsmImmRange<0, 31>;
}

class GiselleRType<string opcodestr, string operands,
  bits<7> funct7,
  bits<3> funct3,
  dag oops = (outs), dag iops = (ins)> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t", operands);
  let OutOperandList = oops;
  let InOperandList = iops;

  bits<32> Inst;
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;
  let Inst{31-25} = funct7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Inst{6-0} = 0b0110011;
}

class GiselleIType<string opcodestr, string operands,
  bits<3> funct3,
  bits<7> opcode,
  dag oops = (outs), dag iops = (ins)> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t", operands);
  let OutOperandList = oops;
  let InOperandList = iops;

  bits<32> Inst;
  bits<12> imm;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}

// Special case for srli and srai, because they have diffrent imm[11:5]
class GiselleShift<bits<7> funct7, bits<3> funct3, string opcodestr>
    : GiselleIType<opcodestr, "$rd, $rs1, $shamt",
                   funct3,
                   /*opcode=*/0b0010011,
                   (outs GPR32:$rd),
                   (ins GPR32:$rs1, uimm5:$shamt)> {
                   
  // Define the 5-bit variable mapped from the (ins ...) list
  bits<5> shamt;

  // Magic happens here: Concatenate funct7 (top 7) and shamt (bottom 5)
  // to populate the 'imm' variable required by GiselleIType
  let imm = { funct7, shamt }; 
}

class GiselleSType<string opcodestr, string operands,
  bits<3> funct3,
  dag oops = (outs), dag iops = (ins)> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t", operands);
  let OutOperandList = oops;
  let InOperandList = iops;

  bits<32> Inst;
  bits<12> imm;
  bits<5> rs2;
  bits<5> rs1;

  // Split the 12-bit immediate
  let Inst{31-25} = imm{11-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-7}  = imm{4-0};
  
  // Hardcoded Store Opcode
  let Inst{6-0}   = 0b0100011; 
}

// Pseudo instructions (don't have encoding information) and must
// disappear before the MC layer.
class GisellePseudoInstruction<dag oops, dag iops, list<dag> pattern>
    : Instruction {
  let Namespace      = "Giselle";
  dag OutOperandList = oops;
  dag InOperandList  = iops;
  let Pattern        = pattern;
  let isCodeGenOnly  = 1;
  let isPseudo       = 1;
  let Size           = 0; 
}
