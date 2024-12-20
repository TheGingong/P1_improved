#include <stdio.h>
#include <time.h>
#include "../h-filer/valgsystemer.h"
#include "../h-filer/realistic_appropriation.h"
#include "math.h"
#include "../pbPlots/pbPlots.h"
#include "../pbPlots/supportLib.h"
#include <stdint.h>

void generate_data() {
    /* Initiering */
    FILE* generate_data_file = fopen("text-files/spatial-file.txt", "w");

    if (generate_data_file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
        exit(EXIT_FAILURE);
    }

    double total_model_array[TOTAL_VOTERS][DIMENSIONS]; // Array der består af alle vælgeres holdninger
    cluster_t cluster_array[CLUSTERS]; // Array af structs som beskriver normalfordelingers variable

    /* Kør funktion */
    assemble_gauss(cluster_array, total_model_array, generate_data_file);
    fclose(generate_data_file);
}

/* Funktion der kører andre underordnede funktioner.
 * Formålet er, at samle alle elementerne, og skrive resultaterne i tekstfilen */
void assemble_gauss (cluster_t cluster_array[CLUSTERS], double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], FILE* file) {
    double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS]; // Array der består af alle kandidaternes holdninger

    /* Her genereres vælgeropinioner for hver dimension */
    for (int i = 0; i < DIMENSIONS ;i++) {
        make_cluster_array(cluster_array);

        /* If statement, så man kan køre rejection sampling eller Box Muller baseret på værdier i static_variables.h */
        if (RUN_REJECTION) {
            /* Genererer kandidat på baggrund af de samme clusters der bliver brugt til generering af stemmer.
             * Ved tilfælde af flere kandidater end clusters, vil clusters blive gentaget */
            for (int k = 0; k < NUMBER_CANDIDATES; k++) {
                candidates_coordinates[k][i] = generate_normal_using_rejection(cluster_array[k%CLUSTERS]);
            }

            /* Funktionen kaldes den rette mængde gange (antal klynger * antal dimensioner) */
            for (int h = 0; h < CLUSTERS; h++) {
                generate_one_gauss(cluster_array[h], gauss_2d_array, i, h);
            }
        }
        /* Følger samme struktur som ovenstående kørsel af rejection sampling,
         * men erstatter med passende funktioner for Box-Muller metoden */
        else if (RUN_BOXMULLER) {
            for (int k = 0; k < NUMBER_CANDIDATES; k++) {
                candidates_coordinates[k][i] = generate_normal_using_box_muller(cluster_array[k%CLUSTERS]);
            }

            for (int h = 0; h < CLUSTERS; h++) {
                generate_one_muller(cluster_array[h], gauss_2d_array, i, h);
            }
        }
    }

    /* If-statement der printer grafer baseret på variabel givet i static_variables.h
     * Grafen printes for én dimension, uanset samlet antal dimensioner */
    if (PRINT_GRAPH) {
        const int dim = 0; // Vælg hvilen dimension som skal printes.
        double tal_x[TOTAL_VOTERS], tal_y[TOTAL_VOTERS],
        tal_x2[NUMBER_CANDIDATES], tal_y2[NUMBER_CANDIDATES];

        /* Arrayet tal_x indeholder alle heltal fra 0 til TOTAL_VOTERS - 1
         * Arrayet tal_y indeholder alle individers holdninger til dimensionen 'dim' */
        for (int z = 0; z < TOTAL_VOTERS; z++) {
            tal_x[z] = z;
            tal_y[z] = gauss_2d_array[z][dim];
        }

        /* Arrayet tal_x2 placere kandidaten midt i det cluster de er genereret fra på x-aksen
         * Arrayet tal_y2 indeholder alle kandidaters holdninger til dimensionen 'dim' */
        for (int z = 0; z < NUMBER_CANDIDATES; z++) {
            tal_x2[z] = (TOTAL_VOTERS / CLUSTERS) * (z % CLUSTERS +1) - (TOTAL_VOTERS / CLUSTERS) /2;
            tal_y2[z] = candidates_coordinates[z][dim];
        }

        /* Sætter graf-titlen til den tilsvarende metode */
        char title[16];
        if (RUN_REJECTION) {
             sprintf(title, "Rejection Sampling");
        } else {
            sprintf(title, "Box-Muller");
        }

        /* Funktion for at generere graf køres */
        create_graph(tal_x, tal_y, tal_x2, tal_y2, "Graf", title);
        FreeAllocations();
    }

    double min_length = 0;
    double max_length = 0;

    /* Kører spatial funktionen for hver voter, der genererer en præference baseret rangering */
    for (int i = 0; i < TOTAL_VOTERS; i++) { // Bruger spacial stemmemodel for at skabe vælgerpræferencer
        spatial(gauss_2d_array[i], candidates_coordinates, file, &max_length, &min_length);
    }
}

/* Funktion der opsætter en array af structs (cluster_t) */
void make_cluster_array (cluster_t cluster_array[CLUSTERS]) {
    for (int i = 0; i < CLUSTERS; i++) {
        /* Sætter middelværdien til en tilfældig værdi ud fra empirical rule med middelværdi 0 og spredning 1 */
        cluster_array[i].mean_cluster = (0 - 3 * 1) + (double) rand() / RAND_MAX * ((0 + 3 * 1) - (0 - 3 * 1));

        /* Sætter spredningen til en tilfældig værdi fra 0 til 1 (spredning kan ikke være negativ) */
        cluster_array[i].spread_cluster = (double) rand() / RAND_MAX * (MAX_SPREAD - MIN_SPREAD) + MIN_SPREAD;

        /* Fordeler vælgere uniformt på mængden af normalfordelinger */
        cluster_array[i].voters_cluster = (double)TOTAL_VOTERS / (double)CLUSTERS;
    }
}

/* Funktion der genererer tilfældige stemmer for én vælger i den j'te dimension */
void generate_one_gauss(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {
    /* Funktionen generate_normal_using_rejection bruges, og tilegner opinioner for vælgere i den gældende dimension */
    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
            double value = generate_normal_using_rejection(cluster_n);
            gauss_2d_array[i][dimension_j] = value;
    }
}

/* Funktion som generer et koordinat i én dimension for én stemme */
double generate_normal_using_rejection(cluster_t cluster_n) {
    double sample, density_at_sample, random_value;
    double min_sample = cluster_n.mean_cluster - 3 * cluster_n.spread_cluster;
    double max_sample = cluster_n.mean_cluster + 3 * cluster_n.spread_cluster;

    /* Do-while, som finder en tilfældig værdi (sample), og sammenligner med en anden tilfældig værdi (random_value) */
    do { // Funktionen kører indtil der findes en acceptabel værdi (rejection sampling)
        /* Genererer et punkt mellem -3 spredninger og 3 spredninger */
        sample = (double) rand() / RAND_MAX * (max_sample - min_sample) + min_sample;

        /* Tætheden findes for sample-punktet */
        density_at_sample = gaussian_density(cluster_n, sample);

        /* Finder en tilfældig værdi mellem 0, og tætheden for middelværdien */
        random_value = (double) rand() / RAND_MAX * gaussian_density(cluster_n, cluster_n.mean_cluster);
    } while (random_value > density_at_sample); // Tjekker, om sample er større end den tilfældige værdi, accepterer hvis den er

    return sample; // Returnerer sample-værdien
}

/* Funktion der kan generere sandsynligheden for ét udfald i en normalfordeling (cluster) */
double gaussian_density (cluster_t cluster_n, double voter_x) {
    /* Følgende er tæthedsfunktionen (Gauss-funktionen) */
    return 1 / ( sqrt(2 * M_PI) * cluster_n.spread_cluster )
           * exp(-0.5 * pow((voter_x - cluster_n.mean_cluster) / cluster_n.spread_cluster, 2));
}

/* Box Muller algoritme der ud fra 2 uniformt-fordelte tal genererer 2 normalfordelte tal */
void box_muller(double *z1, double *z2) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;

    /* Fejlhåndtering så vi ikke står med ln(0), hviklet ikke findes */
    if (u1 == 0.0) {
        u1 = 0.0001;
    }

    *z1 = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
    *z2 = sqrt(-2 * log(u1)) * sin(2 * M_PI * u2);
}


/* Funktion der benytter spredning og middelværdi til at ændre det normalfordelte tal */
double generate_normal_using_box_muller(cluster_t cluster_n) {
    static int use_last = 0;
    static double z1, z2;

    if (use_last) { // Hvis vi har et tidligere ubenyttet udregnet tal, benyt det
        use_last = 0;
        return cluster_n.mean_cluster + z2 * cluster_n.spread_cluster; // + mean og * spread
    }

    box_muller(&z1, &z2); // Generer nye normalfordelte tal
    use_last = 1;
    return cluster_n.mean_cluster + z1 * cluster_n.spread_cluster; // + mean og * spread
}

/* Følger den samme struktur som "generate_one_gauss", bare med Box Muller algoritmen */
void generate_one_muller(cluster_t cluster_n, double gauss_2d_array[TOTAL_VOTERS][DIMENSIONS], int dimension_j, int h) {
    /* Funktionen generate_normal_using_muller bruges, og tilegner opinioner for vælgere i den gældende dimension */
    for (int i = 0 + (h * cluster_n.voters_cluster); i < cluster_n.voters_cluster+(h*cluster_n.voters_cluster); i++) {
        double value = generate_normal_using_box_muller(cluster_n);
        gauss_2d_array[i][dimension_j] = value;
    }
}

/* Funktion som tager vælgeres rangerings-koordinater, og beregner længden fra dem til kandidaterne
 * den kandidat der ligger tættest, er den vælgeren stemmer på for hver dimension */
void spatial(double koords[DIMENSIONS], double candidates_coordinates[NUMBER_CANDIDATES][DIMENSIONS], FILE* file, double* max_length, double* min_length) {
    candidate_distance_t cand_distances[NUMBER_CANDIDATES]; // Array af candidate_distance_t structs

    /* Loop der itererer over antal kandidater */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        double length = 0;

        for (int j = 0; j < DIMENSIONS; j++) { // Loop der itererer over antal dimensioner
            length += pow((koords[j] - candidates_coordinates[i][j]), 2); // Euklids afstandsformel (summerer over flere dimensioner)
        }

        cand_distances[i].id = i; // Tilegning af indeks til den korresponderende vælger i struct-arrayet
        cand_distances[i].distance = sqrt(length) ; // Tilegning af længde fra vælger til kandidat på korresponderende plads i struct-array

        /* max_length og min_length for vælgere til kandidater findes, for senere at kunne normalisere afstande */
        if (cand_distances[i].distance > *max_length) {
            *max_length = cand_distances[i].distance;
        }
        if (cand_distances[i].distance < *min_length) {
            *min_length = cand_distances[i].distance;
        }
    }

    /* Sorterer således, at den kandidat der er kortest til fra vælger, står først */
    qsort(cand_distances, NUMBER_CANDIDATES, sizeof(candidate_distance_t), compare);

    /* Der initieres variabler til brug for velfærds-beregning */
    double welfare = 0;

    /* Printer stat til filen baseret på fordeling af valgmænd */
    fprintf(file, "%d(", create_state()); // Printer stat og '('

    /* Udregner velfærd baseret på distance, og printer dette til tekstfilen med en stat (0-50) foran */
    for (int i = 0; i< NUMBER_CANDIDATES; i++) {
        welfare = 1 - (cand_distances[i].distance- *min_length) / (*max_length - *min_length); // Normaliserer distance så den er mellem 0 til 1

        fprintf(file, "%c%.3lf",'A' + cand_distances[i].id, welfare); // Printer værdierne til tekstfilen
        if (i < NUMBER_CANDIDATES-1) {
            fprintf(file, " "); // Printer mellemrum efter hver nytte, på nær den sidste
        }
    }

    fprintf(file, ")\n"); // Printer ')' og newline
}

/* Genererer en vægtet tilfældig stemme,
 * med hyppigere udfald for en stat med flere valgmænd */
int create_state() {
    int stat = rand() % ANTAL_VALGMÆND + 1; //Genererer et tilfældigt tal, ikke større end antallet af valgmænd
    int i = 0, counter = 0;

    /* Hver stat er vægtet på baggrund af statens antal valgmænd
     * Hver stat er inddelt i intervaller efter valgmænd,
     * eksempelvis har Alabama intervallet 1-9, og Alaska har intervallet 10-12
     * While-loopet undersøger hvilken stat det tilfældigt-genererede tal tilhører. */
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
void create_graph (double *x_akse, double *y_akse, double *x_akse2, double *y_akse2, char prefix[], char title[]) {
    wchar_t wTitle[100];
    mbstowcs(wTitle, title, 100);
    _Bool success;
    StringReference *errorMessage;
    StartArenaAllocator();

    /* Indstillinger til dataserien for vælgere */
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = x_akse;
    series->xsLength = TOTAL_VOTERS;
    series->ys = y_akse;
    series->ysLength = TOTAL_VOTERS;
    series->linearInterpolation = false;
    series->pointType = L"dots";
    series->pointTypeLength = wcslen(series->pointType);
    series->lineThickness = 1;
    series->color = CreateRGBColor(1,0,0);

    /* Indstillinger til dataserien for kandidater */
    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = x_akse2;
    series2->xsLength = NUMBER_CANDIDATES;
    series2->ys = y_akse2;
    series2->ysLength = NUMBER_CANDIDATES;
    series2->linearInterpolation = false;
    series2->pointType = L"dots";
    series2->pointTypeLength = wcslen(series->pointType);
    series2->lineThickness = 1;
    series2->color = CreateRGBColor(0, 0, 1);

    /* Indstillinger for genereringen af grafen */
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1000;
    settings->height = 600;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = wTitle;
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"Personindex";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"Holdning";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s [] = {series, series2};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 2;

    /* Genereringen af grafen */
    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    errorMessage = (StringReference *)malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(canvasReference, settings, errorMessage);

    if (success) {
        /* Konvertering til png, med prefixet som navn */
        ByteArray *pngdata = ConvertToPNG(canvasReference->image);
        char filename[64];
        sprintf(filename, "%s.png", prefix); //Sætter .png efter prefixet, for at danne filnavn
        WriteToFile(pngdata, filename);
        DeleteImage(canvasReference->image);
    } else {
        fprintf(stderr, "Error: ");
        for(int i = 0; i < errorMessage->stringLength; i++) {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }
}