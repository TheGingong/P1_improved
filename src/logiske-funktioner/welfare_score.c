#include "../h-filer/welfare_score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h-filer/static_variables.h"

/* Beregningen af SUE for det givet valgsystem */
void SUE_value(double avg_max, double avg_random_cand_welfare, double avg_elected) {
    double denumerator = (avg_max - avg_random_cand_welfare);
    if (denumerator == 0) { // Tjekker om avg_max minus avg_random_cand_welfare gav 0
        denumerator = 0,0001;
    }
    double SUE = ((avg_elected - avg_random_cand_welfare) / denumerator) * 100;
    printf("SUE Value for the american election: %.3lf%%\n", SUE);
}

/* Funktion til at beregne social utility efficiency hos vinder kandidaten */
void utilitarian_welfare(char winner, FILE *file, double *max, double *elected, double *random) {
    candidate_welfare candidates[NUMBER_CANDIDATES] = {0};
    read_candidate_welfare(candidates, file); // Kalder funktion der læser velfærdsscorene fra filen

    /* Gennemløber antallet af kandidater og finder den kandidat med højest velfærdsscore */
    *max = 0; // Sikrer at for hver simulation defineres en ny max
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (candidates[i].welfare > *max) {
            *max = candidates[i].welfare;
        }
    }

    /* Kalder index_finder funktion for at få vinderne i hhv. borda og americas velfærdsscore */
    int winner_index = index_finder(winner, candidates);

    int random_candidate = rand() % NUMBER_CANDIDATES; // Genererer et tilfældigt tal brugt til at indekse random

    *elected = candidates[winner_index].welfare; // Gemmer vinderens velfærd i winner_welfare
    *random = candidates[random_candidate].welfare; // Vælger en tilfældig kandidats velfærd
}

/* Funktion der gennemløber filen for kandidater og summerer deres velfærdsscore */
void read_candidate_welfare(candidate_welfare *candidates, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    char format[MAX_LINE_LENGTH]; // Det dynamiske format som skal fortælle hvor sscanf skal læse linjen
    double temp;

    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) { // Kører så længe der ikke er en tom linje (returnerer NULL)
        /* For loop der gennemløber antallet af kandidater lægger kandidater ind i candidate arrayet */
        for (int i = 0; i < NUMBER_CANDIDATES; i++) {
            candidates[i].candidate = 'A' + i; // Her initializeres kandidaterne i ordning
            sprintf(format, "%%*[^%c]%c%%lf", candidates[i].candidate, candidates[i].candidate); // sprintf gemmer læsningsformatet som sscanf skal bruge
                                                                                               // fortæller sscanf at den skal springe over alt til-og-med en char og derefter skal læse long float værdien
            if (sscanf(temp_text_str, format, &temp)==1){
                candidates[i].welfare += temp; // Summerer den indlæste velfærdsscoren til den nuværende kandidat i loopet
                //printf("Candidate %c welfare: %lf\n", candidate[i].candidate, candidate[i].welfare);
            } else {
                printf("Error: Could not parse the line (welfare_score.c).\n");
            }
        }
    }
}

/* Funktion som returnerer et index, i candidate arrayet, for den kandidat den modtager */
int index_finder(char winner, candidate_welfare candidates[]) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (candidates[i].candidate == winner) {
            return i;
        }
    }
    return EXIT_FAILURE; // Hvis ikke kandidaten findes lukker programmet
}
