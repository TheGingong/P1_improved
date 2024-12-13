#include <stdio.h>
#include <stdlib.h>

#include "../h-filer/NOTUSED_vote_generation.h"
#include "../h-filer/valgsystemer.h"
#include "../h-filer/welfare_score.h"
#include "../h-filer/realistic_appropriation.h"

void simulation(int run_times) {
    double elected_borda = 0.0, elected_america = 0.0, max = 0.0, random_cand_welfare = 0.0,
           avg_elected_borda = 0.0, avg_elected_america = 0.0,
           avg_max = 0.0, avg_random_cand_welfare = 0.0;

    for (int i = 0; i < run_times; i++) {
        /* Genererer stemmer */
        generate_data(); // Vores stemmegenerering
        //generate_vote_file(1000); // Benytter impartial culture (tilfældig generering af stemmer)

        /* Kalder simluering af det amerikanske valgsystem */
        FILE *file_for_america = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_america = america(file_for_america); // Gemmer vinderen fra america
        //printf("The winner candidate of the american election is: %c\n", winner_america);
        fclose(file_for_america);

        /* Kalder simulering af et valgsystem som bruger Borda count */
        FILE *borda_file = open_file("text-files/test-tekstil.txt"); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_borda = borda_count(borda_file); // Gemmer vinderen fra borda
        //printf("The winner candidate of borda count is: %c\n\n", winner_borda);
        fclose(borda_file);

        /* Social utility efficiency print */
        FILE *welfare_america = open_file("text-files/test-tekstil.txt");
        FILE *welfare_borda = open_file("text-files/test-tekstil.txt");

        social_utility_efficiency(winner_america, welfare_america, &max, &elected_america, &random_cand_welfare);
        social_utility_efficiency(winner_borda, welfare_borda, &max, &elected_borda, &random_cand_welfare);

        avg_max += max / run_times;
        avg_elected_america += elected_america / run_times;
        avg_elected_borda += elected_borda / run_times;
        avg_random_cand_welfare += random_cand_welfare / run_times;

        fclose(welfare_america);
        fclose(welfare_borda);
    }

    /* Beregningen af SUE værdier for valgsystemerne
     * Som følger den "korrekt" formel med en tilfældig kandidat */
    double denumerator = (avg_max - avg_random_cand_welfare);
    double SUE_america_formel = ((avg_elected_america - avg_random_cand_welfare) / denumerator) * 100;
    double SUE_borda_formel = ((avg_elected_borda - avg_random_cand_welfare) / denumerator) * 100;
    printf("SUE Value with a random candidate for the american election: %.3lf%%\n", SUE_america_formel);
    printf("SUE Value with a random candidate for borda count election: %.3lf%%\n\n", SUE_borda_formel);

    /* Beregningen af SUE værdier for valgsystemerne
     * Som ikke tager højde for en tilfældig kandidat */
    double SUE_america = (avg_elected_america / avg_max) * 100;
    double SUE_borda = (avg_elected_borda / avg_max) * 100;
    printf("SUE Value without a random candidate for the american election: %.3lf%%\n", SUE_america);
    printf("SUE Value without a random candidate for borda count election: %.3lf%%\n\n", SUE_borda);

}