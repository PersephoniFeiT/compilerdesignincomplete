#ifndef TYPE_CHECK_H
#define TYPE_CHECK_H

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

TypeRecord constructTypeRecord(BasicType basicType, int* dimension);
char* typeToString(TypeRecord t);
int sizeOfType(TypeRecord t);
int freeTypeRecord(TypeRecord* t);
int typeEqual(TypeRecord t1, TypeRecord t2);

#endif