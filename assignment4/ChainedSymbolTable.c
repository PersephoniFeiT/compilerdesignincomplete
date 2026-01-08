#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "typeCheck.h"
#include "ChainedSymbolTable.h"

#define DEFAULTPRIME 31     //radix factor used for generating the hash function
#define DEFAULTCAPACITY 63  //default capacity of each table for the demo.

typedef struct Binding {
    char* id;
    TypeRecord* value;
    enum { SOURCE, TEMP } level;
    Binding* next; //linked list handling of hashtable collisions    
} Binding;

typedef struct SymbolTable {
    Binding** buckets;
    int size;
    SymbolTable* prev; //chaining reference
} SymbolTable;

int hash(char* id);
void put(SymbolTable* env, char* id, TypeRecord val);
TypeRecord* get(SymbolTable* env, char* id);
void printContents(SymbolTable* tailTable);
void removeBinding(SymbolTable* env, char* id);
SymbolTable* constructTable(int size, SymbolTable* prev);

/**
 * Produces a hash value from a given String id using the formula
 * 
 * SUM (char value * DEFAULTPRIME) for each char in the string
 */
int hash(char* id){
    int hash = 0;
    for(int i = 0; i < strlen(id); i++){
        hash += (((int) id[i]) * DEFAULTPRIME);
    }

    return hash;
}

/**
 * Inserts a binding given id and value val into the tail of a Symbol Table chain env
 */
void put(SymbolTable* env, char* id, TypeRecord* val){
    Binding* newBinding = (Binding*)malloc(sizeof(Binding));
    newBinding->id = id;
    newBinding->value = val;
    newBinding->level = SOURCE;
    newBinding->next = NULL;

    int index = hash(id) % env->size;

    if(env->buckets[index] == NULL){
        env->buckets[index] = newBinding;
    } else{
        Binding* collision = env->buckets[index];

        if(strcmp(id, collision->id) == 0 && collision->level == SOURCE){ //assume if id is same we want to reassign the value instead of inserting an identical id
            free(newBinding);              //no longer need newBinding as an object in memory. We have the existing binding in the table
            collision->value = val;
        } else{                             //actual collision case
            env->buckets[index] = newBinding;
            newBinding->next = collision;
        }
    }
}

void putTempBinding(SymbolTable* env, Binding* tempBinding){
    int index = hash(tempBinding->id) % env->size;

    if(env->buckets[index] == NULL){
        env->buckets[index] = tempBinding;
    } else{
        Binding* collision = env->buckets[index];

        if(strcmp(tempBinding->id, collision->id) == 0 && collision->level == SOURCE){ //assume if id is same we want to reassign the value instead of inserting an identical id
            free(tempBinding);              //no longer need newBinding as an object in memory. We have the existing binding in the table
            collision->value = tempBinding->value;
        } else{                             //actual collision case
            env->buckets[index] = tempBinding;
            tempBinding->next = collision;
        }
    }
}

/**
 * Searches through the symbol table chain given the tail env for a binding of a given id and returns the value bound to that id
 */
TypeRecord* get(SymbolTable* env, char* id){
    while(env != NULL){
        int index = hash(id) % env->size;
        Binding* binding = env->buckets[index];
        while(binding != NULL){
            if(strcmp(binding->id, id) == 0){
                return binding->value;
            } else(binding = binding->next);
        }
        env = env->prev;

    }
    return; //some sort of error handling idk
}

/**
 * Searches through the symbol table chain given the tail env for a binding of a given id and removes the earliest instance of that binding
 */
void removeBinding(SymbolTable* env, char* id){
    while(env != NULL){
        int index = hash(id) % env->size;
        Binding* binding = env->buckets[index];
        while(binding != NULL){
            if(strcmp(binding->id, id) == 0){
                binding = binding->next;
                free(env->buckets[index]);
                env->buckets[index] = binding;
            } else(binding = binding->next);
        }
        env = env->prev;
    }
}

/**
 * function that prints out the contents of a symbol table chain given tailtable as the current environment
 * prints in the format
 * `[id] : [value]`
 * connecting to the previous table in the chain with a `|` character
 */
void printContents(SymbolTable* tailtable){
    printf("---\n");
    while(tailtable != NULL){
        for(int i = 0; i < tailtable->size; i++){
            Binding* entryptr = tailtable->buckets[i];
            while(entryptr != NULL){
                printf("%s: %s\n", entryptr->value, entryptr->id);
                entryptr = entryptr->next;
            }
        }
        if(tailtable->prev != NULL){
            printf("|\n");
        }
        tailtable = tailtable->prev;
    }
    printf("---\n");
}

/**
 * Constructor that allocates and returns an empty table with a capacity size and a previous environment prev
 */
SymbolTable* constructTable(int size, SymbolTable* prev){
    SymbolTable* newTable = (SymbolTable*) malloc(sizeof(SymbolTable));
    newTable->size = size;
    newTable->buckets = (Binding**)(malloc( sizeof(Binding*) * size));
    newTable->prev = prev;
}


void putTempBinding(SymbolTable* env, char* id, TypeRecord* val){
    Binding* newBinding = (Binding*)malloc(sizeof(Binding));
    newBinding->id = id;
    newBinding->value = val;
    newBinding->level = TEMP;
    newBinding->next = NULL;

    int index = hash(id) % env->size;

    if(env->buckets[index] == NULL){
        env->buckets[index] = newBinding;
    } else{
        Binding* collision = env->buckets[index];

        if(strcmp(id, collision->id) == 0 && collision->level == SOURCE){ //assume if id is same we want to reassign the value instead of inserting an identical id
            free(newBinding);              //no longer need newBinding as an object in memory. We have the existing binding in the table
            collision->value = val;
        } else{                             //actual collision case
            env->buckets[index] = newBinding;
            newBinding->next = collision;
        }
    }
}
