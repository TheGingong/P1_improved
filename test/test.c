#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "../src/h-filer/realistic_appropriation.h"
#include "../src/h-filer/calculate_winner.h"
#include "../src/h-filer/static_variables.h"
#include "../src/h-filer/valgsystemer.h"
#include "../src/h-filer/convert.h"
#include "../src/h-filer/welfare_score.h"
#include "../src/h-filer/main.h"

/* Prototyper */
void test_winner_america();
void test_winner_borda();
void test_convert_america();
void test_calc_winner_func();
void test_convert_borda();
void test_SUE();
int is_almost_equal(double actual, double expected);

int main(void) {
    /* Tester funktioner */
    test_winner_america();
    test_winner_borda();
    test_calc_winner_func();
    test_convert_borda();
    test_convert_america();
    test_SUE();

    printf("All tests passed.\n");

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
    assert(winner1 == 'A'); // Test case 1
    assert(winner2 == 'C'); // Test case 2
    assert(winner3 == 'E'); // Test case 3
}

/* Testing af Borda */
void test_winner_borda() {
    /* Arrange */
    FILE *test_file1 = open_file("test/test1.txt");
    FILE *test_file2 = open_file("test/test2.txt");
    FILE *test_file3 = open_file("test/test3.txt");

    /* Act */
    char winner1 = borda_count(test_file1);
    char winner2 = borda_count(test_file2);
    char winner3 = borda_count(test_file3);
    fclose(test_file1);
    fclose(test_file2);
    fclose(test_file3);

    /* Assert */
    assert(winner1 == 'D');
    assert(winner2 == 'B');
    assert(winner3 == 'D');
}

/* Test af calculate winner */
void test_calc_winner_func(){
    /* Arrange */
    /* 3 cases med forskellige indeks' som vinder */
    int scores1[NUMBER_CANDIDATES] = {10, 20, 30, 40, 50}; // Vinder indeks 4
    int scores2[NUMBER_CANDIDATES] = {50, 40, 30, 20, 10}; // Vinder indeks 0
    int scores3[NUMBER_CANDIDATES] = {20, 50, 40, 10, 30}; // Vinder indeks 4

    /* Act */
    /* Kører calculate_winner_func på de forskellige arrays */
    int winner1 = calculate_winner_func(scores1);
    int winner2 = calculate_winner_func(scores2);
    int winner3 = calculate_winner_func(scores3);

    /* Assert */
    /* Tjek hvorvidt output er rigtigt */
    assert(winner1 == 4); // Test case 1
    assert(winner2 == 0); // Test case 2
    assert(winner3 == 1); // Test case 3
}

/* Test af convert borda */
void test_convert_borda() {
    /* Act */
    FILE *test_file1 = open_file("test/test1.txt");
    FILE *test_file2 = open_file("test/test2.txt");
    FILE *test_file3 = open_file("test/test3.txt");

    /* Initialisering af arrays som bruges af convert borda */
    int voter_preference_1[NUMBER_CANDIDATES] = {0};
    int expected_array_output_1[NUMBER_CANDIDATES] = {3,2,4,0,1}; // Dette array bruges til at tjekke om output er korrekt

    int voter_preference_2[NUMBER_CANDIDATES] = {0};
    int expected_array_output_2[NUMBER_CANDIDATES] = {3,2,1,4,0}; // Dette array bruges til at tjekke om output er korrekt

    int voter_preference_3[NUMBER_CANDIDATES] = {0};
    int expected_array_output_3[NUMBER_CANDIDATES] = {2,0,4,1,3}; // Dette array bruges til at tjekke om output er korrekt

    /* Arrange */
    /* Første linje i filen */
    convert_borda(voter_preference_1, test_file1);
    convert_borda(voter_preference_2, test_file2);
    convert_borda(voter_preference_3, test_file3);
    fclose(test_file1);
    fclose(test_file2);
    fclose(test_file3);

    /* Assert */
    for (int i = 0; i < 5; i++) {
        assert(voter_preference_1[i] == expected_array_output_1[i]);
    }

    for (int i = 0; i < 5; i++) {
        assert(voter_preference_2[i] == expected_array_output_2[i]);
    }

    for (int i = 0; i < 5; i++) {
        assert(voter_preference_3[i] == expected_array_output_3[i]);
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
void test_SUE() {
    /* Arrange */
    FILE *test_file = open_file("test/test4.txt");
    candidate_welfare test_candidates[NUMBER_CANDIDATES] = {0};

    /* Act */
    read_candidate_welfare(test_candidates, test_file);
    fclose(test_file);

    /* Assert */
    /* Test case 1 */
    assert(test_candidates[0].candidate == 'A');
    assert(is_almost_equal(test_candidates[0].welfare, 1.663));

    /* Test case 2 */
    assert(test_candidates[3].candidate == 'D');
    assert(is_almost_equal(test_candidates[3].welfare, 2.306));

    /* Test case 3 */
    assert(test_candidates[4].candidate == 'E');
    assert(is_almost_equal(test_candidates[4].welfare, 2.164));

}

/* Åbner en fil */
FILE* open_file(const char* file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

int is_almost_equal(double actual, double expected) {
    return fabs(actual - expected) < 0.000001;
}