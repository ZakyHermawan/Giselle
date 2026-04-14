let Namespace = "Giselle" in {

class GiselleReg<bits<5> enc, string name, list<string> altNames = []>
  : Register<name> {
  let HWEncoding{4-0} = enc;
  let AltNames = altNames;
}

let FallbackRegAltNameIndex = NoRegAltName in
def ABIRegAltName : RegAltNameIndex;

let RegAltNameIndices = [ABIRegAltName] in {
  let isConstant = true in
  def X0 : GiselleReg<0, "x0", ["zero"]>;
  def X1 : GiselleReg<1, "x1", ["ra"]>;
  def X2 : GiselleReg<2, "x2", ["sp"]>;
  def X3 : GiselleReg<3, "x3", ["gp"]>;
  def X4 : GiselleReg<4, "x4", ["tp"]>;
  def X5 : GiselleReg<5, "x5", ["t0"]>;
  def X6 : GiselleReg<6, "x6", ["t1"]>;
  def X7 : GiselleReg<7, "x7", ["t2"]>;
  def X8 : GiselleReg<8, "x8", ["s0", "fp"]>;
  def X9 : GiselleReg<9, "x9", ["s1"]>;
  def X10 : GiselleReg<10, "x10", ["a0"]>;
  def X11 : GiselleReg<11, "x11", ["a1"]>;
  def X12 : GiselleReg<12, "x12", ["a2"]>;
  def X13 : GiselleReg<13, "x13", ["a3"]>;
  def X14 : GiselleReg<14, "x14", ["a4"]>;
  def X15 : GiselleReg<15, "x15", ["a5"]>;
  def X16 : GiselleReg<16,"x16", ["a6"]>;
  def X17 : GiselleReg<17,"x17", ["a7"]>;
  def X18 : GiselleReg<18,"x18", ["s2"]>;
  def X19 : GiselleReg<19,"x19", ["s3"]>;
  def X20 : GiselleReg<20,"x20", ["s4"]>;
  def X21 : GiselleReg<21,"x21", ["s5"]>;
  def X22 : GiselleReg<22,"x22", ["s6"]>;
  def X23 : GiselleReg<23,"x23", ["s7"]>;
  def X24 : GiselleReg<24,"x24", ["s8"]>;
  def X25 : GiselleReg<25,"x25", ["s9"]>;
  def X26 : GiselleReg<26,"x26", ["s10"]>;
  def X27 : GiselleReg<27,"x27", ["s11"]>;
  def X28 : GiselleReg<28,"x28", ["t3"]>;
  def X29 : GiselleReg<29,"x29", ["t4"]>;
  def X30 : GiselleReg<30,"x30", ["t5"]>;
  def X31 : GiselleReg<31,"x31", ["t6"]>;
}

def GPR32 : RegisterClass<"Giselle", [i32], 32, (sequence "X%u", 0, 31)>;

} // Namespace = "Giselle"
