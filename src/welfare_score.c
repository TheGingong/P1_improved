#include "convert.h"
#include "america.h"

double welfare_calculator(char winner) {
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.

    if (file == NULL) {
        perror("Could not open file.");
    }

    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes
    char format[MAX_LINE_LENGTH];
    double welfare_score = 0, temp;
    int person_count = 0;
    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) {
        person_count++;
        sprintf(format, "%%*[^%c]%c%%lf", winner,winner);
            if (sscanf(temp_text_str, format, &temp) == 1){
                welfare_score += temp;
            } else {
                printf("Error: Could not parse the line.\n"); // Printer fejlkoden
            }
    }
    fclose(file); // Lukker text filen
    return welfare_score / person_count; // Gennemsnitlige velfærd for personerne
}