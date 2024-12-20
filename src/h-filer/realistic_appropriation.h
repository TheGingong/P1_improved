#include <stdio.h>
#include "../h-filer/static_variables.h"

#define MIN_SPREAD 0.001  // Minimum spredningsværdi
#define MAX_SPREAD 0.5  // Maximum spredningsværdi

/* Struct for en normalfordeling
 * Indeholder middelværdi, spredning, og antal vælgere for én normalfordeling */
typedef struct {
    double mean_cluster; // Middelværdi
    double spread_cluster; // Spredning
    int voters_cluster; // Vælgere for normalfordelingen
} cluster_t;

/* Struct for længde fra én holdning tilhørende en vælger, til en kandidat */
typedef struct {
    int id; // Kandidat-indeks
    double distance; // Distance fra vælger
} candidate_distance_t;

/* Prototyper */
void generate_data();
void assemble_gauss (cluster_t cluster_array[CLUSTERS], double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], FILE* file);
void make_cluster_array (cluster_t cluster_array[CLUSTERS]);
void generate_one_gauss(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h);
double generate_normal_using_rejection(cluster_t cluster_n);
double gaussian_density (cluster_t cluster_n, double voter_x);
void spatial(double koords[DIMENSIONS], double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS], FILE* file, double* max_length, double* min_length);
int create_state();
int compare(const void* a, const void *b);
void create_graph (double *x_akse, double *y_akse, double *x_akse2, double *y_akse2, char prefix[], char title[]);
void generate_one_muller(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h);
double generate_normal_using_box_muller(cluster_t cluster_n);
void box_muller(double *z1, double *z2);
