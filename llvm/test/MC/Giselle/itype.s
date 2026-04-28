// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s
// RUN: llvm-mc -triple=giselle %s  -o - --show-encoding | FileCheck --check-prefix=ENCODING %s

// === Arithmetic & Logical I-Type ===

// CHECK: addi x5, x0, 15
// ENCODING: [0x93,0x02,0xf0,0x00]
addi t0, zero, 15

// CHECK: xori x10, x11, 255
// ENCODING: [0x13,0xc5,0xf5,0x0f]
xori a0, a1, 255

// CHECK: ori x8, x2, 4
// ENCODING: [0x13,0x64,0x41,0x00]
ori x8, sp, 4

// CHECK: andi x1, x4, 1
// ENCODING: [0x93,0x70,0x12,0x00]
andi ra, x4, 1


// === Shift I-Type ===

// CHECK: slli x7, x6, 8
// ENCODING: [0x93,0x13,0x83,0x00]
slli t2, t1, 8

// CHECK: srli x12, x13, 16
// ENCODING: [0x13,0xd6,0x06,0x01]
srli x12, a3, 16

// CHECK: srai x18, x19, 31
// ENCODING: [0x13,0xd9,0xf9,0x41]
srai s2, x19, 31


// === Compare I-Type ===

// CHECK: slti x28, x0, -1
// ENCODING: [0x13,0x2e,0xf0,0xff]
slti t3, zero, -1

// CHECK: sltiu x14, x15, -1
// ENCODING: [0x13,0xb7,0xf7,0xff]
sltiu x14, a5, -1


// === Load Instructions ===

// CHECK: lb x20, 16(x2)
// ENCODING: [0x03,0x0a,0x01,0x01]
lb s4, 16(sp)

// CHECK: lh x3, -2048(x0)
// ENCODING: [0x83,0x11,0x00,0x80]
lh x3, -2048(zero)

// CHECK: lw x29, -20(x8)
// ENCODING: [0x83,0x2e,0xc4,0xfe]
lw t4, -20(fp)

// CHECK: lbu x16, 4(x1)
// ENCODING: [0x03,0xc8,0x40,0x00]
lbu a6, 4(x1)

// CHECK: lhu x17, 8(x4)
// ENCODING: [0x83,0x58,0x82,0x00]
lhu x17, 8(tp)


// === Jump Instructions ===

// CHECK: jalr x0, 0(x1)
// ENCODING: [0x67,0x80,0x00,0x00]
jalr zero, 0(x1)
