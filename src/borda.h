/* Prototypes */
#include <stdio.h>
char borda_count(FILE *file);
void point_counting(char* voter_preference, int* candidate_points, FILE *file);
char winner(const int* candidate_points, const char* candidate);