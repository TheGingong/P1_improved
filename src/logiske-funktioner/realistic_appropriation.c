#include <stdio.h>
#include <time.h>
#include "../h-filer/convert.h"
#include "../h-filer/america.h"
#include "../h-filer/realistic_appropriation.h"
#include "math.h"
#include "pbPlots.h"
#include "supportLib.h"

/* -- NOTER -- */
/* -- Kontrolparametre --
 * Dispersion - klynger der former grupper med samme ideologi (politiske partier, religion, etc)
 * Correlation - højreorient fører til mere højreorient, sammenhæng mellem forskellige holdninger
 * Noise - der vil fremkomme folk som ikke stemmer rationelt
 * Limiting extreme ideologies - normalfordeling
 * Dimensional weights - visse sager vægtes højere end andre
 */

/* -- PROGRAMMERING -- */

/*TODO: IKKE GJORT ENDNU:
 *  Kontrolparametre
 *  - - noise og strategiske stemmer
 *  - - correlation
 *  - - weights til distanceformel
 *  Ikke uniformt antal stemmer pr cluster
 *  Generering af kandidater (50% done)
 *  Generering af stater reflekterer virkelige populationer
 */

/* Funktion, der kører andre underordnede funktioner.
 * Formålet er, at samle alle elementerne, og skriver resultaterne i tekstfilen */
void assemble_gauss (cluster_t cluster_array[CLUSTERS], double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], FILE* file) {
    double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS];
    srand(time(NULL));  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid
    int density = 1;
    int box_muller = 0;

    for (int i = 0; i < DIMENSIONS ;i++) {
        make_cluster_array(cluster_array);


        if (density) {
            /* Genererer kanditat på baggrund af de samme clusters som bliver brugt til generering af stemmer.
             * Ved tilfælde af flere kandidator end clusters, vil clusterne blive gentaget */
            for (int k = 0; k < NUMBER_CANDIDATES; k++) {
                candidates_coordinates[k][i] = generate_normal_using_density(cluster_array[k%CLUSTERS]);
                //printf("%lf\n", candidates_coordinates[k][i]);
            }

            for (int h = 0; h < CLUSTERS; h++) {

                generate_one_gauss(cluster_array[h], gauss_2d_array, i, h);

            }
        }// else if (box_muller) {
//
         //   for (int k = 0; k < NUMBER_CANDIDATES; k++) {
         //       candidates_coordinates[k][i] = generate_normal_using_muller(cluster_array[k%CLUSTERS]);
         //       //printf("%lf\n", candidates_coordinates[k][i]);
         //   }
//
         //   for (int h = 0; h < CLUSTERS; h++) {
//
         //       generate_one_muller(cluster_array[h], gauss_2d_array, i, h);
//
         //   }
//


        }
    }


    //generate_candidates(candidates_coordinates, cluster_array); //Genererer array af kandidaters koordinater

    for (int i = 0; i < TOTAL_VOTERS; i++) { // Bruger spacial-stemmemodel for at skabe vælgerpræferencer
        spatial(gauss_2d_array[i], candidates_coordinates, file);
    }
}

/* Funktion, der opsætter en array af structs (cluster_t) */
void make_cluster_array (cluster_t cluster_array[CLUSTERS]) {
    for (int i = 0; i < CLUSTERS; i++) {
        // Sætter middelværdien til en tilfældig værdi fra -1 til 1
        cluster_array[i].mean_cluster = MIN_VALUE + (double) rand() / RAND_MAX * (MAX_VALUE - MIN_VALUE);
        // Sætter spredningen til en tilfældig værdi fra 0 til 1 (spredning kan ikke være negativ)
        cluster_array[i].spread_cluster = MIN_VALUE_SPREAD + (double) rand() / RAND_MAX * (MAX_VALUE - MIN_VALUE_SPREAD);
        // Fordeler vælgere uniformt på mængden af normalfordelinger
        cluster_array[i].voters_cluster = TOTAL_VOTERS / CLUSTERS;
    }
}

/* Funktion, der genererer tilfældige stemmer for én vælger i den j'te dimension*/
void generate_one_gauss(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {
    srand(time(NULL));  // Der seed'es for tilfældighedsfunktionerne baseret på computerens tid

    // Funktionen generate_normal_using_density bruges, og tilegner opinioner for vælgere i den gældende dimension
    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
            double value = generate_normal_using_density(cluster_n);
            gauss_2d_array[i][dimension_j] = value;
    }
}

/* Funktion, som generer et koordinat i én dimension for én stemme */
double generate_normal_using_density(cluster_t cluster_n) {
    double sample, density_at_sample, random_value;
    /* Do-while, som finder en tilfældig værdi (sample), og sammenligner med en anden tilfældig værdi (random_value).
     * Hvis tætheden for sample er mindre end den for random_value, findes der et nyt sample og en ny random.
     * Dette sikrer, at der er flere værdier tæt om middelværdien, 0, hvilket gør at de fleste genererede data ligger om 0 */
    do { // Funktionen kører indtil der findes en acceptabel værdi (dette kaldes rejection sampling)
        sample = (double) rand() / RAND_MAX * (MAX_VALUE - MIN_VALUE) + MIN_VALUE; // Genererer et punkt fra -1 til 1

        density_at_sample = gaussian_density(cluster_n, sample); //Tætheden findes for sample-punktet

        // Finder en tilfældig værdi mellem 0, og tætheden for middelværdien
        random_value = (double) rand() / RAND_MAX * gaussian_density(cluster_n, cluster_n.mean_cluster);

    } while (random_value > density_at_sample); // Tjekker, om sample er større end den tilfældige værdi, accepterer hvis den er
    return sample; // Returnerer sample-værdien
}

/* Funktion, der kan generere sandsynligheden for ét udfald i en normalfordeling (cluster) */
double gaussian_density (cluster_t cluster_n, double voter_x) {
    // Følgende er tæthedsfunktionen (også kaldet Gauss-funktionen)
    return 1 / ( sqrt(2 * M_PI) * cluster_n.spread_cluster )
           * exp(-0.5 * pow((voter_x - cluster_n.mean_cluster) / cluster_n.spread_cluster, 2));
}



//void generate_one_muller(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {
//
//    // Funktionen generate_normal_using_density bruges, og tilegner opinioner for vælgere i den gældende dimension
//    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
//        double value = generate_normal_using_muller(cluster_n);
//        gauss_2d_array[i][dimension_j] = value;
//    }
//}
//
//double generate_normal_using_muller(cluster_t cluster_n) { }





/* Funktion, som tager vælgeres rangeringskoordinater, og beregner længden fra dem til kandidternes
 * den kandidat der ligger tættest, er hvem vælgeren stemmer på for hver dimension*/
void spatial(double koords[DIMENSIONS], double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS], FILE* file) {

    // til videreudvikling
    //double cand1[] = {1, 0.2, 0.5, -0.4, 0.9};
    //double cand2[] = {-0.4, 0.4, 0.2, 1, -0.9};
    //double cand3[] = {0.2, 0.9, -1, 0.6, 1};
    //double cand4[] = {-1, 0.1, -0.2, 0.7, -0.1};
    //double* cands[ANTAL_CANDS] = {cand1, cand2, cand3, cand4};

    candidate_distance_t cand_distances[NUMBER_CANDIDATES]; // Array af candidate_distance_t structs

    /* Loop der itererer over antal kandidater */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        double length = 0;
        for (int j = 0; j < DIMENSIONS; j++) { // Loop der itererer over antal dimensioner
            length += pow((koords[j] - candidates_coordinates[i][j]), 2); // Euklids distanceformel (summerer over flere dimensioner)
        }
        cand_distances[i].id = i; // Tilegn indeks til den korresponderende vælger i struct-array'et
        cand_distances[i].distance = sqrt(length); // Tilegn længden fra vælger til kandidat på korresponderende plads i struct-array
    }

    /* Sorterer således den kandidat der er kortest til fra vælger, står først */
    qsort(cand_distances, NUMBER_CANDIDATES, sizeof(candidate_distance_t), compare);

    /* Der initieres variabler til brug for velfærds-beregning */
    double max_length = 0, min_length = 0, welfare = 0;

    /* Udregner maksimale længde en vælger kan være fra en kandidat
     * (velfærd på 0 for værst mulig, velfærd på 1 for bedst mulig) */
    for (int i = 0; i < DIMENSIONS; i++) {
        max_length += pow(1-(-1),2);
    }
    max_length = sqrt(max_length); // Euklids igen



    /* Printer tilfældelig stat til filen, må gerne være på baggrund af indbyggertal */
    fprintf(file, "%d(", rand() % STATES); // Printer tilfældig stat og '('

    /* Udregner velfærd baseret på distance, og printer dette til tekstfilen med en tilfældig stat (0-50) foran */
    for (int i = 0; i< NUMBER_CANDIDATES; i++){
        welfare = 1 - ((cand_distances[i].distance-min_length) / (max_length - min_length)); // Normaliserer distance 0 til 1

        fprintf(file, "%c%.3lf",'A' + cand_distances[i].id, welfare); // Printer værdierne til tekstfilen
        if (i < NUMBER_CANDIDATES-1) {
            fprintf(file, " "); // Printer mellemrum efter hver nytte, på nær den sidste
        }
    }
    fprintf(file, ")\n"); // Printer ')' og newline
}

/* qsort compare funktion til doubles i en struct */
int compare(const void* a, const void *b) {
    /* Typecaster til en candidate_distance pointer, og returner differencen mellem distancefelterne */
    double diff = ((candidate_distance_t*)a)->distance - ((candidate_distance_t*)b)->distance;

    if (diff < 0) return -1;
    if (diff > 0) return 1;
    else return 0;
}

/* Følgende bruges til at lave grafer ved brug af biblioteket, pbPlots, som behjælper debugging */
void create_graph (double *x_akse, double *y_akse, char prefix[]) {

    _Bool success;
    StringReference *errorMessage;
    RGBA color;
    color.r = 0; //Sort
    color.g = 255; //Rød
    color.b = 0; //Grøn
    color.a = 1;

    StartArenaAllocator();

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = x_akse;
    series->xsLength = 200;
    series->ys = y_akse;
    series->ysLength = 200;
    series->linearInterpolation = false;
//	series->lineType = L"dotted";
 //   series->lineTypeLength = wcslen(series->lineType);
    series->pointType = L"dots";
    series->pointTypeLength = wcslen(series->pointType);
   // series->lineThickness = 1;
    series->color = &color;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1000;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"Koordianter";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"X axis";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Y axis";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 1;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if(success){
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        char filename[64];
        sprintf(filename, "%s.png", prefix); //Sætter .png efter prefixet, for at danne filnavn
        WriteToFile(pngdata, filename);
        DeleteImage(canvasReference->image);
    }else{
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++){
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

   // RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
   // /* Bestemmer størrelsen på billedet, og x og y aksen*/
   // //DrawScatterPlot(imageRef, 600, 400, x_akse, 200, y_akse, 200, "Error in creating image");
   // size_t length;
   // ByteArray *pngdata = ConvertToPNG(imageRef->image); //Konvertere til png
   // char filename[64];
   // sprintf(filename, "%s.png", prefix); //Sætter .png efter prefixet, for at danne filnavn
   // WriteToFile(pngdata, filename);
   // DeleteImage(imageRef->image);
}
