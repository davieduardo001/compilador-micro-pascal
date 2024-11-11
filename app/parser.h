// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Variáveis globais
extern FILE *arquivo_entrada;
extern FILE *arquivo_saida;

// Funções de análise sintática
void parser(FILE *arquivo_entrada, FILE *arquivo_saida);
void CasaToken(const char *token_esperado);
void programa();
void bloco();
void parte_declaracoes_variaveis();
void declaracao_variaveis();
void lista_identificadores();
void tipo();
void comando_composto();
void comando();
void atribuicao();
void comando_condicional();
void comando_repetitivo();
void expressao();
void relacao();
void expressao_simples();
void termo();
void fator();
void variavel();

#endif // PARSER_H
