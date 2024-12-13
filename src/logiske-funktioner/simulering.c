#include <stdio.h>
#include <stdlib.h>
#include "../h-filer/NOTUSED_vote_generation.h"
#include "../h-filer/valgsystemer.h"
#include "../h-filer/welfare_score.h"
#include "../h-filer/realistic_appropriation.h"

#define CHOSEN_FILE "text-files/test-tekstil.txt"

void simulation(int run_times) {
    double elected_borda = 0.0, elected_america = 0.0, max = 0.0, random_cand_welfare = 0.0,
           avg_elected_borda = 0.0, avg_elected_america = 0.0,
           avg_max = 0.0, avg_random_cand_welfare = 0.0;

    for (int i = 0; i < run_times; i++) {
        /* Genererer stemmer */
        generate_data(); // Vores stemmegenerering
        //generate_vote_file(1000); // Benytter impartial culture (tilfældig generering af stemmer)

        /* Kalder simluering af det amerikanske valgsystem */
        FILE *file_for_america = open_file(CHOSEN_FILE); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_america = america(file_for_america); // Gemmer vinderen fra america
        //printf("The winner candidate of the american election is: %c\n", winner_america);
        fclose(file_for_america);

        /* Kalder simulering af et valgsystem som bruger Borda count */
        FILE *borda_file = open_file(CHOSEN_FILE); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_borda = borda_count(borda_file); // Gemmer vinderen fra borda
        //printf("The winner candidate of borda count is: %c\n\n", winner_borda);
        fclose(borda_file);

        /* Social utility efficiency print */
        FILE *welfare_america = open_file(CHOSEN_FILE);
        FILE *welfare_borda = open_file(CHOSEN_FILE);

        utilitarian_welfare(winner_america, welfare_america, &max, &elected_america, &random_cand_welfare);
        utilitarian_welfare(winner_borda, welfare_borda, &max, &elected_borda, &random_cand_welfare);

        avg_max += max / run_times;
        avg_elected_america += elected_america / run_times;
        avg_elected_borda += elected_borda / run_times;
        avg_random_cand_welfare += random_cand_welfare / run_times;

        /* Print statements til hjælp af fejl håndtering af programmet
        - printf("avg_max: %lf\n", avg_max);
        - printf("avg_elected_america: %lf\n", avg_elected_america);
        - printf("avg_elected_borda: %lf\n", avg_elected_borda);
        - printf("avg_random_cand_welfare: %lf\n\n", avg_random_cand_welfare);
        */

        fclose(welfare_america);
        fclose(welfare_borda);
    }
    /* Sender vores avg værdier til beregning af SUE og printer resultatet af SUE beregningerne */
    SUE_value(avg_max, avg_random_cand_welfare, avg_elected_america, avg_elected_borda);
}