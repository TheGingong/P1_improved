#include <stdio.h>
#include <stdlib.h>
#include "../h-filer/static_variables.h"
#include "../h-filer/impartial_generation.h"
#include "../h-filer/valgsystemer.h"
#include "../h-filer/welfare_score.h"
#include "../h-filer/realistic_appropriation.h"

/* simulation er her hvor vi kalder vores hoved funktioner som når vi generere stemmer, america, borda og utilitarian_welfare.
 * Funktionerne bliver kaldt i en løkke af antal run_times som simulation kaldes med i main.
 * I hver gennemgang af simulation tælles avg_max, avg_elected_america, avg_elected_borda og avg_random_cand_welfare op,
 * som bruges i beregningen til SUE som til sidst kaldes uden for løkken.
 */
void simulation(int run_times) {
    double elected_borda = 0.0, elected_america = 0.0, max = 0.0, random_cand_welfare = 0.0,
           avg_elected_borda = 0.0, avg_elected_america = 0.0,
           avg_max = 0.0, avg_random_cand_welfare = 0.0;

    for (int i = 0; i < run_times; i++) {
        /* Genererer stemmer på baggrund af define GENERATE_DATA som kan ændres mellem impartial og spatial*/
        GENERATE_DATA

        /* Kalder simluering af det amerikanske valgsystem */
        FILE *file_for_america = open_file(CHOSEN_FILE); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_america = america(file_for_america); // Gemmer vinderen fra america
        //printf("The winner candidate of the american election is: %c\n", winner_america);
        fclose(file_for_america);

        /* Kalder simulering af et valgsystem som bruger Borda Count */
        FILE *borda_file = open_file(CHOSEN_FILE); // Filen med stemmer åbnes vha. funktion open_file()
        char winner_borda = borda_count(borda_file); // Gemmer vinderen fra borda
        //printf("The winner candidate of borda count is: %c\n\n", winner_borda);
        fclose(borda_file);

        /* Social utility efficiency print */
        FILE *welfare_america = open_file(CHOSEN_FILE);
        FILE *welfare_borda = open_file(CHOSEN_FILE);

        utilitarian_welfare(winner_america, welfare_america, &max, &elected_america, &random_cand_welfare); //
        utilitarian_welfare(winner_borda, welfare_borda, &max, &elected_borda, &random_cand_welfare);

        /* Velfærds værdier fra utilitarian_welfare bliver lagt sammen og divideres med run_times for at finde gennemsnittet,
         * og gemmes herefter i for eksempel avg_max som bruges til SUE beregning efter løkken */
        avg_max += (max / run_times);
        avg_elected_america += (elected_america / run_times);
        avg_elected_borda += (elected_borda / run_times);
        avg_random_cand_welfare += (random_cand_welfare / run_times);

        fclose(welfare_america);
        fclose(welfare_borda);
        printf("Sim %.0lf%% out of 100%%\n", (((double)i+1) / run_times) * 100); // Printer hvor langt programmet er i dens udførelse i %
    }
    /* Sender vores gennemsnitlige værdier til beregning af SUE og printer resultatet af SUE beregning */
    printf("SUE Value for the American election: %.3lf%%\n", SUE_value(avg_max, avg_random_cand_welfare, avg_elected_america));
    printf("SUE Value for Borda count: %.3lf%%\n", SUE_value(avg_max, avg_random_cand_welfare, avg_elected_borda));
}