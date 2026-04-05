// RUN: %clang -E -dM %s -o - 2>&1 \
// RUN:     --target=giselle \
// RUN:   | FileCheck -match-full-lines %s -check-prefix=CHECK_GISELLE
// CHECK_GISELLE: #define __Giselle__ 1
