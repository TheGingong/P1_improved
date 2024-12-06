#include "./h-filer/static_variables.h"

#define ANTAL_CANDS 4
#define DIMENSIONS 5
#define CLUSTERS 6
#define TOTAL_VOTERS 150
#define MIN_VALUE -1
#define MAX_VALUE 1
#define MIN_VALUE_SPREAD 0

/* Struct for en normalfordeling, indeholder dens middelværdi, spredning, og antal vælgere for én normalfordeling */
typedef struct {
    double mean_cluster; // Middelværdi
    double spread_cluster; // Spredning
    int voters_cluster; // Vælgere for undertegnede normalfordeling
} cluster_t;

/* Struct for længde fra én holdning tilhørende en vælger, til en kandidat */
typedef struct {
    int id; // Kandidat-indeks
    double distance; // Distance fra vælger
} candidate_distance_t;

/* Prototyper */
void assemble_gauss (cluster_t cluster_array[CLUSTERS], double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], FILE* file);
void make_cluster_array (cluster_t cluster_array[CLUSTERS]);
void generate_one_gauss(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j);
double generate_normal_using_density(cluster_t cluster_n);
double gaussian_density (cluster_t cluster_n, double voter_x);
void generate_candidates(double candidates_coordinates[DIMENSIONS][NUMBER_CANDIDATES], cluster_t cluster_array[CLUSTERS]);
void spatial(double koords[DIMENSIONS], double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS], FILE* file);
int compare(const void* a, const void *b);
void create_graph (double *x_akse, double *y_akse, char prefix[]);
