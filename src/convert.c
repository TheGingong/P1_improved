#include "convert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 40


// Ny optimering

/* convert_borda tager i mod et array af chars og hvilken linjen i text filen den skal sende tilbage i arrayet */
int convert_borda(char* array_pref, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i
    int current_line = 0; // Erklærer den nuværende linje

    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        return 0;
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
        &array_pref[0],&array_pref[1], &array_pref[2], &array_pref[3],&array_pref[4])==5) {
        } else {
            printf("Error: Could not parse the line.\n"); // printer fejlkoden
        }
    return 1; // returner 1 for succes
}


/* convert_america tager imod en linje på tekstfilen der skal læses.
* Tekst fil bliver læst og indlæser værdier til struck person der returnes */
struct person convert_america(FILE *file) {
    struct person ny_person;
    if (file == NULL) {
        perror("Could not open file");
    }

    char temp_text_str[MAX_LINE_LENGTH]; // Laver en temp string for at kunne bruge fgets

    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) { // læser linje og gemmer i "temp_text_str"
        char temp; // midlertidig variabel for at kunne typecast til int senere
        if (sscanf(temp_text_str, "%d( %c", &ny_person.stat, &temp) == 2) { // Sscanf læser en string og indlæser værdier i de specificeret variabler
            ny_person.pref = temp - 'A'; // typecasting the char to an in
        } else {
            printf("Error: Could not parse the line.\n");
        }
        return ny_person;
    }

    ny_person.stat = -1; // Hvis fgets har læst til en newline returneres 'ny_person.stat' med -1 for at signalere slutningen af tekstfilen
    return ny_person;
}
