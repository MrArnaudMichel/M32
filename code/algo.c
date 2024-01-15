//
// Created by arnaud on 04/12/23.
//

#include "algo.h"
#include <math.h>
#define true 1

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
        uK[k] = uK[k - 2] - (euclide.q * uK[k - 1]);
        vK[k] = vK[k - 2] - (euclide.q * vK[k - 1]);

        euclide.a = euclide.b;
        euclide.b = euclide.r;
        euclide.q = euclide.a / euclide.b;
        euclide.r = euclide.a % euclide.b;
        k++;
    }
    result.u = uK[k - 1];
    result.v = vK[k - 1];
    result.gcd = euclide.b;
    return result;
}

uint32_t sieve(uint32_t N, uint32_t* prime_tab) {
    uint32_t nb = 0;
    uint32_t tab[N - 2];
    for (int i = 2; i < N; i++) {
        tab[i] = i;
    }
    for (int i = 0; i < N - 2; i++) {
        if (tab[i] != 0) {
            printf("%d\n", tab[i]);
            for (int j = 0; j < N - 2; j++) {
                if (i != j && tab[i] % tab[j] == 0) {
                    tab[j] = 0;
                }
            }
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
    prime_tab = tab;
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

uint32_t modular_inv(uint32_t a, uint32_t n) {
    return bezout(a, n).u;
}


uint32_t fast_exp(uint32_t a, uint32_t k, uint32_t n) {
    uint32_t result = 1;
    a = a % n;
    while (k > 0) {
        if (k % 2 == 1) {
            result = (result * a) % n;
        }
        k = k >> 1;
        a = (a * a) % n;
    }
    return result;
}

/*
* Détermination du plus petit élément primitif modulo p
* où p est supposé premier
* retourne zéro en cas d'échec
*/
uint32_t least_primitive_root(uint32_t p) {
    if (p == 2) return 1;
    uint32_t phi = p - 1;
    for (uint32_t i = 2; i <= p; i++) {
        EB const result = bezout(i, p);
        if (result.gcd == 1) {
            if (fast_exp(i, phi, p) == 1) {
                return i;
            }
        }
    }
    return 0;
}


/*
* Détermination du logarithme discret de a, en base g, modulo p
* (où p est supposé premier)
* retourne zéro en cas d'échec
*/
uint32_t discrete_log(uint32_t a, uint32_t g, uint32_t p) {
    uint32_t m = (uint32_t)ceil(sqrt(p - 1)); // square root of p - 1

    // Precompute g^(-m) mod p
    uint32_t inv_m = 1;
    for (uint32_t i = 0; i < m; i++) {
        inv_m = (inv_m * g) % p;
    }
    inv_m = modular_inv(inv_m, p);

    // Baby-step
    uint32_t table[m];
    table[0] = 1;
    for (uint32_t i = 1; i < m; i++) {
        table[i] = (table[i - 1] * a) % p;
    }

    // Giant-step
    uint32_t giant_step = 1;
    for (uint32_t j = 0; j < m; j++) {
        // Check if giant_step is in the baby-step table
        for (uint32_t i = 0; i < m; i++) {
            if (giant_step == table[i]) {
                // Solution found: x = i + j * m
                return i + j * m;
            }
        }
        giant_step = (giant_step * inv_m) % p;
    }

    return 0; // Return 0 to indicate failure (logarithm not found)
}

/*
* Test de Miller-Rabin pour l'entier n et le témoin a
*  (où n-1=m*2^s, avec m impair)
* renvoie 1 ou 0 selon que a est un témoin de (primalité) deMiller-Rabin pour
* n, ou non
*/
char MR_witness(uint32_t n, uint32_t m, int s, uint32_t a) {
    uint32_t x = fast_exp(a, m, n);
    if (x == 1 || x == n - 1) {
        return 0;
    }

    for (int i = 1; i < s; i++) {
        x = fast_exp(x, 2, n);
        if (x == n - 1) {
            return 0;
        }
    }

    return 1;
}

uint32_t generate_random(uint32_t max) {
    // Simple pseudo-random number generation for demonstration purposes
    return rand() % (max - 1) + 1;
}

/*
* Test de Miller-Rabin pour l'entier n,
*  et witness_nb témoins tirés aus sort
* renvoie 1 ou 0 selon que candidate passe le test ou non
*/
char MR_test(uint32_t n, int witness_nb) {
    if (n == 2 || n == 3) {
        return 1;
    }
    if (n == 1 || n % 2 == 0) {
        return 0;
    }

    uint32_t m = n - 1;
    int s = 0;
    while (m % 2 == 0) {
        m /= 2;
        s++;
    }

    for (int i = 0; i < witness_nb; i++) {
        uint32_t a = generate_random(n - 2) + 1;
        if (MR_witness(n, m, s, a)) {
            return 0;
        }
    }

    return 1;
}


/*
* génère un pseudo premier s'écrivant avec k chiffres binaires
* epsilon est un majorant du risque de non primalité de l'entier
* retourné
*/
uint32_t MR_prime(int k, float epsilon) {

    uint32_t candidate;
    do {
        candidate = (1 << (k - 1)) + generate_random((1 << (k - 1)));

        if (MR_test(candidate, 5)) {
            return candidate;
        }
    } while (1);
}