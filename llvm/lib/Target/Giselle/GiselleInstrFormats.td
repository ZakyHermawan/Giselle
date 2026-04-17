class GiselleRType<string asm, string operands,
  bits<7> func7,
  bits<3> func3,
  bits<7> opcode,
  dag oops = (outs), dag iops = (ins)> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(asm, "\t", operands);
  let OutOperandList = oops;
  let InOperandList = iops;

  bits<32> Inst;
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;
  let Inst{31-25} = func7;
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = func3;
  let Inst{11-7} = rd;
  let Inst{6-0} = opcode;
}
