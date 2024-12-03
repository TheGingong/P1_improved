#include "static_variables.h"
#include "calculate_winner.h"

int calculate_winner_func(const int* array) {
    int winner_index = 0; // Kandidat A vinder (0 = A)
    int winner_points = array[0]; // (A)

    for(int i = 1; i < NUMBER_CANDIDATES; i++) {
        if(array[i] > winner_points) {
            winner_points = array[i];
            winner_index = i;
        }
    }
    return winner_index;
}