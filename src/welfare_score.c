#include <stdio.h>
#include "static_variables.h"

double welfare_calculator(char winner) {
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.

    if (file == NULL) {
        perror("Could not open file.");
    }

    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    char format[MAX_LINE_LENGTH]; // Det dynamiske format som skal fortælle hvor sscanf skal læse linjen
    double welfare_score = 0, temp;
    int person_count = 0;
    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) { // Kører så længe der ikke er en tom linje
        person_count++; //Count for hver linje/person, så gennemsnittet kan findes til sidst
        sprintf(format, "%%*[^%c]%c%%lf", winner,winner); // Læser op til og forbi vinder, for at finde velfærd hos kandidaten
            if (sscanf(temp_text_str, format, &temp) == 1){ // Loop som efter hver korrekt læsning summere velfærdsscoren
                welfare_score += temp;
            } else {
                printf("Error: Could not parse the line.\n"); // Printer fejlkoden
            }
    }
    fclose(file); // Lukker text filen
    return welfare_score / person_count; // Gennemsnitlige velfærd for personerne
}