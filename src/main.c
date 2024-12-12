#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./h-filer/valgsystemer.h"
#include "./h-filer/welfare_score.h"
#include "./h-filer/realistic_appropriation.h"
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>


// Xorshift generator
uint32_t xorshift32(uint32_t *state) {
    uint32_t x = *state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    *state = x;
    return x;
}
uint32_t random_range_unbiased(uint32_t *state, uint32_t max) {
    uint32_t threshold = (0xFFFFFFFF / (max + 1)) * (max + 1);
    uint32_t r;
    do {
        r = xorshift32(state);
    } while (r >= threshold);
    return r % (max + 1);
}


int main(void) {
    /* Initialisere variabler til clock_t struct */
    clock_t start,end;
    start = clock();
    srand(time(NULL));  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid
    //uint32_t state = (uint32_t)time(NULL);


    //srand(time(0) + getpid());  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid
    //uint32_t random_number = random_range_unbiased(&state, 5);
    //printf("RANDOM NUMBER %u\n", random_number);

    /* Kalder antallet af simulering*/
    simulation(200);

    /* Printer programmet eksekverings tid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}

