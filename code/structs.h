//
// Created by arnaud on 04/12/23.
//

#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>

typedef struct coef_EB {
    uint32_t a;
    uint32_t b;
    int32_t u;
    int32_t v;
}EB;

typedef struct euclide {
    uint32_t a;
    uint32_t b;
    uint32_t q;
    uint32_t r;
}euclide;

#endif //STRUCTS_H
