#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 40

struct person {
    int stat;
    int pref;
};

struct person convert_america(FILE *file);
int convert_borda(int* array_pref, FILE *file);
double welfare_calculator(char winner);