#include "static_variables.h"
#include <stdio.h>
#define STATES 51
#define ANTAL_VALGMÆND 538

typedef struct {
    int votes[NUMBER_CANDIDATES];
    int electors;
    int winner;
} states;

typedef enum {
    ALABAMA, ALASKA, ARIZONA, ARKANSAS, CALIFORNIA, COLORADO,
    CONNECTICUT, DELAWARE, DISTRICT_OF_COLUMBIA, FLORIDA,
    GEORGIA, HAWAII, IDAHO, ILLINOIS, INDIANA, IOWA, KANSAS,
    KENTUCKY, LOUISIANA, MAINE, MARYLAND, MASSACHUSETTS, MICHIGAN,
    MINNESOTA, MISSISSIPPI, MISSOURI, MONTANA, NEBRASKA, NEVADA,
    NEW_HAMPSHIRE, NEW_JERSEY, NEW_MEXICO, NEW_YORK, NORTH_CAROLINA,
    NORTH_DAKOTA, OHIO, OKLAHOMA, OREGON, PENNSYLVANIA, RHODE_ISLAND,
    SOUTH_CAROLINA, SOUTH_DAKOTA, TENNESSEE, TEXAS, UTAH, VERMONT,
    VIRGINIA, WASHINGTON, WEST_VIRGINIA, WISCONSIN, WYOMING
} state_names;

/* Array med antallet af valgmænd for hver stat (2020-2030).
 * Rækkefølgen følger state_names enum rækkefølgen */
static int electors[STATES] = {
    9, 3, 11, 6, 54, 10, 7, 3, 3,
    30, 16, 4, 4, 19, 11, 6, 6, 8, 8, 4,
    10, 11, 15, 10, 6, 10, 4, 5, 6, 4,
    14, 5, 28, 16, 3, 17, 7, 8, 19, 4,
    9, 3, 11, 40, 6, 3, 13, 12, 4, 10, 3
};

/* Prototyper */
char america(FILE* file);
void initialize_states(states all_states[]);
char assign_electors(states all_states[]);
char borda_count(); // Borda prototype