#include <stdio.h>

#include "algo.h"
#include "structs.h"

int main() {
    printf("M32 - TD\n");
    printf("%d\n", fast_exp(5, 39, 20));
    printf("%d\n", least_primitive_root(13));
    printf("%d\n", discrete_log(2, 910, 911));
    return 0;
}
