#include "../h-filer/welfare_score.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../h-filer/static_variables.h"

/* Funktion til at beregne social utility efficiency hos vinder kandidaten */
void social_utility_efficiency(char winner, FILE *file, double *max, double *elected, double *random) {
    candidate_welfare candidate[NUMBER_CANDIDATES] = {0};
    read_candidate_welfare(candidate, file); // Kalder funktion der læser velfærdsscorene fra filen


    /* Gennemløber antallet af kandidater og finder den kandidat med højest velfærdsscore */
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (candidate[i].welfare > *max) {
            *max = candidate[i].welfare;
        }
    }

    /* Kalder hashing funktion for at få vinderne i hhv. borda og americas velfærdsscore */
    int winner_index = index_finder(winner, candidate);

    *elected = candidate[winner_index].welfare; // Gemmer vinderens velfærd i winner_welfare
    *random = candidate[rand() % NUMBER_CANDIDATES].welfare;

    /* Beregningen af social utility efficiency mellem vinder kandidaten og den kandidat med højest velfærdsscore */
    //double SUE_value = (winner_welfare / *max) * 100;

    //return SUE_value; // Returnere procent værdien til main for print
}

/* Funktion der gennemløber filen for kandidater og summerer deres velfærdsscore */
void read_candidate_welfare(candidate_welfare *candidate, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    char format[MAX_LINE_LENGTH]; // Det dynamiske format som skal fortælle hvor sscanf skal læse linjen
    double temp;

    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) { // Kører så længe der ikke er en tom linje (returnerer NULL)
        /* For loop der gennemløber antallet af kandidater lægger kandidater ind i candidate arrayet */
        for (int i = 0; i < NUMBER_CANDIDATES; i++) {
            candidate[i].candidate = 'A' + i; // Her initializeres kandidaterne
            sprintf(format, "%%*[^%c]%c%%lf", candidate[i].candidate, candidate[i].candidate); // sprintf gemmer læsningsformatet som sscanf skal bruge
                                                                                               // fortæller sscanf at den skal springe over alt til-og-med en char og derefter skal læse long float værdien
            if (sscanf(temp_text_str, format, &temp)==1){
                candidate[i].welfare += temp; // Summerer den indlæste velfærdsscoren til den nuværende kandidat i loopet
                //printf("Candidate %c welfare: %lf\n", candidate[i].candidate, candidate[i].welfare);
            } else {
                printf("Error: Could not parse the line (welfare_score.c).\n");
            }
        }
    }
}

/* Hashing funktion som returnerer et index, i candidate arrayet, for den kandidat den modtager */
int index_finder(char winner, candidate_welfare candidate[]) {
    for (int i = 0; i < NUMBER_CANDIDATES; i++) {
        if (candidate[i].candidate == winner) {
            return i;
        }
    }
    return EXIT_FAILURE; // Hvis ikke kandidaten findes lukker programmet
}