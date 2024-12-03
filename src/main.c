#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "america.h"
#include "borda.h"
#include "welfare_score.h"


int main(void) {
    clock_t start,end;
    double cpu_time_used;
    start = clock();


    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med stemmer åbnes i read mode.
    if (file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
    }
    /* Kalder simluering af det amerikanske valgsystem */
    char winner_america = america(file); // Gemmer vinderen fra america
    printf("The winner candidate of the american election is: %c\n", winner_america);
    fclose(file);

    FILE *file2 = fopen("text-files/test-tekstil.txt", "r"); // Filen med stemmer åbnes i read mode.
    if (file2 == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
    }
    /* Kalder simulering af et valgsystem som bruger Borda count */
    char winner_borda = borda_count(file2); // Gemmer vinderen fra borda
    printf("The winner candidate of borda count is: %c\n\n", winner_borda);
    fclose(file2);
  
    /* Velfærd print */
    social_utility_efficiency(winner_america);

    /* Printer programmet eksekverings tid */
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}
