#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "america.h"
#include "borda.h"
#include "static_variables.h"
#include <time.h>

int main(void) {
    /* Kalder simluering af det amerikanske valgsystem */
    clock_t start,end;
    double cpu_time_used;

    start = clock();

    printf("The winner candidate of the american election is: %c\n", america());

    /* Kalder simulering af et valgsystem som bruger Borda count */
    printf("The winner candidate of borda count is: %c\n\n", borda_count());

    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);


    return 0;
}
