#include <stdlib.h>

#include "../h-filer/valgsystemer.h"
#include "../h-filer/convert.h"
#include "../h-filer/calculate_winner.h"
#include "../h-filer/static_variables.h"

/* Funktion borda_count initialiserer de nødvendige arrays, samt tildeler dem en start værdi */
char borda_count() {
    FILE *borda_file = fopen("text-files/test-tekstil.txt", "r"); // Filen med stemmer åbnes i read mode.

    if (borda_file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
        exit(EXIT_FAILURE);
    }

    /* Initialiserer arrays */
    int candidate_points[NUMBER_CANDIDATES] = {0}; // Gemmer point for hver kandidat
    int voter_preference[NUMBER_CANDIDATES] = {0}; // Information om én vælger præference
    int candidate_index = 0;

    /* algoritme der udfører selve optællingen */
    while (convert_borda(voter_preference, borda_file) != 0) { // While fortsætter mens tekstfilen stadig har stemmer der skal optælles
        for (int i = 0, points = NUMBER_CANDIDATES; i < NUMBER_CANDIDATES; i++, points--) {
            candidate_index = voter_preference[i]; // Udregner indeks som point skal tildeles, indekset gemmes i variablen k
            candidate_points[candidate_index] += points; // Tildeler j antal point (j bliver talt ned for hver gennemløb)
        }
    }

    char candidate_winner = calculate_winner_func(candidate_points); // Udpeger den/de kandidater med flest point

    fclose(borda_file);

    return 'A' + candidate_winner; // Returnere den rigtige kandidat ved brug af index fra calculate_winner_func
}