#include <stdio.h>
#include <stdlib.h>
#include "../src/h-filer/main.h"

FILE* open_file(const char* file_path) {
    FILE *file = fopen(file_path, "r");

    if (file == NULL) { // Tjekker om filen kan åbnes
        perror("Could not open file"); // Printer fejl hvis filen ikke kan åbnes
        exit(EXIT_FAILURE);
    }

    return file;
}