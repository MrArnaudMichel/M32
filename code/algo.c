//
// Created by arnaud on 04/12/23.
//

#include "algo.h"

#include <stdio.h>
#include <stdlib.h>

EB bezout(uint32_t a, uint32_t b) {
    EB result;
    result.a = a;
    result.b = b;

    uint32_t uK[64];
    uint32_t vK[64];

    uK[0] = 1;
    uK[1] = 0;

    vK[0] = 0;
    vK[1] = 1;

    euclide euclide;
    euclide.a = a;
    euclide.b = b;
    euclide.q = a / b;
    euclide.r = a % b;

    int k = 2;
    while (euclide.r != 0) {
        printf("%d\t=\t%d\tx\t%d\t+\t%d\n", euclide.a, euclide.b, euclide.q, euclide.r);
        uK[k] = uK[k - 2] - (euclide.q * uK[k - 1]);
        vK[k] = vK[k - 2] - (euclide.q * vK[k - 1]);
        euclide.a = euclide.b;
        euclide.b = euclide.r;
        euclide.q = euclide.a / euclide.b;
        euclide.r = euclide.a % euclide.b;
        k++;
    }
    printf("%d\t=\t%d\tx\t%d\t+\t%d\n\n", euclide.a, euclide.b, euclide.q, euclide.r);
    printf("%d = %d * %d + %d * %d", euclide.b, uK[k-1], a, vK[k - 1], b);

    result.u = 0;
    result.v = 0;
    return result;
}
