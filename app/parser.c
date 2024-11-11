#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

// Declaração de variáveis globais
FILE *arquivo_entrada;
FILE *arquivo_saida;

static Token token_atual;
extern int linha_atual;
extern int coluna_atual;

void CasaToken(const char *token_esperado) {
    if (strcmp(token_atual.nome, token_esperado) == 0) {
        token_atual = obter_token(arquivo_entrada);
    } else {
        fprintf(stderr, "%d: token não esperado [%s]. Esperado [%s].\n", linha_atual, token_atual.lexema, token_esperado);
        exit(EXIT_FAILURE);
    }
}

void parser(FILE *entrada, FILE *saida) {
    arquivo_entrada = entrada;
    arquivo_saida = saida;
    token_atual = obter_token(arquivo_entrada);
    programa();
    if (strcmp(token_atual.nome, "EOF") != 0) {
        fprintf(stderr, "%d: fim de arquivo não esperado.\n", linha_atual);
        exit(EXIT_FAILURE);
    }
}

void programa() {
    CasaToken("PALAVRA_RESERVADA"); // "program"
    CasaToken("ID"); // identificador
    CasaToken("SMB_SEM"); // ";"
    bloco();
    CasaToken("SMB_FINAL"); // "."
}

void bloco() {
    parte_declaracoes_variaveis();
    comando_composto();
}

void parte_declaracoes_variaveis() {
    if (strcmp(token_atual.nome, "PALAVRA_RESERVADA") == 0 && strcmp(token_atual.lexema, "var") == 0) {
        CasaToken("PALAVRA_RESERVADA"); // "var"
        declaracao_variaveis();
        while (strcmp(token_atual.nome, "SMB_SEM") == 0) {
            CasaToken("SMB_SEM"); // ";"
            declaracao_variaveis();
        }
        CasaToken("SMB_SEM"); // ";"
    }
}

void declaracao_variaveis() {
    lista_identificadores();
    CasaToken("SMB_COL"); // ":"
    tipo();
}

void lista_identificadores() {
    CasaToken("ID"); // identificador
    while (strcmp(token_atual.nome, "SMB_COM") == 0) {
        CasaToken("SMB_COM"); // ","
        CasaToken("ID"); // identificador
    }
}

void tipo() {
    if (strcmp(token_atual.nome, "PALAVRA_RESERVADA") == 0) {
        if (strcmp(token_atual.lexema, "integer") == 0 || strcmp(token_atual.lexema, "real") == 0) {
            CasaToken("PALAVRA_RESERVADA");
        } else {
            fprintf(stderr, "%d: tipo não esperado [%s].\n", linha_atual, token_atual.lexema);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "%d: tipo não esperado [%s].\n", linha_atual, token_atual.lexema);
        exit(EXIT_FAILURE);
    }
}

void comando_composto() {
    // Depuração: Verificando o token antes de processar o 'begin'
    printf("Esperando 'begin', token atual: %s\n", token_atual.lexema);  // Depuração
    CasaToken("PALAVRA_RESERVADA"); // "begin"
    
    comando();  // Processa o comando
    while (strcmp(token_atual.nome, "SMB_SEM") == 0) {
        CasaToken("SMB_SEM"); // ";"
        comando();  // Processa o próximo comando
    }
    CasaToken("PALAVRA_RESERVADA"); // "end"
}

void comando() {
    // Depuração: Mostrando o token antes de decidir qual tipo de comando processar
    printf("Token atual: %s\n", token_atual.lexema);  // Depuração
    if (strcmp(token_atual.nome, "ID") == 0) {
        atribuicao();
    } else if (strcmp(token_atual.nome, "PALAVRA_RESERVADA") == 0) {
        if (strcmp(token_atual.lexema, "begin") == 0) {
            comando_composto();
        } else if (strcmp(token_atual.lexema, "if") == 0) {
            comando_condicional();
        } else if (strcmp(token_atual.lexema, "while") == 0) {
            comando_repetitivo();
        } else {
            fprintf(stderr, "%d: comando não esperado [%s].\n", linha_atual, token_atual.lexema);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "%d: comando não esperado [%s].\n", linha_atual, token_atual.lexema);
        exit(EXIT_FAILURE);
    }
}

void atribuicao() {
    CasaToken("ID"); // identificador
    CasaToken("SMB_ATT"); // ":="
    expressao();
}

void comando_condicional() {
    CasaToken("PALAVRA_RESERVADA"); // "if"
    expressao();
    CasaToken("PALAVRA_RESERVADA"); // "then"
    comando();
    if (strcmp(token_atual.nome, "PALAVRA_RESERVADA") == 0 && strcmp(token_atual.lexema, "else") == 0) {
        CasaToken("PALAVRA_RESERVADA"); // "else"
        comando();
    }
}

void comando_repetitivo() {
    CasaToken("PALAVRA_RESERVADA"); // "while"
    expressao();
    CasaToken("PALAVRA_RESERVADA"); // "do"
    comando_composto();
}

void expressao() {
    expressao_simples();
    if (strcmp(token_atual.nome, "OP_EQ") == 0 || strcmp(token_atual.nome, "OP_NE") == 0 ||
        strcmp(token_atual.nome, "OP_LT") == 0 || strcmp(token_atual.nome, "OP_LE") == 0 ||
        strcmp(token_atual.nome, "OP_GT") == 0 || strcmp(token_atual.nome, "OP_GE") == 0) {
        relacao();
        expressao_simples();
    }
}

void relacao() {
    if (strcmp(token_atual.nome, "OP_EQ") == 0) {
        CasaToken("OP_EQ");
    } else if (strcmp(token_atual.nome, "OP_NE") == 0) {
        CasaToken("OP_NE");
    } else if (strcmp(token_atual.nome, "OP_LT") == 0) {
        CasaToken("OP_LT");
    } else if (strcmp(token_atual.nome, "OP_LE") == 0) {
        CasaToken("OP_LE");
    } else if (strcmp(token_atual.nome, "OP_GT") == 0) {
        CasaToken("OP_GT");
    } else if (strcmp(token_atual.nome, "OP_GE") == 0) {
        CasaToken("OP_GE");
    } else {
        fprintf(stderr, "%d: relação não esperada [%s].\n", linha_atual, token_atual.lexema);
        exit(EXIT_FAILURE);
    }
}

void expressao_simples() {
    if (strcmp(token_atual.nome, "OP_AD") == 0 || strcmp(token_atual.nome, "OP_MIN") == 0) {
        CasaToken(token_atual.nome);
    }
    termo();
    while (strcmp(token_atual.nome, "OP_AD") == 0 || strcmp(token_atual.nome, "OP_MIN") == 0) {
        CasaToken(token_atual.nome);
        termo();
    }
}

void termo() {
    fator();
    while (strcmp(token_atual.nome, "OP_MUL") == 0 || strcmp(token_atual.nome, "OP_DIV") == 0) {
        CasaToken(token_atual.nome);
        fator();
    }
}

void fator() {
    if (strcmp(token_atual.nome, "ID") == 0) {
        CasaToken("ID"); // identificador
    } else if (strcmp(token_atual.nome, "NUM") == 0) {
        CasaToken("NUM"); // número
    } else if (strcmp(token_atual.nome, "SMB_OPA") == 0) {
        CasaToken("SMB_OPA"); // "("
        expressao();
        CasaToken("SMB_CPA"); // ")"
    } else {
        fprintf(stderr, "%d: fator não esperado [%s].\n", linha_atual, token_atual.lexema);
        exit(EXIT_FAILURE);
    }
}

void variavel() {
    CasaToken("ID"); // identificador
}
