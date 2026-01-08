#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "ChainedSymbolTable.h"
#include "typeCheck.h"
#include "intermediateCode.h"

typedef enum Operator{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    LSH,
    RSH,
    FLTCAST,
    INTCAST,
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

void appendInstruction(IntermediateCodeList* list, Addr target, Addr source1, Addr source2, Operator opperator){
    IntermediateInstruction newInstruction;
    newInstruction.opperator = opperator;
    newInstruction.source1 = source1;
    newInstruction.source2 = source2;
    newInstruction.result = target;

    list->instructions[list->size] = newInstruction;
    list->size += 1;
}

char* opToString(Operator instr){
    switch(instr){
        case ADD: return ;
        case SUB: return "SUB";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case GTO: return "GTO";
        default: return "UNKNOWN INSTRUCTION";
    }
}

char* addrToString(Addr addr){
    switch(addr.kind){
        case VAR: return addr.value.variable.id;
        case LABEL: return addr.value.label;
        case INT_CONST: {
            static char buffer[20];
            sprintf(buffer, "%d", addr.value.intConstant);
            return buffer;
        }
        case FLOAT_CONST: {
            static char buffer[20];
            sprintf(buffer, "%f", addr.value.floatConstant);
            return buffer;
        }
        case BOOL_CONST: {
            return addr.value.boolConstant ? "true" : "false";
        }
        default: return "UNKNOWN ADDR TYPE";
    }
}

char* instructionToString(IntermediateInstruction instr){
    static char buffer[100];
    snprintf(buffer, sizeof(buffer), "%s = %s %s %s",
             addrToString(instr.result),
             addrToString(instr.source1),
             opToString(instr.opperator),
             addrToString(instr.source2));
    return buffer;
}

void printIntermediateCode(IntermediateCodeList* list){
    for(int i = 0; i < list->size; i++){
        printf("%s\n", intermediateCodeToString(list->instructions[i]));
    }
}

Binding createTempVar(TypeRecord type){
    static int tempVarCounter = 0;
    char* tempVarName = malloc(20 * sizeof(char));
    sprintf(tempVarName, "t%d", tempVarCounter++);
    
    Binding tempBinding;
    tempBinding.id = tempVarName;
    tempBinding.value = type;
    tempBinding.level = TEMP;    
    return tempBinding;
}

Addr widen(Addr a, TypeRecord t1, TypeRecord t2, SymbolTable* symTable, IntermediateCodeList* codeList){
    if(typeEqual(t1, t2) == 1){
        return a;
    }   
    else if(t1.basic == INT && t2.basic == FLOAT){
        Addr widenedAddr;
        widenedAddr.kind = VAR;
        TypeRecord floatType = constructTypeRecord(FLOAT, t2.dimList.dimensions);
        Binding tempVar = createTempVar(floatType);
        putTempBinding(symTable, &tempVar);
        appendInstruction(codeList, widenedAddr, a, (Addr){0}, INTCAST);
        return widenedAddr;
    } else{
        yyerror("Type Mismatch: Cannot widen types");
    }
}