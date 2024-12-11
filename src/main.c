#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./h-filer/valgsystemer.h"
#include "./h-filer/welfare_score.h"
#include "./h-filer/realistic_appropriation.h"

int main(void) {
    /* Initialisere variabler til clock_t struct */
    clock_t start,end;
    start = clock();

    /* Genererer stemmer */
    generate_data();

    FILE *file_for_america = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()

    /* Kalder simluering af det amerikanske valgsystem */
    char winner_america = america(file_for_america); // Gemmer vinderen fra america
    printf("The winner candidate of the american election is: %c\n", winner_america);
    fclose(file_for_america);

    FILE *borda_file = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()

    /* Kalder simulering af et valgsystem som bruger Borda count */
    char winner_borda = borda_count(borda_file); // Gemmer vinderen fra borda
    printf("The winner candidate of borda count is: %c\n\n", winner_borda);
    fclose(borda_file);

    /* Social utility efficiency print */
    printf("The social utility efficiency for the american election is: %.3lf%%\n", social_utility_efficiency(winner_america));
    printf("The social utility efficiency for borda count is: %.3lf%%\n\n", social_utility_efficiency(winner_borda));

    /* Printer programmet eksekverings tid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}

/* Åbner en fil */
FILE* open_file(const char* file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
        exit(EXIT_FAILURE);
    }

    return file;
}