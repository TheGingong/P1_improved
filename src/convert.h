#include <stdio.h>
struct person {
    int stat;
    int pref;
};

struct person convert_america(FILE *file);
int convert_borda(int* array_pref, FILE *file);