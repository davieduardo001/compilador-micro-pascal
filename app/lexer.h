#ifndef LEXER_H
#define LEXER_H

typedef struct {
    char nome[20];    // Nome do token (por exemplo, "ID", "NUM")
    char lexema[100]; // O valor do token (por exemplo, "x", "12")
    int linha;        // Linha em que o token foi encontrado
    int coluna;       // Coluna em que o token foi encontrado
} Token;

// Funções para o analisador léxico
Token obter_token(FILE *arquivo);
void analisar_lexico(FILE *arquivo);
void iniciar_tabela_de_simbolos();
void inserir_na_tabela(char *lexema);
void reportar_erro(char *mensagem, int linha, int coluna);

#endif
