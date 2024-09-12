#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct SymbolTableEntry {
    char* lexema;
    char* tipo;
    struct SymbolTableEntry* next;
} SymbolTableEntry;

void addToSymbolTable(const char* lexema, const char* tipo);
void printSymbolTable();

#endif // SYMBOL_TABLE_H
