// RUN: llvm-mc -triple giselle %s -o - | FileCheck %s
// RUN: llvm-mc -triple giselle %s -o - --show-encoding | FileCheck %s --check-prefix=ENCODING

// === Jump Instructions (J-Type) ===

// CHECK: jal x1, 2048
// ENCODING: [0xef,0x00,0x10,0x00]
jal ra, 2048

// CHECK: jal x0, -4
// ENCODING: [0x6f,0xf0,0xdf,0xff]
jal zero, -4

// CHECK: jal x5, 1048574
// ENCODING: [0xef,0xf2,0xff,0x7f]
jal t0, 1048574
