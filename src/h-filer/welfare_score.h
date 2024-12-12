#include <stdio.h>

typedef struct {
    char candidate;
    double welfare;
} candidate_welfare;

double social_utility_efficiency(char winner, FILE *file);
void read_candidate_welfare(candidate_welfare *candidate, FILE *file);
int index_finder(char winner, candidate_welfare candidate[]);