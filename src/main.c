#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "america.h"
#include "borda.h"
#include "welfare_score.h"


int main(void) {
    /* Kalder simluering af det amerikanske valgsystem */
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    if (file == NULL) {
        perror("Could not open file");
    }
    clock_t start,end;
    double cpu_time_used;

    start = clock();

    char winner_america = america(file);
    printf("The winner candidate of the american election is: %c\n", winner_america);
    fclose(file);

    FILE *file2 = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    if (file2 == NULL) {
        perror("Could not open file");
    }
    /* Kalder simulering af et valgsystem som bruger Borda count */
    char winner_borda = borda_count(file2);
    printf("The winner candidate of borda count is: %c\n\n", winner_borda);
    fclose(file2);
  
    /* Velfærd print */
    printf("The total welfare for America: %lf\n", welfare_calculator(winner_america));
    //printf("The total welfare for Borda count: %lf\n\n", welfare_calculator(winner_borda));

    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}
