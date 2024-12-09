#include "../h-filer/borda.h"
#include "../h-filer/convert.h"
#include "../h-filer/calculate_winner.h"
#include "../h-filer/static_variables.h"

/* Funktion borda_count initialiserer de nødvendige arrays, samt tildeler dem en start værdi */
char borda_count(FILE *file) {
    /* Initialiserer arrays */
    int candidate_points[NUMBER_CANDIDATES] = {0}; // Gemmer point for hver kandidat
    int voter_preference[NUMBER_CANDIDATES] = {0}; // Information om én vælger præference

    /* Funktions kald der udfører selve optællingen, og annoncerer vinderen */
    point_counting(voter_preference, candidate_points, file); // Stemme optællings funktion

    char candidate_winner = calculate_winner_func(candidate_points); // Udpeger den/de kandidater med flest point
    return 'A' + candidate_winner; // Returnere den rigtige kandidat ved brug af index fra calculate_winner_func
}

/* Funktion point_counting, henter én vælger præference, og uddeler point til kandidaterne på baggrund præferencen */
void point_counting(int voter_preference[], int* candidate_points, FILE *file) {
    int candidate_index = 0;
    while (convert_borda(voter_preference, file) != 0) { // While fortsætter mens tekstfilen stadig har stemmer der skal optælles
        for (int i = 0, points = NUMBER_CANDIDATES; i < NUMBER_CANDIDATES; i++, points--) {
            candidate_index = voter_preference[i]; // Udregner indeks som point skal tildeles, indekset gemmes i variablen k
            candidate_points[candidate_index] += points; // Tildeler j antal point (j bliver talt ned for hver gennemløb)
        }
    }
}