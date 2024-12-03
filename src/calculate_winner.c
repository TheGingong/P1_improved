#include "static_variables.h"
#include "calculate_winner.h"

int calculate_winner_func(const int* scores) {
    int max_score_index = 0; // Kandidat A initialiserede som vinder af valget
    int max_score = scores[0]; // Kandidat A's score bliver sat som den kandidat med højest score

    /* For loop som gennemløber alle kandidater, og sammenligner score blandt dem.
     * Finder vinder blandt kandidaterne baseret på scoren. */
    for(int i = 1; i < NUMBER_CANDIDATES; i++) {
        if(scores[i] > max_score) { // Tjekker om den nuværende kandidat har højere score end den forrige kandidat
            max_score_index = i; // Sætter den nye kandidat som nuværende vinder
            max_score = scores[i]; // Sætter den nye kandidats vinder score til at være den nuværende største
        }
    }
    return max_score_index; // Returnere vinder indexet for vinder kandidaten
}