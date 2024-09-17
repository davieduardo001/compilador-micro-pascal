#ifndef LEXER_H
#define LEXER_H

#define MAX_LEXEMA 100
#define MAX_NOME 20

typedef struct {
    char nome[MAX_NOME];
    char lexema[MAX_LEXEMA];
    int linha;
    int coluna;
} Token;

void iniciar_tabela_de_simbolos();
void analisar_lexico(FILE *arquivo);
void imprimir_token(Token token);
void reportar_erro(char *mensagem, int linha, int coluna);

#endif // LEXER_H
