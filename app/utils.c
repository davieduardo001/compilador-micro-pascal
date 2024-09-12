#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void generateOutputFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Gerar a saída com tokens e tabela de símbolos
    fprintf(file, "Tokens e Tabela de Símbolos:\n");
    printSymbolTable();

    fclose(file);
}
