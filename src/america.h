#include "static_variables.h"
#define STATES 51
#define NUMBER_OF_VOTERS 100

typedef struct {
    int votes[NUMBER_CANDIDATES];
    int electors;
    int winner;
} states;

typedef enum {
    ALABAMA,
    ALASKA,
    ARIZONA,
    ARKANSAS,
    CALIFORNIA,
    COLORADO,
    CONNECTICUT,
    DELAWARE,
    FLORIDA,
    GEORGIA,
    HAWAII,
    IDAHO,
    ILLINOIS,
    INDIANA,
    IOWA,
    KANSAS,
    KENTUCKY,
    LOUISIANA,
    MAINE,
    MARYLAND,
    MASSACHUSETTS,
    MICHIGAN,
    MINNESOTA,
    MISSISSIPPI,
    MISSOURI,
    MONTANA,
    NEBRASKA,
    NEVADA,
    NEW_HAMPSHIRE,
    NEW_JERSEY,
    NEW_MEXICO,
    NEW_YORK,
    NORTH_CAROLINA,
    NORTH_DAKOTA,
    OHIO,
    OKLAHOMA,
    OREGON,
    PENNSYLVANIA,
    RHODE_ISLAND,
    SOUTH_CAROLINA,
    SOUTH_DAKOTA,
    TENNESSEE,
    TEXAS,
    UTAH,
    VERMONT,
    VIRGINIA,
    WASHINGTON,
    WEST_VIRGINIA,
    WISCONSIN,
    WYOMING,
    DISTRICT_OF_COLUMBIA
} state_names;

/* Prototyper */
int calculate_winner(const int *array, int number_of_candidates);
char america(int number_of_candidates);
void initialize_states(states all_states[]);
int assign_electors(states all_states[], int number_of_candidates);