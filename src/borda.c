#include "borda.h"
#include <stdio.h>
#include "convert.h"
#include "static_variables.h"

/* Funktion borda_count initialiserer de nødvendige arrays, samt tildeler dem en start værdi */
char borda_count(const int number_of_candidates) {
    /* Initialiserer arrays */
    char candidate[number_of_candidates]; // Alle mulige kandidater sorteret fra a-z
    int candidate_points[number_of_candidates]; // Gemmer point for hver kandidat
    char voter_preference[number_of_candidates]; // Information om én vælger præference

    /* Indlæser værdier i vælger og resultat */
    for (int i = 0; i < number_of_candidates;i++) {
        candidate[i] = 'A' + i; // Indlæser char a-z alt efter antal kandidater
        candidate_points[i] = 0; // Tildeler 0 point til hver kandidat
    }
    /*Funktions kald der udfører selve optællingen, og annoncerer vinderen*/
    point_counting(voter_preference, number_of_candidates, candidate_points); // Stemme optællings funktion
    char candidate_winner = winner(candidate_points,candidate, number_of_candidates); // Udpeger den/de kandidater med flest point
    return candidate_winner;
}

/* Funktion point_counting, henter én vælger præference, og uddeler point til kandidaterne på baggrund præferencen */
void point_counting(char* voter_preference, const int number_of_candidates, int* candidate_points) {
    int linje = 0; // Optæller der specificerer hvilken linje i convert_borda som betragtes

    while (convert_borda(linje, voter_preference) != 0) { // While fortsætter mens tekstfilen stadig har stemmer der skal optælles
        convert_borda(linje, voter_preference); /* convert_borda konverterer data gemt i
                                                 * tekstfilen til et array, repræsenteret af voter_preference */
        linje++; // Optæller bliver talt op
        for (int i = 0, j = number_of_candidates; i < number_of_candidates; i++, j--) {
            int k = voter_preference[i] - 'A'; // Udregner indeks som point skal tildeles, indekset gemmes i variablen k
            candidate_points[k] += j; // Tildeler j antal point (j bliver talt ned for hver gennemløb)
        }
    }
}

/* Funktionen winner fastlægger og printer den eller de kandidater med flest point */
char winner(const int* candidate_points, const char* candidate, const int number_of_candidates) {
    int current_winner = 0; // Holder styr på den hidtil højeste pointscore

    /* Point score for hver kandidat betragtet i rækkefølge a-z. Den højeste point score gemmes i nuværende_winner */
    for (int i = 0; i < number_of_candidates;i++) {
        if (current_winner <= candidate_points[i]) {
            current_winner = candidate_points[i];
        }
    }
    /* Printer alle kandidater samt deres point */
   // for (int i = 0; i < number_of_candidates; i++) {
   //     printf("%c : %d\n", candidate[i], candidate_points[i]);
   // }
    /* returnere kandidat med højeste pointscore */
    for (int i = 0; i < number_of_candidates; i++) {
        if (current_winner == candidate_points[i]) { // Tjekker om en kandidats point er lig med det højeste antal scorede point
            return candidate[i];
        }
    }
}
