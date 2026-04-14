class GiselleInstruction<string asm, string operands, dag oops = (outs), dag iops = (ins)> : Instruction<> {
  let Namespace = "Giselle";
  let AsmString = !strconcat(asm, "\t", operands);
  let OutOperandList = oops;
  let InOperandList = iops;
}
