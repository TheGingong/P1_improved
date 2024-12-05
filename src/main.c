#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "america.h"
#include "borda.h"
#include "welfare_score.h"

int main(void) {
    /* Initialisere variabler til clock_t struct */
    clock_t start,end;
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
  
    /* Social utility efficiency print */
    printf("The social utility efficiency for the american election is: %.3lf%%\n", social_utility_efficiency(winner_america));
    printf("The social utility efficiency for borda count is: %.3lf%%\n\n", social_utility_efficiency(winner_borda));

    /* Printer programmet eksekverings tid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}