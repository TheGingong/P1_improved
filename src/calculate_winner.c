#include "static_variables.h"
#include "calculate_winner.h"

int calculate_winner_i(const int* candidate_points, int return_index) {
    int winner_index = 0; // Kandidat A vinder
    int winner_points = candidate_points[0];

    for(int i = 1; i < NUMBER_CANDIDATES; i++) {
        if(candidate_points[i] > winner_points) {
            winner_points = candidate_points[i];
            winner_index = i;
        }
    }

    /* Hvis return_index er en integer (1), så anses den for at være true, ligesome i en if-statement
     * dermed returneres winner_index for det amerikanske valg, ellers returneres en karakter for borda count */
    return return_index ? winner_index : ('A' + winner_index);
}