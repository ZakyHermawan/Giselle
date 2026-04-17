// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s
// RUN: llvm-mc -triple=giselle %s  -o - --show-encoding | FileCheck --check-prefix=ENCODING %s

// CHECK: add x0, x2, x3
// ENCODING: [0x33,0x00,0x31,0x00]
add x0, x2, x3

// CHECK: sub x1, x2, x3
// ENCODING: [0xb3,0x00,0x31,0x40]
sub x1, x2, x3

// CHECK: xor x1, x2, x3
// ENCODING: [0xb3,0x40,0x31,0x00]
xor x1, x2, x3

// CHECK: or x1, x2, x3
// ENCODING: [0xb3,0x60,0x31,0x00]
or x1, x2, x3

// CHECK: and x1, x2, x3
// ENCODING: [0xb3,0x70,0x31,0x00]
and x1, x2, x3

// CHECK: sll x1, x2, x3
// ENCODING: [0xb3,0x10,0x31,0x00]
sll x1, x2, x3

// CHECK: srl x1, x2, x3
// ENCODING: [0xb3,0x50,0x31,0x00]
srl x1, x2, x3

// CHECK: sra x1, x2, x3
// ENCODING: [0xb3,0x50,0x31,0x40]
sra x1, x2, x3

// CHECK: slt x1, x2, x3
// ENCODING: [0xb3,0x20,0x31,0x00]
slt x1, x2, x3

// CHECK: sltu x1, x2, x3
// ENCODING: [0xb3,0x30,0x31,0x00]
sltu x1, x2, x3
