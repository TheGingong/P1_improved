#include "../h-filer/welfare_score.h"
#include <stdio.h>
#include <stdlib.h>
#include "../h-filer/static_variables.h"

/* Beregningen af SUE for det givet valgsystem */
double SUE_value(double avg_max, double avg_random_cand_welfare, double avg_elected) {
    double denumerator = (avg_max - avg_random_cand_welfare);
    if (denumerator == 0) { // Tjekker om avg_max minus avg_random_cand_welfare gav 0, dette gøres for at undgå division med 0
        denumerator = 0.0001;
    }

    double SUE = ((avg_elected - avg_random_cand_welfare) / denumerator) * 100;
    return SUE;
}

/* Funktion der sørger for at velfærdsscore for maksimerende kandidat, valgte kandidat og en tilfældig kandidat,
 * bliver talt op, hen over alle simulationer*/
void utilitarian_welfare(char winner, FILE *file, double *max, double *elected, double *random) {
    candidate_welfare candidates[NUMBER_CANDIDATES] = {0};
    read_candidate_welfare(candidates, file); // Kalder funktion der læser velfærdsscore fra filen

    /* Gennemløber antallet af kandidater og finder den kandidat med højest velfærdsscore */
    *max = 0; // Sikrer at for hver simulation defineres en ny max
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (candidates[i].welfare > *max) {
            *max = candidates[i].welfare; //værdien gemmes i max, hvor denne værdi sendes tilbage til simulations.c i form af en pointer
        }
    }

    /* Kalder index_finder funktion for at få vinderne i hhv. borda og americas velfærdsscore */
    int winner_index = index_finder(winner, candidates);
    *elected = candidates[winner_index].welfare; // Gemmer vinderens velfærd i pointeren elected

    /* Summere alle kandidaters velfærdsscore op, så den gennemsnitlige velfærdsscore for en tilfældig kandidat kan beregnes */
    double sum_of_candidates = 0;
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        sum_of_candidates += candidates[i].welfare;
    }
    *random = sum_of_candidates / NUMBER_CANDIDATES;
}

/* Funktion der optæller hver kandidats velfærdsscore */
void read_candidate_welfare(candidate_welfare *candidates, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    char format[MAX_LINE_LENGTH]; // Det dynamiske format som skal fortælle hvor sscanf skal læse linjen
    double temp;

    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) { // Kører så længe der ikke er en tom linje (returnerer NULL)
        /* For-løkke der gennemløber antallet af kandidater lægger kandidater ind i candidate arrayet */
        for (int i = 0; i < NUMBER_CANDIDATES; i++) {
            candidates[i].candidate = (char)('A' + i); // Her initialiseres kandidaterne i ordning, først tælles kandidat A's velfærdsscore op, så B, C, D...
            sprintf(format, "%%*[^%c]%c%%lf", candidates[i].candidate, candidates[i].candidate); // sprintf gemmer læsningsformatet som sscanf skal bruge
                                                                                                       // fortæller sscanf at den skal springe over alt til-og-med den ønsket char
                                                                                                       // og derefter skal læse long float værdien
            if (sscanf(temp_text_str, format, &temp) == 1){ // sscanf læser på temp_text_str strengen (der indeholder én vælgers præference) med format givet af sprinf.
                candidates[i].welfare += temp; // Summerer den indlæste velfærdsscoren til den nuværende kandidat i løkken
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
