#include "convert.h"


int convert_borda(char winner) {
    FILE *file = fopen("text-files/test-tekstil.txt", "r"); // Filen med præferencer åbnes i read mode.
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    int current_line = 0; // Erklærer den nuværende linje

    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    while (fgets(temp_text_str, sizeof(temp_text_str), file) != NULL) {
        if (current_line == line_person) { // Tjekker om current line er lig den linje som vi vil returnere tilbage
            /* %c Gemmer en enkelt character kan være hvad som helst i en tekst streng.
            * %*f Kombinere det at læse en float og så ignorer den med stjernen.
            * %f Gemmer en float værdi.
            * "*" Istedet for at gemme så har stjernen den funktion at ignorer det den læser.
            *  sscanf kigger i temp_text_str og gør sig brug af de forskellige gemme variabler nævnt ovenfor til at gemme i
            *  Arrayet's forskellige pladser
            *  Hvis ikke den gemmer 5 characters i arrayet giver den fejl kode.
            */
            if (sscanf(temp_text_str, "%*d( %c%*f %c%*f %c%*f %c%*f %c%*f",
                &array_pref[0],&array_pref[1], &array_pref[2], &array_pref[3],&array_pref[4])==5) {
            } else {
                printf("Error: Could not parse the line.\n"); // printer fejlkoden
            }
            fclose(file); //Lukker text filen
            return 1; // returner 1 for succes
        }
        current_line++;
    }
    if (current_line < line_person) {
        // printf("The file has fewer than %d lines.\n", line_person); // Hvis der bliver bedt om at kigge på en linje der ikke findes i tekst filen får man denne error besked
        return 0; // returner 0 for fejl
    }
    fclose(file); // Lukker text filen
}