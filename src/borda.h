/* Prototypes */
char borda_count(const int number_of_candidates);
void point_counting(char* voter_preference, const int number_of_candidates, int* candidate_points);
char winner(const int* candidate_points, const char* candidate, const int number_of_candidates);

