#ifndef CHAINED_SYMBOL_TABLE_H
#define CHAINED SYMBOL_TABLE_H

#define DEFAULTPRIME 31     //radix factor used for generating the hash function
#define DEFAULTCAPACITY 63  //default capacity of each table for the demo.

typedef struct Binding {
    char* id;
    TypeRecord value;
    enum { SOURCE, TEMP } level;
    struct Binding* next; //linked list handling of hashtable collisions    
} Binding;


typedef struct SymbolTable {
    Binding** buckets;
    int size;
    struct SymbolTable* prev; //chaining reference
} SymbolTable;

int hash(char* id);
void put(SymbolTable* env, char* id, TypeRecord val);
void putTempBinding(SymbolTable* env, Binding* tempBinding);
TypeRecord get(SymbolTable* env, char* id);
void printContents(SymbolTable* tailTable);
void removeBinding(SymbolTable* env, char* id);
SymbolTable* constructTable(int size, SymbolTable* prev);

#endif
