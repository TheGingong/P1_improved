typedef struct {
    char candidate;
    double welfare;
}candidate_welfare;

//double welfare_calculator(char winner);
double social_utility_efficiency(char winner);
void read_candidate_welfare(candidate_welfare *candidate);
char winner_index(char winner, candidate_welfare candidate[]);