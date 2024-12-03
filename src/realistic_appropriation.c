#include <stdio.h>
#include <math.h>
#include "convert.h"
#include "realistic_appropriation.h"
#include "america.h"
#include "borda.h"

const int dimensions = 5;
const int total_voters = 1000;

/* -- NOTER -- */
/* -- Kontrolparametre --
 * Dispersion - klynger der former grupper med samme ideologi (politiske partier, religion, etc)
 * Correlation - høreorient fører til mere højreorient, sammenhæng mellem forskellige holdninger
 * Noise - der vil fremkomme folk som ikke stemmer rationelt
 * Limiting extreme ideologies - normalfordeling
 * Dimensional weights - visse sager vægtes højere end andre
 */

/* én normalfordeling medfører én cluster, hvilket implier én basis holdning, som alle holdninger samels om
 * flere normalfordelinger, for hver klynge der skal være, er mere korrekt.
 * - normalfordelingernes median er forskellig, afgør politisk centrum for klynge
 * - spredning varierer, nogle klyner er større eller mindre end andre, altså varians i medlemmer pr klynge
 * -
 */

/* -- variable --
 * antal dimensioner (mærkesager)
 * antal klynger pr dimension
 *     - spredning
 *     - middel (lokation på spacial)
 *     - vælgere i klyngen (50-300)
 *
 */

/* -- stemmer består af --
 * USA stat
 * antal kandidater med vægtning pr kandidat
 */

//stemmer genereres over x antal dimensioner (1 dimension, 1 mærkesag)

//hver dimension har x antal klynger (1 klynge, 1 normalfordeling) (-dispersion- -limiting extreme ideologies-)

//hver klynge har 50-300 medlemmer (varians i klyngestr)
        //der genereres ~2-5% impartial vælgere (-noise-)

//til sidst vægtes holdningerne blandt vælgerne, og vægten påføres deres holdninger (-dimensional weights-)
    //for alle gælder det, at én mærkesag kommer før en anden osv

// stemme: (0.3, 0.7, -0.1, -1, 1)

/* -- PROGRAMMERING -- */

//funktion, der kan generere én normalfordeling
double gaussian_density (cluster_t cluster_n, double voter_x) {
    return 1 / ( sqrt(2 * M_PI) * cluster_n.spread_cluster ) * exp(-(1/2) * pow((voter_x - cluster_n.mean_cluster) / cluster_n.spread_cluster, 2));
}

void generate_one_gauss (cluster_t cluster_n, double* gauss_array) {
    int voter_per_gauss = total_voters / dimensions;

    for (int i = 0; i < voter_per_gauss; i++) {
        gauss_array[i] = gaussian_density(cluster_n, i);
        printf("%lf", gauss_array[i]);
    }
}

void generating_real_votes (int n_dimensions, cluster_t clusters) {
    //generer x klynger i n dimensioner
    for (int i = 0; i <= n_dimensions; i++) {

    }
}
