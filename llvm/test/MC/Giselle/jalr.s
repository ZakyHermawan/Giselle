// RUN: llvm-mc -triple giselle %s -o - | FileCheck %s
// RUN: llvm-mc -triple giselle %s -o - --show-encoding | FileCheck %s --check-prefix=ENCODING

// CHECK: jalr	x0, 0(x1)
// ENCODING: [0x67,0x80,0x00,0x00]
jalr x0, 0(x1)
