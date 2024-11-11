// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

// Função para exibir a ajuda detalhada
void exibir_ajuda(const char *nome_programa) {
    printf("Uso: %s <arquivo de entrada>\n", nome_programa);
    printf("\n");
    printf("Este programa realiza a análise léxica e sintática de um arquivo de entrada, identificando tokens e verificando a conformidade sintática.\n");
    printf("\nOpções:\n");
    printf("  -h, --help         Exibe esta mensagem de ajuda\n");
    printf("  --tokens           Exibe a lista de tokens suportados\n");
    printf("\nExemplo de uso:\n");
    printf("  %s programa.txt\n", nome_programa);
}

// Função para exibir a lista de tokens suportados pelo compilador
void exibir_lista_de_tokens() {
    printf("Lista de Tokens Suportados:\n\n");
    printf("  Palavras reservadas:\n");
    printf("    * program\n");
    printf("    * var\n");
    printf("    * integer\n");
    printf("    * real\n");
    printf("    * begin\n");
    printf("    * end\n");
    printf("    * if\n");
    printf("    * then\n");
    printf("    * else\n");
    printf("    * while\n");
    printf("    * do\n");
    printf("    * write\n");
    printf("    * read\n");

    printf("\n  Operadores:\n");
    printf("    * +    (Adição)\n");
    printf("    * -    (Subtração)\n");
    printf("    * *    (Multiplicação)\n");
    printf("    * /    (Divisão)\n");
    printf("    * =    (Atribuição)\n");
    printf("    * >    (Maior)\n");
    printf("    * >=   (Maior ou igual)\n");
    printf("    * <    (Menor)\n");
    printf("    * <=   (Menor ou igual)\n");
    printf("    * <>   (Diferente)\n");
    printf("    * :=   (Atribuição)\n");

    printf("\n  Símbolos:\n");
    printf("    * ;    (Ponto e vírgula)\n");
    printf("    * ,    (Vírgula)\n");
    printf("    * {    (Chave de abertura)\n");
    printf("    * }    (Chave de fechamento)\n");
    printf("    * (    (Parêntese de abertura)\n");
    printf("    * )    (Parêntese de fechamento)\n");
    printf("    * .    (Ponto final)\n");
    printf("    * :    (Dois pontos)\n");

    printf("\n  Outros tokens:\n");
    printf("    * ID   (Identificadores)\n");
    printf("    * NUM  (Números)\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Verifica se o argumento -h ou --help foi passado
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        exibir_ajuda(argv[0]);
        return 0;
    }

    if (argc < 2) {
        printf("Uso: %s <arquivo de entrada>\n", argv[0]);
        printf("Use -h ou --help para obter mais informações.\n");
        return 1;
    }

    // Verifica se o argumento --tokens foi passado
    if (argc == 2 && strcmp(argv[1], "--tokens") == 0) {
        exibir_lista_de_tokens();
        return 0;
    }

    FILE *arquivo_entrada = fopen(argv[1], "r");
    if (arquivo_entrada == NULL) {
        fprintf(stderr, "Não foi possível abrir o arquivo de entrada: %s\n", argv[1]);
        perror("Erro");
        return 1;
    }

    // Cria o nome do arquivo de saída com a extensão .lex
    char arquivo_saida_nome[256];
    snprintf(arquivo_saida_nome, sizeof(arquivo_saida_nome), "%s.lex", argv[1]);

    FILE *arquivo_saida = fopen(arquivo_saida_nome, "w");
    if (arquivo_saida == NULL) {
        fprintf(stderr, "Não foi possível criar o arquivo de saída: %s\n", arquivo_saida_nome);
        perror("Erro");
        fclose(arquivo_entrada);
        return 1;
    }

    iniciar_tabela_de_simbolos();
    analisar_lexico(arquivo_entrada, arquivo_saida);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Processamento concluído. Saída gerada em: %s\n", arquivo_saida_nome);

    // Reabra o arquivo de entrada para análise sintática
    arquivo_entrada = fopen(argv[1], "r");
    if (arquivo_entrada == NULL) {
        fprintf(stderr, "Não foi possível reabrir o arquivo de entrada: %s\n", argv[1]);
        perror("Erro");
        return 1;
    }

    // Chamar o parser para análise sintática
    parser(arquivo_entrada, arquivo_saida);
    fclose(arquivo_entrada);

    printf("Análise sintática concluída.\n");
    return 0;
}
