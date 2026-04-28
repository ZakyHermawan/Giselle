// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s
// RUN: llvm-mc -triple=giselle %s  -o - --show-encoding | FileCheck --check-prefix=ENCODING %s

// CHECK: lui x10, 1
// ENCODING: [0x37,0x15,0x00,0x00]
lui a0, 1

// CHECK: auipc x6, 1048575
// ENCODING: [0x17,0xf3,0xff,0xff]
auipc t1, 1048575
