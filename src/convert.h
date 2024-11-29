#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 40

struct person {
    int stat;
    int pref;
};

struct person convert_america(int line_person);
int Lav_tal_om_for_soren(int tal);
int convert_borda(int line_person, char* array_pref);