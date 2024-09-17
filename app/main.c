#include <stdio.h>
#include <stddef.h> // Para NULL
#include <stdlib.h> // Para outras utilidades
#include <string.h> // Para manipulação de strings
#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo_entrada = fopen(argv[1], "r");
    if (arquivo_entrada == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo de entrada: %s\n", argv[1]);
        perror("Erro");
        return 1;
    }

    // Cria o nome do arquivo de saída com a extensão .out
    char arquivo_saida_nome[256];
    snprintf(arquivo_saida_nome, sizeof(arquivo_saida_nome), "%s.lex", argv[1]);

    FILE *arquivo_saida = fopen(arquivo_saida_nome, "w");
    if (arquivo_saida == NULL) {
        fprintf(stderr, "Não foi possível criar o arquivo de saída: %s\n", arquivo_saida_nome);
        perror("Erro");
        fclose(arquivo_entrada);
        return 1;
    }

    // Adiciona uma linha no início do arquivo de saída
    fprintf(arquivo_saida, "Este arquivo foi gerado automaticamente. Arquivo de entrada: %s\n\n", argv[1]);

    iniciar_tabela_de_simbolos();
    analisar_lexico(arquivo_entrada, arquivo_saida);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Processamento concluído. Saída gerada em: %s\n", arquivo_saida_nome);

    return 0;
}
