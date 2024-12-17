#include <stdio.h>
#define MAX_LINE_LENGTH 256
#define NUMBER_CANDIDATES 5
#define NUMBER_SIMULATIONS 1000
#define TOTAL_VOTERS 5000
#define DIMENSIONS 1
#define CLUSTERS 5
#define PRINT_GRAPH 0 // Sæt til 0, hvis der ikke skal printes en graf


/* Prototyper */
FILE* open_file(const char* file_path); // Prototype til main.c
void simulation(int run_times);