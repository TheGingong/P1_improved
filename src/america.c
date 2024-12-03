#include <stdio.h>
#include "america.h"
#include "convert.h"
#include "calculate_winner.h"

/* Hovedfunktion som modtager antallet af kandidater fra main.c
 * Returnerer karakteren på vinder kandidaten til main.c */
char america(FILE *file) {
    /* Sætter votes og winner værdier i structen, all_states, til at være 0 */
    states all_states[STATES] = {0}; // Laver et array af states structen med antallet af stater

    initialize_states(all_states); // Kalder funktion som laver stater og tildeler valgmænd

    /* Initialisere person structen som benyttes */
    struct person current_state = convert_america(file); // Læser den første linje fra convert_america. Hvis den returnere -1 vil den ikke køre while loopet.

    /* While loop som kører så længe at convert_america ikke returnerer -1 */
    while(current_state.stat != -1) {
        current_state = convert_america(file); // Modtager en ny struct, current_state, fra convert_america til 'index' linje
        if (current_state.stat == -1) {
            break;
        }
        all_states[current_state.stat].votes[current_state.pref]++; // Tæller votes op i all_states udfra præferencen hos den individuelle person
    }

    /* For loop som gennemløber alle stater for at beregne vinderen i hver stat */
    /* Kald vinder funktion som også bruges af borda.c */
    for (int i = 0; i < STATES; i++) {
        all_states[i].winner = calculate_winner_func(all_states[i].votes);
    }

    /* Konventere vinderen fra en integer til en char, for et bedre resultat */
    char winner = assign_electors(all_states);

    return winner;
}

/* Tildeler hver vinder i den enkelte stat med statens antal valgmænd i et samlede array: candidates */
char assign_electors(states all_states[]) {
    int candidates[NUMBER_CANDIDATES] = {0};

    /* For loop gennemløber hver stats vinder og tildeler valgmændende i arrayet */
    for (int i = 0; i < STATES; i++) {
        candidates[all_states[i].winner] += all_states[i].electors;
    }

    /* Kalder calculate_winner
     * for at bestemme hvilken kandidat der har flest valgmænd og dermed vinder valget */
    char winner = calculate_winner_func(candidates);
    return 'A' + winner; // Returnere den korrekte kandidat ved brug af det index fra calculate_winner_func
}

/* Her initialiseres alle staterne i USA med korrekte antal valgmænd udfra antal hus repræsentanter og senater pr. stat */
void initialize_states(states all_states[]) {
        all_states[ALABAMA].electors = 9;
        all_states[ALASKA].electors = 3;
        all_states[ARIZONA].electors = 11;
        all_states[ARKANSAS].electors = 6;
        all_states[CALIFORNIA].electors = 54;
        all_states[COLORADO].electors = 10;
        all_states[CONNECTICUT].electors = 7;
        all_states[DELAWARE].electors = 3;
        all_states[DISTRICT_OF_COLUMBIA].electors = 3;
        all_states[FLORIDA].electors = 30;
        all_states[GEORGIA].electors = 16;
        all_states[HAWAII].electors = 4;
        all_states[IDAHO].electors = 4;
        all_states[ILLINOIS].electors = 19;
        all_states[INDIANA].electors = 11;
        all_states[IOWA].electors = 6;
        all_states[KANSAS].electors = 6;
        all_states[KENTUCKY].electors = 8;
        all_states[LOUISIANA].electors = 8;
        all_states[MAINE].electors = 4;
        all_states[MARYLAND].electors = 10;
        all_states[MASSACHUSETTS].electors = 11;
        all_states[MICHIGAN].electors = 15;
        all_states[MINNESOTA].electors = 10;
        all_states[MISSISSIPPI].electors = 6;
        all_states[MISSOURI].electors = 10;
        all_states[MONTANA].electors = 4;
        all_states[NEBRASKA].electors = 5;
        all_states[NEVADA].electors = 6;
        all_states[NEW_HAMPSHIRE].electors = 4;
        all_states[NEW_JERSEY].electors = 14;
        all_states[NEW_MEXICO].electors = 5;
        all_states[NEW_YORK].electors = 28;
        all_states[NORTH_CAROLINA].electors = 16;
        all_states[NORTH_DAKOTA].electors = 3;
        all_states[OHIO].electors = 17;
        all_states[OKLAHOMA].electors = 7;
        all_states[OREGON].electors = 8;
        all_states[PENNSYLVANIA].electors = 19;
        all_states[RHODE_ISLAND].electors = 4;
        all_states[SOUTH_CAROLINA].electors = 9;
        all_states[SOUTH_DAKOTA].electors = 3;
        all_states[TENNESSEE].electors = 11;
        all_states[TEXAS].electors = 40;
        all_states[UTAH].electors = 6;
        all_states[VERMONT].electors = 3;
        all_states[VIRGINIA].electors = 13;
        all_states[WASHINGTON].electors = 12;
        all_states[WEST_VIRGINIA].electors = 4;
        all_states[WISCONSIN].electors = 10;
        all_states[WYOMING].electors = 3;
}