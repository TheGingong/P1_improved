#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "realistic_appropriation.h"
#include "static_variables.h"

int main(void) {
    /* Starter tidstagning af computing time */
    clock_t start,end;
    double cpu_time_used;
    start = clock();

    /* Kalder simluering af det amerikanske valgsystem */
    //FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.

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

    /* Initiering */
    FILE* file3 = fopen("text-files/test-tekstil.txt", "w");
    double total_model_array[TOTAL_VOTERS][DIMENSIONS];
    cluster_t cluster_array[CLUSTERS];
    /* Kør funktion */
    //generate_one_gauss(test, total_model_array, min_value, max_value);
    assemble_gauss(cluster_array, total_model_array, file3);
    fclose(file3);

    /* Kan lave grafer til debugging*/
    //create_graph(test_array, test_array2, "hej");
    //FreeAllocations();

    /* Beregner computing time */
    end = clock();
    cpu_time_used = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("The program executed in: %lf s\n", cpu_time_used);
    return 0;
}
