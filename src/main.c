#include <stdio.h>
#include <stdlib.h>
#include "america.h"
#include "borda.h"
#include <time.h>

#include "convert.h"

int main(void) {
    /* Kalder simluering af det amerikanske valgsystem */
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    clock_t start,end;
    double cpu_time_used;

    start = clock();

    printf("The winner candidate of the american election is: %c\n", america(file));
    fclose(file);

    FILE *file2 = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.

    /* Kalder simulering af et valgsystem som bruger Borda count */
    printf("The winner candidate of borda count is: %c\n\n", borda_count(file2));
    fclose(file2);
  
    /* Velfærd print */
    printf("The total welfare for America: %lf\n", welfare_calculator(america(NUMBER_CANDIDATES)));
    printf("The total welfare for Borda count: %lf\n\n", welfare_calculator(borda_count()));

    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}
