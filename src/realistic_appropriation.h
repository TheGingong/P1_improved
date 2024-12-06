#define ANTAL_CANDS 4
#define dimensions 5
#define clusters 5

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

void generate_one_gauss(cluster_t cluster_n, double** gauss_2d_array, double min_value, double max_value, int dimension_j);
void make_cluster_array (cluster_t* cluster_array, int total_voters, int total_clusters);
void assemble_gauss (cluster_t* cluster_array, double** gauss_2d_array);
void spatial(double koords[dimensions], char pref[ANTAL_CANDS], double* cands[ANTAL_CANDS]);
int compare(const void* a, const void *b);
void create_graph (double *x_akse, double *y_akse, char prefix[]);
void gaussian_mixture(double array1[], double array2[], int size, double* mix_array);
int compare_doubles(const void* a, const void* b);