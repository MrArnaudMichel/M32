//
// Created by arnaud on 04/12/23.
//

#ifndef ALGO_H
#define ALGO_H

#include "structs.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

EB bezout(uint32_t a, uint32_t b);
uint32_t sieve(uint32_t N, uint32_t* prime_tab);
bool isPrime(uint32_t N);
uint32_t sieve(uint32_t N, uint32_t* prime_tab);
uint32_t fast_exp(uint32_t a, uint32_t k, uint32_t n);
bool puissance2(const unsigned int a, const unsigned int i);
uint32_t least_primitive_root(uint32_t p);
uint32_t discrete_log(uint32_t a, uint32_t g,uint32_t p);
char MR_witness(uint32_t n, uint32_t m, int s, uint32_t a);
char MR_test(uint32_t n, int witness_nb);
uint32_t MR_prime(int k, float epsilon);

#endif //ALGO_H
