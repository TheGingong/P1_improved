#include <stdio.h>

#define NUMBER_CANDIDATES 10
#define MAX_LINE_LENGTH 256

/* Prototyper */
FILE* open_file(const char* file_path); // Prototype til main.c
void simulation(int run_times);