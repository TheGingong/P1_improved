#include <assert.h>
#include <stdlib.h>
#include "./h-filer/realistic_appropriation.h"
#include "./h-filer/calculate_winner.h"
#include "./h-filer/static_variables.h"
#include "./h-filer/valgsystemer.h"
#include "./h-filer/convert.h"
#include "./h-filer/welfare_score.h"

void test_winner_america1();

int main(void) {
    test_winner_america1();
    return 0;
}

/* Testing af om den rigtige kandidat bliver valgt */
void test_winner_america1() {
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
}