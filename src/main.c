#include <stdio.h>
#include <stdlib.h>
#include "america.h"
#include "borda.h"
#include <time.h>
#include "realistic_appropriation.h"
#include "convert.h"


int main(void) {
    /* Kalder simluering af det amerikanske valgsystem */
    //FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    clock_t start,end;
    double cpu_time_used;

    start = clock();

    //char winner_america = america(file);
    //printf("The winner candidate of the american election is: %c\n", winner_america);
    //fclose(file);
//
    //FILE *file2 = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
//
    ///* Kalder simulering af et valgsystem som bruger Borda count */
    //char winner_borda = borda_count(file2);
    //printf("The winner candidate of borda count is: %c\n\n", winner_borda);
    //fclose(file2);
  //
    /* Velfærd print */
    //printf("The total welfare for America: %lf\n", welfare_calculator(winner_america));
    //printf("The total welfare for Borda count: %lf\n\n", welfare_calculator(winner_borda));

    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s\n", cpu_time_used);

    double voter[] = {0.2, 1, -0.5, 0.1, 0.7};
    char pref[] = {0};
    double cand1[] = {1, 0.2, 0.5, -0.4, 0.9};
    double cand2[] = {-0.4, 0.4, 0.2, 1, -0.9};
    double cand3[] = {0.2, 0.9, -1, 0.6, 1};
    double cand4[] = {-1, 0.1, -0.2, 0.7, -0.1};
    double* cands[ANTAL_CANDS] = {cand1, cand2, cand3, cand4};

    spatial(voter, pref, cands);

    double test_array[200];
    cluster_t test; test.mean_cluster = 0; test.spread_cluster = 0.1; test.voters_cluster = 100;
    double min_value = -1.0;
    double max_value = 1.0;
    generate_one_gauss(test, test_array, min_value, max_value);



    double number_array[200];
    for (int i = 0; i < 200; i++) {
        number_array[i] = i;
    }
    create_graph(number_array, test_array);

    return 0;
}
