#include <stdio.h>
#include "lexer.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", argv[1]);
        return 1;
    }

    iniciar_tabela_de_simbolos(); // Inicializa palavras reservadas
    analisar_lexico(arquivo);     // Analisa o arquivo

    fclose(arquivo);
    return 0;
}
