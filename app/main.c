#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "symbol_table.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *sourceFile = argv[1];
    initializeLexer(sourceFile);

    Token token;
    while ((token = getNextToken()).nome != NULL) {
        printf("Token: %s, Lexema: %s, Linha: %d, Coluna: %d\n", 
               token.nome, token.lexema, token.linha, token.coluna);
    }

    printSymbolTable(); // Mostrar a tabela de símbolos
    generateOutputFile("output.lex");
    return EXIT_SUCCESS;
}
