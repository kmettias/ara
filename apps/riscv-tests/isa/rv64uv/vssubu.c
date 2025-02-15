// Copyright 2021 ETH Zurich and University of Bologna.
// Solderpad Hardware License, Version 0.51, see LICENSE for details.
// SPDX-License-Identifier: SHL-0.51
//
// Author: Matheus Cavalcante <matheusd@iis.ee.ethz.ch>
//         Basile Bougenot <bbougenot@student.ethz.ch>

#include "vector_macros.h"

void TEST_CASE1(void) {
  VSET(4,e32,m1);
  VLOAD_U32(v1, 5, 10, 15, 20);
  VLOAD_U32(v2, 1, 2, 3, 25);
  __asm__ volatile("vssubu.vv v3, v1, v2"::);
  VEC_CMP_U32(1,v3,4,8,12,0);
}

void TEST_CASE2(void) {
  VSET(4,e32,m1);
  VLOAD_U32(v1, 5, 10, 15, 20);
  VLOAD_U32(v2, 1, 2, 3, 120);
  VLOAD_U32(v0,10,0,0,0);
  CLEAR(v3);
  __asm__ volatile("vssubu.vv v3, v1, v2, v0.t"::);
  VEC_CMP_U32(2,v3,0,8,0,0);
}

void TEST_CASE3(void) {
  VSET(4,e32,m1);
  VLOAD_U32(v1, 5, 1, 15, 20);
  const uint64_t scalar = 5;
  __asm__ volatile("vssubu.vx v3, v1, %[A]"::[A] "r" (scalar));
  VEC_CMP_U32(3,v3,0,0,10,15);
}

void TEST_CASE4(void) {
  VSET(4,e32,m1);
  VLOAD_U32(v1, 5, 1, 15, 20);
  const uint64_t scalar = 5;
  VLOAD_U32(v0,10,0,0,0);
  CLEAR(v3);
  __asm__ volatile("vssubu.vx v3, v1, %[A], v0.t"::[A] "r" (scalar));
  VEC_CMP_U32(4,v3,0,0,0,15);
}



int main(void){
  INIT_CHECK();
  enable_vec();
  enable_fp();
  TEST_CASE1();
  TEST_CASE2();
  TEST_CASE3();
  TEST_CASE4();
  EXIT_CHECK();
}
