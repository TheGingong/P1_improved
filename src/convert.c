#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include "static_variables.h"

/* convert_borda tager i mod et array af ints og finder hvad en person har stemt */
int convert_borda(int* array_pref, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    char temp[NUMBER_CANDIDATES] = {0};
    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        return 0; // returner 0 for fejl
    }
            /* %c Gemmer en enkelt character kan være hvad som helst i en tekst streng.
            * %*f Kombinere det at læse en float og så ignorer den med stjernen.
            * %f Gemmer en float værdi.
            * "*" Istedet for at gemme så har stjernen den funktion at ignorer det den læser.
            *  sscanf kigger i temp_text_str og gør sig brug af de forskellige gemme variabler nævnt ovenfor til at gemme i
            *  Arrayet's forskellige pladser
            *  Hvis ikke den gemmer 5 characters i arrayet giver den fejl kode.
            */
            if (sscanf(temp_text_str, "%*d( %c%*f %c%*f %c%*f %c%*f %c%*f",
            &temp[0], &temp[1], &temp[2], &temp[3], &temp[4]) == 5) {
                array_pref[0] = temp[0]-'A';
                array_pref[1] = temp[1]-'A';
                array_pref[2] = temp[2]-'A';
                array_pref[3] = temp[3]-'A';
                array_pref[4] = temp[4]-'A';
            } else {
                printf("Error: Could not parse the line.\n"); // printer fejlkode hvis ikke den indlæser 5
            }
            return 1; // returner 1 for succes

    }


/* convert_america taget tekst fil, læser og indlæser værdier til struck ny_person der returnes */
struct person convert_america(FILE *file) {
    struct person ny_person;
    char temp_text_str[MAX_LINE_LENGTH]; // Laver en temp string for at kunne bruge fgets
    int current_line = 0;

    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        ny_person.stat = -1; // Hvis fgets har læst til en newline returneres 'ny_person.stat' med -1 for at signalere slutningen af tekstfilen
        return ny_person;
    }
    char temp; // midlertidig variabel for at kunne typecast til int senere
    if (sscanf(temp_text_str, "%d( %c", &ny_person.stat, &temp) == 2) { // Sscanf læser en string og indlæser værdier i de specificeret variabler
        ny_person.pref = temp - 'A'; // typecasting the char to an int
    } else {
        printf("Error: Could not parse the line.\n"); // printer fejlkode hvis ikke den indlæser 5
    }
    return ny_person; // returner ny_person struct for succes
}