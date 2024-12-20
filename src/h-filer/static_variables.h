#include <stdio.h>
#define NUMBER_CANDIDATES 5 // Angiver antallet af kandidater, som genereres.
#define NUMBER_SIMULATIONS 10 // Angiver antallet af simulationer.
#define TOTAL_VOTERS 10000 // Angiver antallet af vælgere for hver simulation.
#define DIMENSIONS 5 // Angiver antallet af dimensioner, som repræsentere en mærkesag.
#define CLUSTERS 5 // Angiver antallet af klynger for hver dimension.
#define MAX_LINE_LENGTH 256 // Angiver den maksimale længde på en linje i stemmegenereringsfilen.

/* Kun én af de følgende, kan sættes til 1 på samme tid */
#define RUN_REJECTION 1 // Sæt til 1 for at køre stemme generering med rejection sampling
#define RUN_BOXMULLER 0 // Sæt til 1 for at køre stemme generering med box muller

/* Angiver om der skal printes en graf, for én dimension.
 * Valget af dimension kan ændres i realistic_appropriation.c.
 * Hvis der køres mere end én simulation, printes kun den sidste. */
#define PRINT_GRAPH 0

/* Angiver hvilken fil simulationerne læses fra, så skal derfor følge stemmegenereringsmetoden.
 * Ved spatial voting vælges "text-files/spatial-file.txt".
 * Ved impartial voting vælges "text-files/impartial-file.txt". */
#define CHOSEN_FILE "text-files/spatial-file.txt"

/* Angiver hvilken stemmegenererinsmodel som skal benyttes.
 * Hvis spatial voting skal benyttes, angives generate_spatial_data.
 * Hvis impartial voting skal benyttes, angives generate_impartial_data(TOTAL_VOTERS). */
#define GENERATE_DATA generate_spatial_data(TOTAL_VOTERS);