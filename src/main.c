#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./h-filer/valgsystemer.h"
#include "./h-filer/welfare_score.h"
#include "./h-filer/realistic_appropriation.h"
#include <unistd.h>

int main(void) {
    /* Initialisere variabler til clock_t struct */
    clock_t start,end;
    start = clock();
    srand(time(0) + getpid());  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid

    /* Genererer stemmer */
    generate_data();

    /* Kalder simluering af det amerikanske valgsystem */
    FILE *file_for_america = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()
    char winner_america = america(file_for_america); // Gemmer vinderen fra america
    printf("The winner candidate of the american election is: %c\n", winner_america);
    fclose(file_for_america);

    /* Kalder simulering af et valgsystem som bruger Borda count */
    FILE *borda_file = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()
    char winner_borda = borda_count(borda_file); // Gemmer vinderen fra borda
    printf("The winner candidate of borda count is: %c\n\n", winner_borda);
    fclose(borda_file);

    /* Social utility efficiency print */
    FILE *welfare_america = open_file("text-files/test-tekstil.txt");
    FILE *welfare_borda = open_file("text-files/test-tekstil.txt");

    printf("The social utility efficiency for the american election is: %.3lf%%\n", social_utility_efficiency(winner_america, welfare_america));
    printf("The social utility efficiency for borda count is: %.3lf%%\n\n", social_utility_efficiency(winner_borda, welfare_borda));

    fclose(welfare_america);
    fclose(welfare_borda);

    /* Printer programmet eksekverings tid */
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("The program executed in: %lf s", cpu_time_used);

    return 0;
}