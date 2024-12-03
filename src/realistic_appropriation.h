//constant values for a single cluster
typedef struct {
    double mean_cluster; //center of cluster, the mean
    double spread_cluster; //standard deviation from the mean
    int voters_cluster; //amount of voters within selected cluster
} cluster_t;

void generate_one_gauss (cluster_t cluster_n, double* gauss_array);