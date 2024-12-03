#include "vote_generation.h"
#include "america.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "static_variables.h"

void generate_vote_file(int voters_amount) {
    FILE *f = fopen("text-files/file1.txt", "w");
    if (f == NULL) {
        printf("Could not open file, to write");
        exit(EXIT_FAILURE);
    }

    char candidate[NUMBER_CANDIDATES];
    double utility[NUMBER_CANDIDATES];
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        candidate[i] = 'A'+i;
    }

    srand(time(NULL));
    for (int i = 0; i < voters_amount; i++) {

        int j = 0;
        shuffle_array(candidate);
        shuffle_utility(utility);
        fprintf(f, "%d(%c%.3lf %c%.3lf %c%.3lf %c%.3lf %c%.3lf)\n",
        rand() % STATES,
        candidate[j], utility[j++],
        candidate[j], utility[j++],
        candidate[j], utility[j++],
        candidate[j], utility[j++],
        candidate[j], utility[j]);
    }

    fclose(f);
}


void shuffle_array(char* candidates_shuffle) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        int random_candidate = rand()%NUMBER_CANDIDATES;
        char temp = candidates_shuffle[i];
        candidates_shuffle[i] = candidates_shuffle[random_candidate];
        candidates_shuffle[random_candidate] = temp;
    }
}

void shuffle_utility (double* utility_array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        utility_array[i] = rand() / (double)RAND_MAX;
    }
    qsort(utility_array, NUMBER_CANDIDATES, sizeof(double), compare);
}

void print_array(const char* array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");
}

int compare(const void *a, const void *b) {
    double ap = *(const double*)a;
    double bp = *(const double*)b;
    if (ap > bp) return -1;
    if (ap < bp) return 1;
    return 0;
}