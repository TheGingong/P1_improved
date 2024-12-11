#include <assert.h>
#include <stdlib.h>
#include "./h-filer/realistic_appropriation.h"
#include "./h-filer/calculate_winner.h"
#include "./h-filer/static_variables.h"
#include "./h-filer/valgsystemer.h"
#include "./h-filer/convert.h"
#include "./h-filer/welfare_score.h"

void test_winner_america();
void test_convert_america();
void test_calc_winner_func();

int main(void) {
    test_winner_america();
    test_calc_winner_func();
    test_convert_america();
    return 0;
}

/* Testing af om den rigtige kandidat bliver valgt */
void test_winner_america() {
    /* Arrange */
    FILE *test_file = fopen("test/test.txt", "r");

    if (test_file == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    /* Act */
    char winner = america(test_file);

    /* Assert */
    assert(winner == 'D');
    fclose(test_file);
}

/* Testing af Borda */

/* Test af calculate winner */
void test_calc_winner_func(){
    // Arrange
    /* 3 cases med forskellige indeks' som vinder */
    int scores1[NUMBER_CANDIDATES] = {10, 20, 30, 40, 50}; // Vinder indeks 4
    int scores2[NUMBER_CANDIDATES] = {50, 40, 30, 20, 10}; // Vinder indeks 0
    int scores3[NUMBER_CANDIDATES] = {20, 30, 40, 10, 50}; // Vinder indeks 4

    // Act
    /* Kører calculate_winner_func på de forskellige arrays */
    int winner1 = calculate_winner_func(scores1);
    int winner2 = calculate_winner_func(scores2);
    int winner3 = calculate_winner_func(scores3);

    // Assert
    /* Tjek hvorvidt output er rigtigt */
    assert(winner1 == 4); // Test case 1
    assert(winner2 == 0); // Test case 2
    assert(winner3 == 4); // Test case 3
    }


/* Test af convert borda */

/* Test af convert america */
void test_convert_america() {
    /* Arrange */
    FILE *test_convert_america = fopen("test/test.txt", "r");

    if (test_convert_america == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }

    /* Act */
    struct person test = convert_america(test_convert_america);

    /* Assert */
    assert(test.stat == 40 && test.pref == 3);
    fclose(test_convert_america);
}



/* Test af welfare score */