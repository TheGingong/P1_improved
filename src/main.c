#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "./h-filer/valgsystemer.h"
#include "./h-filer/welfare_score.h"
#include "./h-filer/realistic_appropriation.h"

int main(void) {
    /* Initialisere variabler til clock_t struct */
    clock_t start,end;
    start = clock();
    srand(time(NULL));  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid

    /* Kalder antallet af simulering*/
    simulation(300);

    /* Printer programmet eksekverings tid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}