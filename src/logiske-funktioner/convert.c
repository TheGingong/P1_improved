#include <string.h>
#include "../h-filer/convert.h"
#include "../h-filer/static_variables.h"

/* convert_borda tager imod et array af integers og finder hvad en person har stemt */
int convert_borda(int* array_pref, FILE *file) {
    char temp_text_str[MAX_LINE_LENGTH]; // Erklærer en midlertidig tekststreng hvor hele linjen fra tekstfilen gemmes i

    /* fgets læser max "sizeof(temp_text_str) characters fra file stream -
    * - og gemmer dem i tekststrengen "temp_text_str"
    * fgets stopper med at parse text hvis den rammer en ny linje */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        return 0; // returner 0 for fejl
    }

    /* Benytter strtok, fra string.h library, for at tilgå de nødvendige dele af hver linje i tekstfilen.
     * Strtok splitter hver linje op med '\0' ved den delimiter man specificere, fx. '(' eller mellemrum.
     * Tildeler de individuelle del-strenge strtok danner, og indsætter dem for array_pref til det nuværende index, så hver vælger får den korrekte præference ordning.
     * Token begrebet benyttes ofte til at beskrive at det er del elemeneter i en lang sekvens */
    char* token = strtok(temp_text_str, "(");
    token = strtok(NULL, "("); // Delimiter "("

    token = strtok(token, " "); // Delimiter mellemrum
    int index = 0; // Kandidat index initialiseres (bruges som tællevariabel og til at indeksere)
    while (token != NULL) { // Fortsætter while loop indtil token returnerer NULL, hvilket vil sige at linjen er færdig
        array_pref[index] = token[0] - 'A'; // Tildeler her hvert første element i de indivuelle delstrings, som strtok danner, til array_pref kandidat indekset
        token = strtok(NULL, " ");
        index++;
    }

    return 1; // returner 1 for succes
}

/* convert_america tager imod en fil med tekst, læser og indlæser værdier til struct ny_person der returnes af funktionen */
struct person convert_america(FILE *file) {
    struct person ny_person = {0};
    char temp_text_str[MAX_LINE_LENGTH]; // Laver en midlertidig tekststreng for at kunne bruge fgets

    /* fgets læser max "sizeof(temp_text_str) characters fra file stream -
    * - og gemmer dem i tekststrengen "temp_text_str"
    * fgets stopper med at parse text hvis den rammer en ny linje */
    if (fgets(temp_text_str, sizeof(temp_text_str), file) == NULL) {
        ny_person.stat = -1; // Hvis fgets har læst til en ny linje returneres 'ny_person.stat' med -1 for at signalere slutningen af tekstfilen
        return ny_person;
    }

    char temp; // midlertidig variabel som bruges til konvertering fra char til integer senere
    if (sscanf(temp_text_str, "%d( %c", &ny_person.stat, &temp) == 2) { // Sscanf læser en streng og indlæser værdier i de specificeret variabler
        ny_person.pref = temp - 'A'; // Konvertere præference charen til en integer
    } else {
        printf("Error: Could not parse the line (convert.c).\n"); // printer fejlkode hvis ikke den indlæser 2 værdier
    }

    return ny_person; // returner ny_person struct for succes
}