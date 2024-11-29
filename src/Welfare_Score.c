#include "convert.h"


int welfare_calculator(char winner) {
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    double welfare_score = 0;
    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) {
            if (sscanf(temp_text_str, "%*[^A]%lf", &welfare_score)<=10){
                welfare_score += welfare_score;
            } else {
                printf("Error: Could not parse the line.\n"); // printer fejlkoden
            }
    }
    printf("%lf\n", welfare_score);
    fclose(file); // Lukker text filen
}