typedef struct {
    char candidate;
    double welfare;
} candidate_welfare;

double social_utility_efficiency(char winner);
void read_candidate_welfare(candidate_welfare *candidate);
int hashing(char winner, candidate_welfare candidate[]);