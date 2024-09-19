#include <stdio.h>
#include <stddef.h> // Para NULL
#include <stdlib.h> // Para outras utilidades
#include <string.h> // Para manipulação de strings
#include "lexer.h"

// Função para exibir a ajuda detalhada
void exibir_ajuda(const char *nome_programa) {
    printf("Uso: %s <arquivo de entrada>\n", nome_programa);
    printf("\n");
    printf("Este programa realiza a análise léxica de um arquivo de entrada, identificando tokens como:\n");
    printf("  - Identificadores\n");
    printf("  - Palavras reservadas\n");
    printf("  - Operadores (+, -, *, /, >, <, =, etc.)\n");
    printf("  - Símbolos (parênteses, chaves, ponto e vírgula, etc.)\n");
    printf("\n");
    printf("Durante o processamento, o programa gera um arquivo de saída com a extensão \".lex\", que contém os tokens\n");
    printf("identificados no seguinte formato: <TOKEN_NOME, TOKEN_LEXEMA> na linha X, coluna Y.\n");
    printf("\nOpções:\n");
    printf("  -h, --help         Exibe esta mensagem de ajuda\n");
    printf("  --tokens           Exibe a lista de tokens suportados\n");
    printf("\nExemplo de uso:\n");
    printf("  %s programa.txt\n", nome_programa);
    printf("\nDetalhes das funcionalidades:\n");
    printf("  - Análise léxica: O programa lê o arquivo de entrada e identifica os tokens presentes.\n");
    printf("  - Tokens suportados:\n");
    printf("    * Palavras reservadas: program, var, integer, real, begin, end, if, then, else, while, do, write, read\n");
    printf("    * Operadores: +, -, *, /, >, >=, <, <=, <>, =, :=\n");
    printf("    * Símbolos: ; , { } ( ) . :\n");
    printf("  - Tratamento de erros: Se encontrar um caractere inválido, o programa reporta um erro léxico com a linha e coluna.\n");
    printf("  - Geração de arquivo de saída: A saída é gerada em um arquivo com o mesmo nome do arquivo de entrada, mas com a\n");
    printf("    extensão \".lex\" contendo os tokens identificados.\n");
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

    iniciar_tabela_de_simbolos();
    analisar_lexico(arquivo_entrada, arquivo_saida);

    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    printf("Processamento concluído. Saída gerada em: %s\n", arquivo_saida_nome);

    return 0;
}