#include <stdio.h>

#define NUMBER_CANDIDATES 2
#define MAX_LINE_LENGTH 256
#define NUMBER_SIMULATIONS 500
#define TOTAL_VOTERS 20000

/* Prototyper */
FILE* open_file(const char* file_path); // Prototype til main.c
void simulation(int run_times);