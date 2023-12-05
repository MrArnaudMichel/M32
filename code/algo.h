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
bool isPrime(uint32_t N);
uint32_t sieve(uint32_t N, uint32_t* prime_tab);

#endif //ALGO_H
