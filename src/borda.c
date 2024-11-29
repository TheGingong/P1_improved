#include "borda.h"
#include <stdio.h>
#include <stdlib.h>
#include "convert.h"
#include "static_variables.h"

/* Funktion borda_count initialiserer de nødvendige arrays, samt tildeler dem en start værdi */
char borda_count(FILE *file) {
    /* Initialiserer arrays */
    char candidate[NUMBER_CANDIDATES]; // Alle mulige kandidater sorteret fra a-z
    int candidate_points[NUMBER_CANDIDATES]; // Gemmer point for hver kandidat
    char voter_preference[NUMBER_CANDIDATES]; // Information om én vælger præference

    /* Indlæser værdier i vælger og resultat */
    for (int i = 0; i < NUMBER_CANDIDATES;i++) {
        candidate[i] = 'A' + i; // Indlæser char a-z alt efter antal kandidater
        candidate_points[i] = 0; // Tildeler 0 point til hver kandidat
    }
    /*Funktions kald der udfører selve optællingen, og annoncerer vinderen*/
    point_counting(voter_preference, candidate_points, file); // Stemme optællings funktion
    char candidate_winner = winner(candidate_points,candidate); // Udpeger den/de kandidater med flest point
    return candidate_winner;
}

/* Funktion point_counting, henter én vælger præference, og uddeler point til kandidaterne på baggrund præferencen */
void point_counting(char* voter_preference, int* candidate_points, FILE *file) {
    int linje = 0; // Optæller der specificerer hvilken linje i convert_borda som betragtes

    int x = 1;
    while (x != 0) { // While fortsætter mens tekstfilen stadig har stemmer der skal optælles
        x = convert_borda(voter_preference, file);
        linje++; // Optæller bliver talt op
        for (int i = 0, j = NUMBER_CANDIDATES; i < NUMBER_CANDIDATES; i++, j--) {
            int k = voter_preference[i] - 'A'; // Udregner indeks som point skal tildeles, indekset gemmes i variablen k
            candidate_points[k] += j; // Tildeler j antal point (j bliver talt ned for hver gennemløb)
        }
    }
}

/* Funktionen winner fastlægger og printer den eller de kandidater med flest point */
char winner(const int* candidate_points, const char* candidate) {
    int current_winner = 0; // Holder styr på den hidtil højeste pointscore

    /* Point score for hver kandidat betragtet i rækkefølge a-z. Den højeste point score gemmes i nuværende_winner */
    for (int i = 0; i < NUMBER_CANDIDATES;i++) {
        if (current_winner <= candidate_points[i]) {
            current_winner = candidate_points[i];
        }
    }
    /* Printer alle kandidater samt deres point */
   // for (int i = 0; i < NUMBER_CANDIDATES; i++) {
   //     printf("%c : %d\n", candidate[i], candidate_points[i]);
   // }
    /* returnere kandidat med højeste pointscore */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (current_winner == candidate_points[i]) { // Tjekker om en kandidats point er lig med det højeste antal scorede point
            return candidate[i];
        }
    }
}
