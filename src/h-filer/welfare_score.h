#include <stdio.h>

/* Struct der kommer til at indeholde hver kandidats velfærdsscore */
typedef struct {
    char candidate;
    double welfare;
} candidate_welfare;

/* Prototyper */
void utilitarian_welfare(char winner, FILE *file, double *max, double *elected, double *random);
void read_candidate_welfare(candidate_welfare *candidates, FILE *file);
int index_finder(char winner, candidate_welfare candidates[]);
double SUE_value(double avg_max, double avg_random_cand_welfare, double avg_elected);