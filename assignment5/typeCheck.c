#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "typeCheck.h"
//#include "parser.tab.h" 

typedef enum BasicType{
    INT,
    FLOAT,
    BOOL
} BasicType;

typedef struct DimensionList{
    int* dimensions;
    int numDimensions;
} DimensionList;

typedef struct TypeRecord{
    BasicType basic;
    DimensionList dimList;
} TypeRecord;

TypeRecord constructTypeRecord(BasicType basicType, DimensionList dimensions){
    TypeRecord* t = malloc(sizeof(TypeRecord));
    switch(basicType){
        case 0:
            t->basic = INT;
            break;
        case 1:
            t->basic = FLOAT;
            break;
        case 2:
            t->basic = BOOL;
            break;
        default: break;
    }
    t->dimList = dimensions;
    return *t;
}

int sizeOfType(TypeRecord t){
    int magnitude = 1;
    if(t.dimList.numDimensions != 0){
        for(int i = 0; i < t.dimList.numDimensions; i++){
            magnitude *= t.dimList.dimensions[i];
        }
    }

    switch(t.basic){
        case INT: return magnitude * sizeof(int);
        case FLOAT: return magnitude * sizeof(double);
        case BOOL: return magnitude;
        default: return -1;
    }
}

char* typeToString(TypeRecord t){
    char* string = "{ ";

    switch(t.basic){
        case INT: strcat(string, "int, ["); break;
        case FLOAT: strcat(string, "float, ["); break;
        case BOOL: strcat(string, "bool, ["); break;
        default: return "";
    }

    char* dimstr;
    for(int i = 0; i < t.dimList.numDimensions; i++){
        itoa(t.dimList.dimensions[i], dimstr, 10);
        strcat(string, dimstr);

        if(i < t.dimList.numDimensions - 1){
            strcat(string, ", ");
        }
    }

    free(dimstr);
    strcat(string, "] }");

    return string;
}

int freeTypeRecord(TypeRecord* t){
    if(t == NULL) return -1;
    if(t->dimList.numDimensions != 0)
        free(t->dimList.dimensions);
    free(t);
    return 0;
}


BasicType maxType(BasicType t1, BasicType t2){
    /*if(t1.dimList.numDimensions > 1 || t2.dimList.numDimensions > 1){
        yyerror("Type Mismatch: Cannot perform type conversions on arrays");
    }*/
    if(t1 == FLOAT || t2 == FLOAT){
        return FLOAT;
    } else if(t1 == INT || t2 == INT){
        return INT;
    } else if (t1 == BOOL || t2 == BOOL){
        return BOOL;
    }
    /*} else{
        yyerror("Type Mismatch: Type does not exist in type hierarchy");
    }*/
} 

int typesEqual(TypeRecord t1, TypeRecord t2){
    if(t1.basic != t2.basic) return 0;
    if(t1.dimList.numDimensions != t2.dimList.numDimensions) return 0;
    for(int i = 0; i < t1.dimList.numDimensions; i++){
        if(t1.dimList.dimensions[i] != t2.dimList.dimensions[i]) return 0;
    }
    return 1;
}