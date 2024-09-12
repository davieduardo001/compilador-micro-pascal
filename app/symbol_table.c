#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static SymbolTableEntry* symbolTable = NULL;

static SymbolTableEntry* createEntry(const char* lexema, const char* tipo) {
    SymbolTableEntry* entry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    entry->lexema = strdup(lexema);
    entry->tipo = strdup(tipo);
    entry->next = NULL;
    return entry;
}

void addToSymbolTable(const char* lexema, const char* tipo) {
    SymbolTableEntry* entry = createEntry(lexema, tipo);
    entry->next = symbolTable;
    symbolTable = entry;
}

void printSymbolTable() {
    SymbolTableEntry* current = symbolTable;
    while (current != NULL) {
        printf("Lexema: %s, Tipo: %s\n", current->lexema, current->tipo);
        current = current->next;
    }
}
