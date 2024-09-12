#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "symbol_table.h"

static FILE *sourceFile;
static int currentChar;
static int line = 1, column = 0;

void initializeLexer(const char *filename) {
    sourceFile = fopen(filename, "r");
    if (sourceFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    currentChar = fgetc(sourceFile);
}

static void advance() {
    currentChar = fgetc(sourceFile);
    if (currentChar == '\n') {
        line++;
        column = 0;
    } else {
        column++;
    }
}

static char* readIdentifier() {
    char buffer[100];
    int i = 0;
    while (isalnum(currentChar) || currentChar == '_') {
        buffer[i++] = currentChar;
        advance();
    }
    buffer[i] = '\0';
    return strdup(buffer);
}

Token getNextToken() {
    Token token;
    token.nome = NULL;
    token.lexema = NULL;
    token.linha = line;
    token.coluna = column;

    while (isspace(currentChar)) {
        advance();
    }

    if (isalpha(currentChar) || currentChar == '_') {
        char* lexema = readIdentifier();
        // Verificar se é palavra-chave ou identificador
        if (strcmp(lexema, "program") == 0 ||
            strcmp(lexema, "var") == 0 ||
            strcmp(lexema, "integer") == 0 ||
            strcmp(lexema, "real") == 0 ||
            strcmp(lexema, "begin") == 0 ||
            strcmp(lexema, "end") == 0 ||
            strcmp(lexema, "if") == 0 ||
            strcmp(lexema, "then") == 0 ||
            strcmp(lexema, "else") == 0 ||
            strcmp(lexema, "while") == 0 ||
            strcmp(lexema, "do") == 0) {
            token.nome = lexema;
            token.lexema = lexema;
        } else {
            token.nome = "ID";
            token.lexema = lexema;
            addToSymbolTable(lexema, "IDENTIFICADOR");
        }
        return token;
    } else if (isdigit(currentChar)) {
        // Adicionar lógica para números
        // ...
    } else if (currentChar == EOF) {
        token.nome = "EOF";
    } else {
        // Adicionar lógica para operadores e símbolos
        // ...
    }

    advance();
    return token;
}
