#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

// Variáveis globais para controlar a linha e coluna atuais
int linha_atual = 1;
int coluna_atual = 0;

// Tabela de símbolos para palavras reservadas
char *palavras_reservadas[] = {"program", "var", "integer", "real", "begin", "end", "if", "then", "else", "while", "do", "write", "read", NULL};

// Inicia a tabela de símbolos com palavras reservadas
void iniciar_tabela_de_simbolos() {
    // Nenhuma implementação necessária no momento, pois estamos apenas imprimindo tokens
}

// Função para imprimir erros léxicos
void reportar_erro(char *mensagem, int linha, int coluna) {
    printf("\033[31mErro léxico: %s na linha %d, coluna %d\033[0m\n", mensagem, linha, coluna);
}

Token obter_token(FILE *arquivo) {
    Token token;
    int estado = 0;
    char c;
    int i = 0;

    while ((c = fgetc(arquivo)) != EOF) {
        coluna_atual++;

        if (isspace(c)) {
            if (c == '\n') {
                linha_atual++;
                coluna_atual = 0;
            }
            continue; // Ignora espaços em branco
        }

        if (isalpha(c)) { // Identifica identificadores e palavras reservadas
            token.lexema[i++] = c;
            while (isalnum(c = fgetc(arquivo))) {
                coluna_atual++;
                token.lexema[i++] = c;
            }
            token.lexema[i] = '\0';
            ungetc(c, arquivo); // Coloca o último caractere de volta no fluxo

            // Verifica se é uma palavra reservada
            for (int j = 0; palavras_reservadas[j] != NULL; j++) {
                if (strcmp(token.lexema, palavras_reservadas[j]) == 0) {
                    strcpy(token.nome, "PALAVRA_RESERVADA");
                    token.linha = linha_atual;
                    token.coluna = coluna_atual;
                    return token;
                }
            }

 
            strncpy(token.nome, "ID", sizeof(token.nome) - 1);
            token.nome[sizeof(token.nome) - 1] = '\0';  // Certificar-se que termina com '\0'

            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        }

        if (isdigit(c)) { // Números
            token.lexema[i++] = c;
            while (isdigit(c = fgetc(arquivo))) {
                coluna_atual++;
                token.lexema[i++] = c;
            }
            token.lexema[i] = '\0';
            ungetc(c, arquivo);

            strcpy(token.nome, "NUM");
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        }

        // Operadores
        if (c == '+') {
            strcpy(token.nome, "OP_AD");
            token.lexema[0] = '+';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '-') {
            strcpy(token.nome, "OP_MIN");
            token.lexema[0] = '-';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '*') {
            strcpy(token.nome, "OP_MUL");
            token.lexema[0] = '*';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '/') {
            strcpy(token.nome, "OP_DIV");
            token.lexema[0] = '/';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '=') {
            strcpy(token.nome, "OP_ASS");  // Atribuição e igualdade são tratados como OP_ASS
            token.lexema[0] = '=';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '>') {
            char next = fgetc(arquivo);
            coluna_atual++;
            if (next == '=') {
                strcpy(token.nome, "OP_GE"); // Maior ou igual
                token.lexema[0] = '>';
                token.lexema[1] = '=';
                token.lexema[2] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            } else {
                ungetc(next, arquivo);
                strcpy(token.nome, "OP_GT"); // Maior
                token.lexema[0] = '>';
                token.lexema[1] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            }
        } else if (c == '<') {
            char next = fgetc(arquivo);
            coluna_atual++;
            if (next == '=') {
                strcpy(token.nome, "OP_LE"); // Menor ou igual
                token.lexema[0] = '<';
                token.lexema[1] = '=';
                token.lexema[2] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            } else if (next == '>') {
                strcpy(token.nome, "OP_NE"); // Diferente <>
                token.lexema[0] = '<';
                token.lexema[1] = '>';
                token.lexema[2] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            } else {
                ungetc(next, arquivo);
                strcpy(token.nome, "OP_LT"); // Menor
                token.lexema[0] = '<';
                token.lexema[1] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            }
        }

        // Símbolos
        if (c == ';') {
            strcpy(token.nome, "SMB_SEM");
            token.lexema[0] = ';';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == ',') {
            strcpy(token.nome, "SMB_COM");
            token.lexema[0] = ',';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '{') {
            strcpy(token.nome, "SMB_OBC");
            token.lexema[0] = '{';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '}') {
            strcpy(token.nome, "SMB_CBC");
            token.lexema[0] = '}';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '(') {
            strcpy(token.nome, "SMB_OPA");
            token.lexema[0] = '(';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == ')') {
            strcpy(token.nome, "SMB_CPA");
            token.lexema[0] = ')';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == '.') {
            strcpy(token.nome, "SMB_FINAL");
            token.lexema[0] = '.';
            token.lexema[1] = '\0';
            token.linha = linha_atual;
            token.coluna = coluna_atual;
            return token;
        } else if (c == ':') {
            char next = fgetc(arquivo);
            coluna_atual++;
            if (next == '=') {
                strcpy(token.nome, "SMB_ATT");
                token.lexema[0] = ':';
                token.lexema[1] = '=';
                token.lexema[2] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            } else {
                ungetc(next, arquivo);
                strcpy(token.nome, "SMB_COL");
                token.lexema[0] = ':';
                token.lexema[1] = '\0';
                token.linha = linha_atual;
                token.coluna = coluna_atual;
                return token;
            }
        }

        reportar_erro("Caractere não reconhecido", linha_atual, coluna_atual);
    }

    strcpy(token.nome, "EOF");
    token.lexema[0] = '\0';
    token.linha = linha_atual;
    token.coluna = coluna_atual;
    return token;
}

void analisar_lexico(FILE *arquivo) {
    Token token;
    do {
        token = obter_token(arquivo);
        printf("<%s, %s> na linha %d, coluna %d\n", token.nome, token.lexema, token.linha, token.coluna);
    } while (strcmp(token.nome, "EOF") != 0);
}
