#include <stdio.h>
#include <time.h>
#include "../h-filer/valgsystemer.h"
#include "../h-filer/realistic_appropriation.h"
#include "math.h"
#include "../pbPlots/pbPlots.h"
#include "../pbPlots/supportLib.h"

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

void generate_data() {
    /* Initiering */
    FILE* generate_data_file = fopen("text-files/test-tekstil.txt", "w");

    if (generate_data_file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
        exit(EXIT_FAILURE);
    }

    double total_model_array[TOTAL_VOTERS][DIMENSIONS];
    cluster_t cluster_array[CLUSTERS];
    /* Kør funktion */
    //generate_one_gauss(test, total_model_array, min_value, max_value);
    assemble_gauss(cluster_array, total_model_array, generate_data_file);
    fclose(generate_data_file);

    /* Kan lave grafer til debugging*/
    //create_graph(test_array, test_array2, "hej");
    //FreeAllocations();
}

/* Funktion, der kører andre underordnede funktioner.
 * Formålet er, at samle alle elementerne, og skriver resultaterne i tekstfilen */
void assemble_gauss (cluster_t cluster_array[CLUSTERS], double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], FILE* file) {
    double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS];
    int density = 1;
    int box_muller = 0;
    cluster_t test_array[3];
    test_array[0].mean_cluster = 0.28934598834192937; test_array[0].spread_cluster = 0.068039796136356703; test_array[0].voters_cluster = 1100;
    test_array[1].mean_cluster = 0.73094882045960885; test_array[1].spread_cluster = 0.9; test_array[1].voters_cluster = 1100;
    test_array[2].mean_cluster = 0.63444929349650558; test_array[2].spread_cluster = 0.12379848628192998; test_array[2].voters_cluster = 1100;
    for (int i = 0; i < DIMENSIONS ;i++) {
        make_cluster_array(cluster_array);

        /* If statement så man kan køre tæthedsfunktionen eller Box Muller */
        if (density) {
            /* Genererer kandidat på baggrund af de samme clusters som bliver brugt til generering af stemmer.
             * Ved tilfælde af flere kandidater end clusters, vil clusters blive gentaget */
            for (int k = 0; k < NUMBER_CANDIDATES; k++) {
                candidates_coordinates[k][i] = generate_normal_using_density(cluster_array[k%CLUSTERS]);

            }
            for (int h = 0; h < CLUSTERS; h++) {
                generate_one_gauss(cluster_array[h], gauss_2d_array, i, h);
            }


        } else if (box_muller) {
            for (int k = 0; k < NUMBER_CANDIDATES; k++) {
                candidates_coordinates[k][i] = generate_normal_using_box_muller(cluster_array[k%CLUSTERS]);
            }

            for (int h = 0; h < CLUSTERS; h++) {
                generate_one_muller(cluster_array[h], gauss_2d_array, i, h);
            }
        }


    //for (int a = 0; a < 20; a++) {
    //    printf("%d", )
    //}

    }
    const int dim = 2;
    double tal_x[TOTAL_VOTERS];
    double tal_y[TOTAL_VOTERS];
    for (int z = 0; z < TOTAL_VOTERS; z++) {
        tal_x[z] = z;
        tal_y[z] = gauss_2d_array[z][dim];
        //printf("%d %lf\n", z, gauss_2d_array[z][dim]);
    }
    char title[64];
    if (density) {
        sprintf(title, "Density");
    } else {
        sprintf(title, "Box-Muller");
    }

    create_graph(tal_x, tal_y, "Gauss", title);

    double max_length = 0;
    /* Kører spatial funktionen for hver voter, der generere en præference baseret rangering */
    for (int i = 0; i < TOTAL_VOTERS; i++) { // Bruger spacial-stemmemodel for at skabe vælgerpræferencer
        spatial(gauss_2d_array[i], candidates_coordinates, file, &max_length);
    }

}

/* Funktion, der opsætter en array af structs (cluster_t) */
void make_cluster_array (cluster_t cluster_array[CLUSTERS]) {

    for (int i = 0; i < CLUSTERS; i++) {
        // Sætter middelværdien til en tilfældig værdi fra -1 til 1
        //cluster_array[i].mean_cluster = MIN_VALUE_MEAN + (double) rand() / RAND_MAX * (MAX_VALUE_MEAN - MIN_VALUE_MEAN);
        cluster_array[i].mean_cluster = (0 - 3 * 1) + (double) rand() / RAND_MAX * ((0 + 3 * 1) - (0 - 3 * 1));

        // Sætter spredningen til en tilfældig værdi fra 0 til 1 (spredning kan ikke være negativ)

        // Generate random spread from uniform distribution
        cluster_array[i].spread_cluster = (double) rand() / RAND_MAX * (MAX_SPREAD - MIN_SPREAD) + MIN_SPREAD;

        //cluster_array[i].spread_cluster = MIN_VALUE_SPREAD + 0.5 * (double) rand() / RAND_MAX * (MAX_VALUE - MIN_VALUE_SPREAD);

        // Fordeler vælgere uniformt på mængden af normalfordelinger
        cluster_array[i].voters_cluster = (double)TOTAL_VOTERS / (double)CLUSTERS;
    }
}

/* Funktion, der genererer tilfældige stemmer for én vælger i den j'te dimension*/
void generate_one_gauss(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {

    // Funktionen generate_normal_using_density bruges, og tilegner opinioner for vælgere i den gældende dimension
    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
            double value = generate_normal_using_density(cluster_n);
            gauss_2d_array[i][dimension_j] = value;
    }
}

/* Funktion, som generer et koordinat i én dimension for én stemme */
double generate_normal_using_density(cluster_t cluster_n) {
    double sample, density_at_sample, random_value;
    double min_sample = cluster_n.mean_cluster - 3 * cluster_n.spread_cluster;
    double max_sample = cluster_n.mean_cluster + 3 * cluster_n.spread_cluster;
    /* Do-while, som finder en tilfældig værdi (sample), og sammenligner med en anden tilfældig værdi (random_value).
     * Hvis tætheden for sample er mindre end den for random_value, findes der et nyt sample og en ny random.
     * Dette sikrer, at der er flere værdier tæt om middelværdien, 0, hvilket gør at de fleste genererede data ligger om 0 */
    do { // Funktionen kører indtil der findes en acceptabel værdi (dette kaldes rejection sampling)
        sample = (double) rand() / RAND_MAX * (max_sample - min_sample) + min_sample; // Genererer et punkt fra -1 til 1

        density_at_sample = gaussian_density(cluster_n, sample); //Tætheden findes for sample-punktet

        // Finder en tilfældig værdi mellem 0, og tætheden for middelværdien
        random_value = (double) rand() / RAND_MAX * gaussian_density(cluster_n, cluster_n.mean_cluster);

    } while (random_value > density_at_sample); // Tjekker, om sample er større end den tilfældige værdi, accepterer hvis den er
    //printf("%lf %lf\n", sample, density_at_sample);
    //printf("accepted sample = %lf\n", sample);
    return sample; // Returnerer sample-værdien
}

/* Funktion, der kan generere sandsynligheden for ét udfald i en normalfordeling (cluster) */
double gaussian_density (cluster_t cluster_n, double voter_x) {
    // Følgende er tæthedsfunktionen (også kaldet Gauss-funktionen)
    return 1 / ( sqrt(2 * M_PI) * cluster_n.spread_cluster )
           * exp(-0.5 * pow((voter_x - cluster_n.mean_cluster) / cluster_n.spread_cluster, 2));
}

/* Box Muller algoritme der ud fra 2 uniform-fordelte tal genererer 2 normalfordelte tal */
void box_muller(double *z1, double *z2) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;

    // Fejl håndtering så vi ikke står med ln(0) som ikke findes
    if (u1 == 0.0) {
        u1 = 0.0001;
    }

    *z1 = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
    *z2 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
}


/* Funktion der benytter spread og mean til ændre det normalfordelte tal */
double generate_normal_using_box_muller(cluster_t cluster_n) {
    static int use_last = 0;
    static double z1, z2;

    if (use_last) { // Hvis vi har et tidligere ubenyttet udregnet tal, benyt det
        use_last = 0;
        return cluster_n.mean_cluster + z2 * cluster_n.spread_cluster; // +mean og *spread
    }

    box_muller(&z1, &z2); // Generer nye normalfordelte tal
    use_last = 1;
    return cluster_n.mean_cluster + z1 * cluster_n.spread_cluster; // +mean og *spread
}


/* Samme som "generate_one_gauss" men bare med Box Muller algoritmen */
void generate_one_muller(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {

    // Funktionen generate_normal_using_muller bruges, og tilegner opinioner for vælgere i den gældende dimension
    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
        double value = generate_normal_using_box_muller(cluster_n);
        gauss_2d_array[i][dimension_j] = value;
    }
}


/* Funktion, som tager vælgeres rangerings-koordinater, og beregner længden fra dem til kandidaternes
 * den kandidat der ligger tættest, er hvem vælgeren stemmer på for hver dimension*/
void spatial(double koords[DIMENSIONS], double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS], FILE* file, double* max_length) {

    candidate_distance_t cand_distances[NUMBER_CANDIDATES]; // Array af candidate_distance_t structs

    /* Loop der itererer over antal kandidater */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        double length = 0;

        for (int j = 0; j < DIMENSIONS; j++) { // Loop der itererer over antal dimensioner
            length += pow((koords[j] - candidates_coordinates[i][j]), 2); // Euklids distanceformel (summerer over flere dimensioner)
        }
        cand_distances[i].id = i; // Tilegn indeks til den korresponderende vælger i struct-arrayet
        cand_distances[i].distance = sqrt(length) ; // Tilegn længden fra vælger til kandidat på korresponderende plads i struct-array
        if (cand_distances[i].distance > *max_length) {
            *max_length = cand_distances[i].distance;
        }

    }

    /* Sorterer således den kandidat der er kortest til fra vælger, står først */
    qsort(cand_distances, NUMBER_CANDIDATES, sizeof(candidate_distance_t), compare);

    /* Der initieres variabler til brug for velfærds-beregning */
    double min_length = 0, welfare = 0;

    /* Udregner maksimale længde en vælger kan være fra en kandidat
     * (velfærd på 0 for værst mulig, velfærd på 1 for bedst mulig) */
    //for (int i = 0; i < DIMENSIONS; i++) {
    //    max_length += pow(MAX_VALUE-(MIN_VALUE),2);
    //}
    //max_length = sqrt(max_length); // Euklids igen



    /* Printer tilfældig stat til filen, må gerne være på baggrund af indbyggertal */
    fprintf(file, "%d(", create_state()); // Printer tilfældig stat og '('

    /* Udregner velfærd baseret på distance, og printer dette til tekstfilen med en tilfældig stat (0-50) foran */
    for (int i = 0; i< NUMBER_CANDIDATES; i++){
        welfare = 1 - ((cand_distances[i].distance-min_length) / (*max_length - min_length)); // Normaliserer distance 0 til 1
        //welfare = ikke_linear(cand_distances[i].distance); // Ikke linear welfare
        //printf("welfare = %lf dist = %lf\n", welfare, cand_distances[i].distance);

        fprintf(file, "%c%.3lf",'A' + cand_distances[i].id, welfare); // Printer værdierne til tekstfilen
        if (i < NUMBER_CANDIDATES-1) {
            fprintf(file, " "); // Printer mellemrum efter hver nytte, på nær den sidste
        }
    }
   fprintf(file, ")\n"); // Printer ')' og newline
}

/* Generere en vægtet tilfældig stemme,
 * med hyppigere udfald for en stat med flere valgmænd */
int create_state() {
    int stat = rand() % ANTAL_VALGMÆND + 1; //Generere et tilfældigt tal, ikke større end antallet af valgmænd
    int i = 0, counter = 0;

    /* Hver stat er vægtet på baggrund af statens antal valgmænd
     * Hver stat er inddelt i intervaller efter valgmænd,
     * eksempelvis har Alabama intervallet 1-9, og Alaska har intervallet 10-12
     * While-loopet undersøger hvilken stat det tilfældigt-genererede tal tilhører.
     */
    while (stat > counter + electors[i]) {
        counter += electors[i];
        i++;
    }
    return i;
}

/* qsort compare funktion til doubles i en struct */
int compare(const void* a, const void *b) {
    /* Typecaster til en candidate_distance pointer, og returner differencen mellem distancefelterne */
    double diff = ((candidate_distance_t*)a)->distance - ((candidate_distance_t*)b)->distance;

    if (diff < 0) return -1;
    if (diff > 0) return 1;
    else return 0;
}

/* Følgende bruges til at lave grafer ved brug af biblioteket, pbPlots, som hjælper til debugging */
void create_graph (double *x_akse, double *y_akse, char prefix[], char title[]) {
    wchar_t wTitle[100];
    mbstowcs(wTitle, title, 100);

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
    series->xsLength = TOTAL_VOTERS;
    series->ys = y_akse;
    series->ysLength = TOTAL_VOTERS;
    series->linearInterpolation = false;
//	series->lineType = L"dotted";
 //   series->lineTypeLength = wcslen(series->lineType);
    series->pointType = L"dots";
    series->pointTypeLength = wcslen(series->pointType);
    series->lineThickness = 1;
    series->color = &color;

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1000;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = wTitle;
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"Person index";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Holdning";
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


   //     StartArenaAllocator();
   // RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
   // /* Bestemmer størrelsen på billedet, og x og y aksen*/
   // DrawScatterPlot(imageRef, 600, 400, x_akse, 6, y_akse, 6, "Error in creating image");
   // size_t length;
   // ByteArray *pngdata = ConvertToPNG(imageRef->image); //Konvertere til png
   // char filename[64];
   // sprintf(filename, "%s.png", prefix); //Sætter .png efter prefixet, for at danne filnavn
   // WriteToFile(pngdata, filename);
   // DeleteImage(imageRef->image);


}
