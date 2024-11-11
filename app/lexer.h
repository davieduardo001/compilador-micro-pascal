// lexer.h

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKEN_LENGTH 1000000

typedef struct {
    char nome[MAX_TOKEN_LENGTH];
    char lexema[MAX_TOKEN_LENGTH];
    int linha;
    int coluna;
} Token;

// Function prototypes
Token create_token(const char *nome, const char *lexema, int linha, int coluna);
void skip_whitespace(FILE *arquivo);
Token obter_token(FILE *arquivo);
void iniciar_tabela_de_simbolos();
void analisar_lexico(FILE *arquivo, FILE *saida);

#endif // LEXER_H
