#include <stdio.h>

typedef struct {
    char candidate;
    double welfare;
} candidate_welfare;

void social_utility_efficiency(char winner, FILE *file, double *max, double *elected, double *random);
void read_candidate_welfare(candidate_welfare *candidate, FILE *file);
int index_finder(char winner, candidate_welfare candidate[]);