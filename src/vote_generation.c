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
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        candidate[i] = 'A'+i;
    }

    //print_array(candidate);
    //shuffle_array(candidate);
    //print_array(candidate);
    //shuffle_array(candidate);
    //print_array(candidate);
    //shuffle_array(candidate);
    //print_array(candidate);
    //shuffle_array(candidate);

    srand(time(NULL));
    for (int i = 0; i < voters_amount; i++) {

        int j = 0;
        shuffle_array(candidate);
        fprintf(f, "%d(%c%.1lf %c%.1lf %c%.1lf %c%.1lf %c%.1lf)\n",
        rand() % STATES,
        candidate[j++], 1.0,
        candidate[j++], 1.0,
        candidate[j++], 1.0,
        candidate[j++], 1.0,
        candidate[j], 1.0);

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

void print_array(const char* array) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");
}