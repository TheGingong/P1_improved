#define ANTAL_CANDS 4
#define dimensions 5
typedef struct {
    int id;         // Candidate ID
    double distance; // Distance from voter
} candidate_distance_t;


//constant values for a single cluster
typedef struct {
    double mean_cluster; //center of cluster, the mean
    double spread_cluster; //standard deviation from the mean
    int voters_cluster; //amount of voters within selected cluster
} cluster_t;

void generate_one_gauss (cluster_t cluster_n, double* gauss_array);
void spacial(double koords[dimensions], char pref[ANTAL_CANDS], double* cands[ANTAL_CANDS]);
int compare(const void* a, const void *b);