#include <stdio.h>
#include "convert.h"
#include "america.h"
#include "borda.h"
#include "math.h"

const int dimensions = 5;
const int total_voters = 1000;

#include "realistic_appropriation.h"
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

/* -- PROGRAMMERING -- */

//funktion, der kan generere normalfordelinger pr. dimension
void gaussian_density () {
    
}

void generating_real_votes (int n_dimensions, cluster_t clusters) {
    //generer x klynger i n dimensioner
    for (int i = 0; i <= n_dimensions; i++) {

    }
}



void spatial(double koords[dimensions], char pref[ANTAL_CANDS],  double* cands[ANTAL_CANDS]) {
    candidate_distance_t cand_distances[ANTAL_CANDS];

    for (int i = 0; i < ANTAL_CANDS; i++) {
        double length = 0;
        for (int j = 0; j < dimensions; j++) {
            length += pow((koords[j] - cands[i][j]), 2);
        }
        cand_distances[i].id = i;
        cand_distances[i].distance = sqrt(length);
    }


    qsort(cand_distances, ANTAL_CANDS, sizeof(candidate_distance_t), compare);
    // printer præf ud for 1 voter


    // now time for velfærd
    double max_length = 0;
    double min_length = 0;
    double velfarg = 0;

    for (int i = 0; i < dimensions; i++) {
        max_length += pow(1-(-1),2);
    }
    max_length = sqrt(max_length);


    FILE* file = fopen("text-files/test-tekstil.txt", "w");
    fprintf(file, "%d(", rand() % STATES); //Printer tilfældig stat og '('

    for (int i = 0; i< ANTAL_CANDS; i++){
        velfarg = 1 - ((cand_distances[i].distance-min_length) / (max_length - min_length));
        pref[i] = cand_distances[i].id;
        fprintf(file, "%c%.3lf",'A' + pref[i], velfarg);
        printf("%c%lf, ", 'A' + pref[i], velfarg);
        if (i < ANTAL_CANDS-1) {
            fprintf(file, " "); //Printer mellemrum efter hver nytte, undtaget af den sidste
        }
    }

    fprintf(file, ")\n"); //Printer ')' og newline
    fclose(file);
}

int compare(const void* a, const void *b) {
    /* Typecaster til en candidate_distance pointer og returner differences af distance felterne*/
    double diff = ((candidate_distance_t*)a)->distance - ((candidate_distance_t*)b)->distance;

    if (diff < 0)
        return -1;

    if (diff > 0)
        return 1;

    else
        return 0;
}
