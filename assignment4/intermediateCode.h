#include <stdbool.h>
#ifndef intermediate_code_h
#define intermediate_code_h

typedef enum Operator{
    ADD,
    SUB,
    MUL,
    DIV,
    GTO
} Operator;

typedef union Addrval{
    struct {TypeRecord type; char* id} variable;
    char* label;
    int intConstant;
    double floatConstant;
    bool boolConstant;
} Addrval;

typedef struct Addr{
    Addrval value;
    enum { VAR, INSTR, INT_CONST, FLOAT_CONST, BOOL_CONST, LABEL } kind;
} Addr;

typedef struct IntermediateInstruction{
    Operator opperator;
    Addr source1;
    Addr source2;
    Addr result;
} IntermediateInstruction;

typedef struct IntermediateCodeList{
    IntermediateInstruction* instructions;
    int size;
}IntermediateCodeList;

void appendInstruction(IntermediateCodeList* list, Addr target, Addr source1, Addr source2, Operator opperator);
char* opToString(Operator instr);
char* addrToString(Addr addr);
char* instructionToString(IntermediateInstruction instr);
void printIntermediateCodeList(IntermediateCodeList list);


#endif