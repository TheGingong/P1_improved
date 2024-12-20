#include <stdio.h>
#include <stdlib.h>
#include "../h-filer/impartial_generation.h"
#include "../h-filer/realistic_appropriation.h"

/* Hovedfunktion, som generere stemmesæt med størrelsen voters_amount
 * Stemmerne er upartiske, så præferencen blandt kandidater er tilfældigt genereret
 * Stemmernes bosiddende stat er fortsat fordelt efter statens antal af valgmænd */
void generate_impartial_data(int voters_amount) {
    /* Åbner fil for at skrive til. */
    FILE *file_for_impartial = fopen("text-files/impartial-file.txt", "w");

    if (file_for_impartial == NULL) {
        printf("Could not open file, to write\n");
        exit(EXIT_FAILURE);
    }

    char candidate[NUMBER_CANDIDATES]; // Array til hver individs præference blandt kandidater.
    double utility[NUMBER_CANDIDATES]; // Array til hver individs nytte for hver kandidat.

    /* Indsætter kandidater i array med A-Z for antallet af kandidater. */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        candidate[i] = 'A' + i;
    }

    /* For løkken kører for hver vælger, og blander de mulige kandidater i en tilfældig rækkefølge,
     * for at fremstille vælgerens præferencer. Nytten bliver tilfældigt genereret, og derefter
     * sorteret i faldende rækkefølge, hvilket derved ikke tager højde for strategiske vælgere. */
    for (int i = 0; i < voters_amount; i++) {
        shuffle_array(candidate); // Blander array af kandidater.
        get_utility(utility); // Genererer og sorterer array af tilfældig nytte.

        fprintf(file_for_impartial, "%d(", create_state()); // Printer tilfældig stat og '(' i tekstfilen.
        /* Loop printer kandidater og nytte i ordnet rækkefølge for hver kandidat*/
        for (int j = 0; j < NUMBER_CANDIDATES; j++) {
            fprintf(file_for_impartial, "%c%.3lf", candidate[j], utility[j]);
            if (j < NUMBER_CANDIDATES-1) {
                fprintf(file_for_impartial, " "); // Printer mellemrum efter hver nytte, undtaget af den sidste.
            }
        }
        fprintf(file_for_impartial, ")\n"); // Printer ')' og newline.
    }

    fclose(file_for_impartial);
}

/* Blander arrayet af kandidater tilfældigt, som derved bliver individets præference af kandidater. */
void shuffle_array(char* candidates_shuffle) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        int random_candidate = rand()%NUMBER_CANDIDATES;
        char temp = candidates_shuffle[i];

        candidates_shuffle[i] = candidates_shuffle[random_candidate];
        candidates_shuffle[random_candidate] = temp;
    }
}

/* Fylder arrayet af nytte med tilfældige doubles fra 0.000 - 1.000, og sortere derefter fra størst til lavest. */
void get_utility (double* utility_array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        utility_array[i] = rand() / (double)RAND_MAX;
    }
    qsort(utility_array, NUMBER_CANDIDATES, sizeof(double), compare_impartial);
}

/* Sammenligner to pointere til doubles. Bruges til qsort. */
int compare_impartial(const void *a, const void *b) {
    double ap = *(const double*)a;
    double bp = *(const double*)b;
    if (ap > bp) return -1;
    if (ap < bp) return 1;
    return 0;
}