#include <string.h>
#include "../h-filer/convert.h"
#include "../h-filer/static_variables.h"

/* convert_borda tager i mod et array af ints og finder hvad en person har stemt */
int convert_borda(int* array_pref, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en temp tekst streng hvor hele linjen fra tekst filen gemmes i

    /* fgets læser max "sizeof(text_string) characters fra file stream -
    * - og gemmer dem i string-arrayet "text_string"
    * fgets stopper med at parse text hvis den rammer en newline */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        return 0; // returner 0 for fejl
    }

    /* Benytter strtok, fra string.h library for at tilgå de nødvendige dele af hver linje i tekstfilen.
     * Strtok splitter hver linje op med '\0' ved den delimiter man specificere, fx. '(' eller mellemrum.
     * Tildeler de individuelle del-strenge strtok danner, og indsætter dem for array_pref til det nuværende index så hver vælger får den korrekte præference ordning.
     * Token begrebet benyttes ofte til at beskrive at det er del elemeneter i en lang sekvens. */
    char* token = strtok(temp_text_str, "(");
    token = strtok(NULL, "(");

    token = strtok(token, " ");
    int index = 0; // Kandidat index
    while (token != NULL) { // Fortsætter while loop indtil token returnerer NULL hvilket vil sige at linjen er færdig
        array_pref[index] = token[0] - 'A'; // Tildeler her hvert første element i de indivuelle delstrings, som strtok danner, til array_pref kandidat indexet
        token = strtok(NULL, " ");
        index++;
    }
    return 1; // returner 1 for succes
}

/* convert_america taget tekst fil, læser og indlæser værdier til struck ny_person der returnes */
struct person convert_america(FILE *file) {
    struct person ny_person = {0};
    char temp_text_str[MAX_LINE_LENGTH]; // Laver en temp string for at kunne bruge fgets

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