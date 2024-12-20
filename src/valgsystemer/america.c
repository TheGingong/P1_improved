#include <stdlib.h>

#include "../h-filer/valgsystemer.h"
#include "../h-filer/convert.h"
#include "../h-filer/calculate_winner.h"

/* Hovedfunktion som modtager antallet af kandidater fra main.c
 * Returnerer karakteren på vinder kandidaten til main.c */
char america(FILE* file) {
    /* Sætter votes og winner værdier i structen, all_states, til at være 0 */
    states all_states[STATES] = {0}; // Laver et array af states structen med antallet af stater

    initialize_states(all_states); // Kalder funktion som laver stater og tildeler valgmænd

    /* Initialisere person structen som benyttes */
    struct person current_state = convert_america(file); // Læser den første linje fra convert_america.

    /* While løkke som kører så længe at convert_america ikke returnerer -1 */
    while(current_state.stat != -1) {
        all_states[current_state.stat].votes[current_state.pref]++; // Tæller votes op i all_states ud fra præferencen hos den individuelle person
        current_state = convert_america(file); // Modtager en ny struct, current_state, fra convert_america til 'index' linje
    }

    /* For løkke som gennemløber alle stater for at beregne vinderen i hver stat
     * Kald vinder funktion som også bruges af borda.c */
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

    /* For løkke gennemløber hver stats vinder og tildeler valgmændende i arrayet */
    for (int i = 0; i < STATES; i++) {
        candidates[all_states[i].winner] += all_states[i].electors;
    }

    /* Kalder calculate_winner for at bestemme hvilken kandidat der har flest valgmænd og dermed vinder valget */
    char winner = calculate_winner_func(candidates);
    return 'A' + winner; // Returnerer den korrekte kandidat ved brug af det index fra calculate_winner_func
}

/* Her initialiseres alle staterne i USA med korrekte antal valgmænd ud fra antal husrepræsentanter og senatorer pr. stat */
void initialize_states(states all_states[]) {
    for (int i = 0; i < STATES; i++) {
        all_states[i].electors = electors[i];
    }
}