class GiselleRType<string opcodestr, string operands,
  bits<7> funct7,
  bits<3> funct3,
  bits<7> opcode,
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
  let Inst{6-0} = opcode;
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

class AsmImmRange<int Low, int High> : AsmOperandClass {
  string StrLow = !if(!lt(Low, 0), "N" # !mul(Low, -1), "" # Low);
  let Name = "Imm" # StrLow # "_" # High;
  let DiagnosticType = "InvalidImm" # StrLow # "_" # High;
  let RenderMethod = "addImmOperands";
  let PredicateMethod = "isImmInRange<" # Low # "," # High # ">";
}

def u16imm12 : Operand<i16>, ImmLeaf<i16, [{return Imm >= 0 && Imm < 4096;}]> {
  let ParserMatchClass = AsmImmRange<0, 4095>;
}
