// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s
// RUN: llvm-mc -triple=giselle %s  -o - --show-encoding | FileCheck --check-prefix=ENCODING %s

// CHECK: beq x1, x2, 256
// ENCODING: [0x63,0x80,0x20,0x10]
beq x1, x2, 256

// CHECK: bne x5, x6, -4
// ENCODING: [0xe3,0x9e,0x62,0xfe]
bne t0, t1, -4

// CHECK: bltu x10, x11, 4094
// ENCODING: [0xe3,0x6f,0xb5,0x7e]
bltu a0, a1, 4094
