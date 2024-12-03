#include "vote_generation.h"
#include "america.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "static_variables.h"

void generate_vote_file(int voters_amount) {
    /* Åbner fil for at skrive til */
    FILE *f = fopen("text-files/file1.txt", "w");
    if (f == NULL) {
        printf("Could not open file, to write");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL)); //Seeder rand baseret på tid
    char candidate[NUMBER_CANDIDATES]; //Array til hver individs præference blandt kandidater
    double utility[NUMBER_CANDIDATES]; //Array til hver individs nytte for hver kandidat
    /* Indsætter kandidater i array med A-Z for antallet af kandidater*/
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        candidate[i] = 'A'+i;
    }

    for (int i = 0; i < voters_amount; i++) {
        shuffle_array(candidate); //Blander array af kandidater
        get_utility(utility); //Sortere array af tilfældig nytte

        fprintf(f, "%d(", rand() % STATES); //Printer tilfældig stat og '('

        /* Loop printer kandidater og nytte i ordnet rækkefølge for hver kandidat*/
        for (int j = 0; j < NUMBER_CANDIDATES; j++) {
            fprintf(f, "%c%.3lf", candidate[j], utility[j]);
            if (j < NUMBER_CANDIDATES-1) {
                fprintf(f, " "); //Printer mellemrum efter hver nytte, undtaget af den sidste
            }
        }
        fprintf(f, ")\n"); //Printer ')' og newline
    }

    fclose(f);
}

/* Blander arrayet tilfældigt med individets præferencer af kandidater */
void shuffle_array(char* candidates_shuffle) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        int random_candidate = rand()%NUMBER_CANDIDATES;
        char temp = candidates_shuffle[i];

        candidates_shuffle[i] = candidates_shuffle[random_candidate];
        candidates_shuffle[random_candidate] = temp;
    }
}

/* Fylder arrayet med tilfældige doubles fra 0.000 - 1.000, og sortere derefter fra størst til lavest */
void get_utility (double* utility_array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        utility_array[i] = rand() / (double)RAND_MAX;
    }
    qsort(utility_array, NUMBER_CANDIDATES, sizeof(double), compare);
}

/* Printer et array af chars. Brugt til debug, burde slettes */
void print_array(const char* array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");
}

/* Sammenligner to pointere til doubles, som returnere den største */
int compare(const void *a, const void *b) {
    double ap = *(const double*)a;
    double bp = *(const double*)b;
    if (ap > bp) return -1;
    if (ap < bp) return 1;
    return 0;
}