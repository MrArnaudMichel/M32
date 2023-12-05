//
// Created by arnaud on 04/12/23.
//

#include "algo.h"

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

uint32_t sieve(uint32_t N, uint32_t* prime_tab) {
    uint32_t nb = 0;
    uint32_t tab[N - 2];
    for (int i = 2; i < N; i++) {
        tab[i] = i;
    }
    for (int i = 0; i < N - 2; ++i) {
        if (!isPrime(tab[i])) {
            tab[i] = 0;
        }
    }
    printf("Liste des premiers plus petits que 100\n");
    for (int i = 0; i < N - 2; ++i) {
        if (tab[i] != 0) {
            printf("%d ", tab[i]);
            nb ++;
        }
    }
    printf("\nNombre de premiers plus petits que 100: %d\n", nb);
    return nb;
}

bool isPrime(uint32_t N) {
    for (int i = 2; i < N && i * i <= N; ++i) {
        if (N % i == 0) {
            return false;
        }
    }
    return true;
}
