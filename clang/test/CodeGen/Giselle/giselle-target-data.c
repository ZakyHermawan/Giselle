// RUN: %clang_cc1 -triple giselle-unknown -o - -emit-llvm %s | \
// RUN: FileCheck %s -check-prefix=Giselle
// Giselle: target datalayout = "e-m:e-p:32:32:32-n32-i64:64:64-i32:32:32-i16:16:16-i1:8:8-f32:32:32-v32:32:32"
