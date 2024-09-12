#ifndef LEXER_H
#define LEXER_H

typedef struct {
    char* nome;
    char* lexema;
    int linha;
    int coluna;
} Token;

void initializeLexer(const char *filename);
Token getNextToken();
void generateOutputFile(const char *filename);

#endif // LEXER_H
