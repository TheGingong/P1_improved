#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "america.h"
#include "borda.h"
#include "static_variables.h"

int main(void) {
    /* Kalder simluering af det amerikanske valgsystem */
    printf("The winner candidate of the american election is: %c\n\n", america(NUMBER_CANDIDATES));

    /* Kalder simulering af et valgsystem som bruger Borda count */
    printf("The winner candidate of borda count is: %c", borda_count(NUMBER_CANDIDATES));

    return 0;
}
