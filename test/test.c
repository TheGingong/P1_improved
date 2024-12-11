#include <assert.h>
#include <stdlib.h>
#include "../src/h-filer/realistic_appropriation.h"
#include "../src/h-filer/calculate_winner.h"
#include "../src/h-filer/static_variables.h"
#include "../src/h-filer/valgsystemer.h"
#include "../src/h-filer/convert.h"
#include "../src/h-filer/welfare_score.h"

void test_winner_america();
void test_winner_borda();
void test_convert_america();
void test_calc_winner_func();
void test_convert_borda();
FILE* open_file(const char* file_path);

int main(void) {
    test_winner_america();
    test_winner_borda();
    test_calc_winner_func();
    test_convert_borda();
    test_convert_america();
    return 0;
}

/* Testing af om den rigtige kandidat bliver valgt */
void test_winner_america() {
    /* Arrange */
    FILE *test_file1 = open_file("test/test1.txt");
    FILE *test_file2 = open_file("test/test2.txt");
    FILE *test_file3 = open_file("test/test3.txt");

    /* Act */
    char winner1 = america(test_file1);
    char winner2 = america(test_file2);
    char winner3 = america(test_file3);
    fclose(test_file1);
    fclose(test_file2);
    fclose(test_file3);

    /* Assert */
    assert(winner1 == 'D');
    assert(winner2 == 'C');
    assert(winner3 == 'E');
}

/* Testing af Borda */
void test_winner_borda() {
    /* Arrange */
    FILE *test_file = open_file("test/test1.txt");

    /* Act */
    char winner = borda_count(test_file);
    fclose(test_file);

    /* Assert */
    assert(winner == 'D');
}

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
void test_convert_borda() {
    /* Act */
    FILE *test_file = open_file("test/test1.txt");

    /* Initialisering af arrays som bruges af convert borda */
    int voter_preference[NUMBER_CANDIDATES] = {0};
    int expected_array_output[NUMBER_CANDIDATES] = {3,2,4,0,1}; // Dette array bruges til at tjekke om output er korrekt

    /* Arrange */
    convert_borda(voter_preference, test_file);
    fclose(test_file);

    /* Assert */
    for (int i = 0; i < 5; i++) {
        assert(voter_preference[i] == expected_array_output[i]);
    }
}

/* Test af convert america */
void test_convert_america() {
    /* Arrange */
    FILE *test_file1 = open_file("test/test1.txt");
    FILE *test_file2 = open_file("test/test2.txt");
    FILE *test_file3 = open_file("test/test3.txt");

    /* Act */
    struct person test1 = convert_america(test_file1);
    struct person test2 = convert_america(test_file2);
    struct person test3 = convert_america(test_file3);
    fclose(test_file1);
    fclose(test_file2);
    fclose(test_file3);

    /* Assert */
    assert(test1.stat == 40 && test1.pref == 3);
    assert(test2.stat == 0 && test2.pref == 3);
    assert(test3.stat == 0 && test3.pref == 2);

}

/* Test af welfare score */

/* Åbner en fil igennem  */
FILE* open_file(const char* file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    return file;
}