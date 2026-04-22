let Entry = 1 in
def CC_Giselle_Common : CallingConv<[
  // Promote smaller integer types to i32
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  // Pass integer arguments in registers a0-a7 (X10-X17)
  CCIfType<[i32], CCAssignToReg<[X10, X11, X12, X13, X14, X15, X16, X17]>>
]>;

let Entry = 1 in
def RetCC_Giselle_Common : CallingConv<[
  // Assign i32 return values to X10 (a0) and X11 (a1)
  CCIfType<[i32], CCAssignToReg<[X10, X11]>>
]>;

def CSR : CalleeSavedRegs<(add X1, X2, X8, X9, (sequence "X%u", 18, 27))>;
