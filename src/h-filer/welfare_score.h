#include <stdio.h>

typedef struct {
    char candidate;
    double welfare;
} candidate_welfare;

void utilitarian_welfare(char winner, FILE *file, double *max, double *elected, double *random);
void read_candidate_welfare(candidate_welfare *candidates, FILE *file);
int index_finder(char winner, candidate_welfare candidates[]);