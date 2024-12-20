#include <stdio.h>
#define MAX_LINE_LENGTH 256
#define NUMBER_CANDIDATES 5
#define NUMBER_SIMULATIONS 500
#define TOTAL_VOTERS 10000
#define DIMENSIONS 5
#define CLUSTERS 5
#define PRINT_GRAPH 0 // Sæt til 0, hvis der ikke skal printes en graf

/* Kun én af de følgende kan være 1 på samme tid */
#define RUN_REJECTION 1 // Sæt til 1 for at køre stemme generering med rejection sampling
#define RUN_BOXMULLER 0 // Sæt til 1 for at køre stemme generering med box muller

#define CHOSEN_FILE "text-files/spatial-file.txt"

/* Prototyper */
FILE* open_file(const char* file_path); // Prototype til main.c
void simulation(int run_times);