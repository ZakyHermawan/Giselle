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

def simm13_lsb0 : Operand<i16>, ImmLeaf<i16, [{return Imm >= -4096 && Imm < 4096;}]> {
  let ParserMatchClass = AsmImmRange<-4096, 4095>;
}

def uimm20 : Operand<i32>, ImmLeaf<i32, [{return Imm >= 0 && Imm < 1048576;}]> {
  let ParserMatchClass = AsmImmRange<0, 1048575>;
}

def simm21_lsb0 : Operand<i32>, ImmLeaf<i32, [{return Imm >= -1048576 && Imm < 1048576;}]> {
  let ParserMatchClass = AsmImmRange<-1048576, 1048575>;
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

class GiselleBType<string opcodestr, bits<3> funct3> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t$rs1, $rs2, $imm");
  let OutOperandList = (outs); // Branches don't write to registers
  let InOperandList = (ins GPR32:$rs1, GPR32:$rs2, simm13_lsb0:$imm);

  bits<32> Inst;
  bits<13> imm;
  bits<5> rs2;
  bits<5> rs1;

  // The infamous RISC-V Branch Immediate Scramble
  let Inst{31}    = imm{12};
  let Inst{30-25} = imm{10-5};
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = funct3;
  let Inst{11-8}  = imm{4-1};
  let Inst{7}     = imm{11};
  
  // Hardcoded Branch Opcode
  let Inst{6-0}   = 0b1100011; 
}

class GiselleUType<string opcodestr, bits<7> opcode> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t$rd, $imm");
  let OutOperandList = (outs GPR32:$rd);
  let InOperandList = (ins uimm20:$imm);

  bits<32> Inst;
  bits<20> imm;
  bits<5> rd;

  let Inst{31-12} = imm;
  let Inst{11-7}  = rd;
  let Inst{6-0}   = opcode;
}

class GiselleJType<string opcodestr> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(opcodestr, "\t$rd, $imm");
  let OutOperandList = (outs GPR32:$rd);
  let InOperandList = (ins simm21_lsb0:$imm);

  bits<32> Inst;
  bits<21> imm;
  bits<5> rd;

  // The J-Type Immediate Scramble
  let Inst{31}    = imm{20};
  let Inst{30-21} = imm{10-1};
  let Inst{20}    = imm{11};
  let Inst{19-12} = imm{19-12};
  let Inst{11-7}  = rd;
  
  // Hardcoded JAL Opcode
  let Inst{6-0}   = 0b1101111; 
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
