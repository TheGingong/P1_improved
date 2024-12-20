#include <stdio.h>

/* Stuct person defineres som bruges af convert_america() og america()
 * Består af en stat og en præference per vælger */
struct person {
    int stat;
    int pref;
};

/* Prototyper */
struct person convert_america(FILE *file);
int convert_borda(int* array_pref, FILE *file);