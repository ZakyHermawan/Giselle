// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s
// RUN: llvm-mc -triple=giselle %s  -o - --show-encoding | FileCheck --check-prefix=ENCODING %s

// CHECK: sb x5, 16(x2)
// ENCODING: [0x23,0x08,0x51,0x00]
sb t0, 16(sp)

// CHECK: sh x8, -4(x8)
// ENCODING: [0x23,0x1e,0x84,0xfe]
sh s0, -4(s0)

// CHECK: sw x1, 2044(x0)
// ENCODING: [0x23,0x2e,0x10,0x7e]
sw ra, 2044(zero)

// CHECK: sw x31, -2048(x30)
// ENCODING: [0x23,0x20,0xff,0x81]
sw x31, -2048(x30)
