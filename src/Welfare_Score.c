#include "convert.h"
#include "america.h"


double welfare_calculator(char winner) {
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    double welfare_score = 0;
    double temp;
    char format[MAX_LINE_LENGTH];
    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) {
        sprintf(format, "%*[^%c]%c%lf", winner, winner);
            if (sscanf(temp_text_str, format, &temp)<= 1){
                welfare_score += temp;
            } else {
                printf("Error: Could not parse the line.\n"); // printer fejlkoden
            }
    }
    return welfare_score/51;
    fclose(file); // Lukker text filen
}