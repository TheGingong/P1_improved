#include "borda.h"
#include <stdio.h>
#include "calculate_winner.h"
#include "convert.h"
#include "static_variables.h"

/* Funktion borda_count initialiserer de nødvendige arrays, samt tildeler dem en start værdi */
char borda_count(FILE *file) {
    /* Initialiserer arrays */
    int candidate_points[NUMBER_CANDIDATES] = {0}; // Gemmer point for hver kandidat
    int voter_preference[NUMBER_CANDIDATES] = {0}; // Information om én vælger præference

    /*Funktions kald der udfører selve optællingen, og annoncerer vinderen*/
    point_counting(voter_preference,  candidate_points, file); // Stemme optællings funktion
  
    char candidate_winner = calculate_winner_i(candidate_points, 0); // Udpeger den/de kandidater med flest point
  
    return candidate_winner;
}

/* Funktion point_counting, henter én vælger præference, og uddeler point til kandidaterne på baggrund præferencen */
void point_counting(int* voter_preference, int* candidate_points, FILE *file) {
    int x = 1;
    while (x != 0) { // While fortsætter mens tekstfilen stadig har stemmer der skal optælles
        x = convert_borda(voter_preference, file);
        
        for (int i = 0, j = NUMBER_CANDIDATES; i < NUMBER_CANDIDATES; i++, j--) {
            int k = voter_preference[i]; // Udregner indeks som point skal tildeles, indekset gemmes i variablen k
            candidate_points[k] += j; // Tildeler j antal point (j bliver talt ned for hver gennemløb)
        }
    }
}