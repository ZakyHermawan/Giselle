// RUN: llvm-mc -triple=giselle %s  -o - | FileCheck %s

// CHECK: add x1, x2, x3
add x1, x2, x3

// CHECK: sub x1, x2, x3
sub x1, x2, x3

// CHECK: xor x1, x2, x3
xor x1, x2, x3

// CHECK: or x1, x2, x3
or x1, x2, x3

// CHECK: and x1, x2, x3
and x1, x2, x3

// CHECK: sll x1, x2, x3
sll x1, x2, x3

// CHECK: srl x1, x2, x3
srl x1, x2, x3

// CHECK: sra x1, x2, x3
sra x1, x2, x3

// CHECK: slt x1, x2, x3
slt x1, x2, x3

// CHECK: sltu x1, x2, x3
sltu x1, x2, x3
