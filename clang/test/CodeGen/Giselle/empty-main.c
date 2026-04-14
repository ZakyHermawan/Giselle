// RUN: %clang_cc1 -triple giselle -O0 -emit-llvm %s -o - | FileCheck %s --check-prefix=O0
// RUN: %clang_cc1 -triple giselle -O1 -emit-llvm %s -o - | FileCheck %s --check-prefix=O1
// REQUIRES: giselle-registered-target

// Check that the Giselle target is properly hooked up for the target agnostic
// optimizers.

// O0-LABEL: define dso_local i32 @main(
// O0-SAME: ) #[[ATTR0:[0-9]+]] {
// O0-NEXT:  [[ENTRY:.*:]]
// O0-NEXT:    [[RETVAL:%.*]] = alloca i32, align 4
// O0-NEXT:    store i32 0, ptr [[RETVAL]], align 4
// O0-NEXT:    ret i32 0
//
// O1-LABEL: define dso_local noundef i32 @main(
// O1-SAME: ) local_unnamed_addr #[[ATTR0:[0-9]+]] {
// O1-NEXT:  [[ENTRY:.*:]]
// O1-NEXT:    ret i32 0
//
int main() {
  return 0;
}
