#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./h-filer/valgsystemer.h"
#include "./h-filer/realistic_appropriation.h"
#include "./h-filer/main.h"

int main(void) {
    /* Initialisere variabler til clock_t struct, som bruges til at give os den lokale eksekveringstid */
    clock_t start, end;
    start = clock();
    srand(time(NULL));  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid

    /* Kører simulationer med antallet af simulationer defineret i static_variables.h */
    simulation(NUMBER_SIMULATIONS);

    /* Printer programmets eksekveringstid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}