#include <stdio.h>
#include <stddef.h> // Para NULL
#include <stdlib.h> // Para outras utilidades, se necessário
#include <string.h> // Para strcmp, se necessário

// Supondo que as funções estejam declaradas em algum cabeçalho incluído
void iniciar_tabela_de_simbolos(void);
void analisar_lexico(FILE *arquivo);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo de entrada: %s\n", argv[1]);
        perror("Erro");
        return 1;
    }

    iniciar_tabela_de_simbolos();
    analisar_lexico(arquivo);

    fclose(arquivo);
    return 0;
}
