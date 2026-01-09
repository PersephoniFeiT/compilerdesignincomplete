CC = gcc
LEX = flex
BISON = bison
CFLAGS = -g -Wall

TARGET = myparser
OBJS = main.o ChainedSymbolTable.o typeCheck.o intermediateCode.o parser.tab.o lex.yy.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lfl -o $(TARGET)

main.o: main.c typeCheck.h intermediateCode.h ChainedSymbolTable.h parser.tab.h
	$(CC) $(CFLAGS) -c main.c

parser.tab.o: parser.tab.c parser.y ChainedSymbolTable.h typeCheck.h intermediateCode.h
	$(CC) $(CFLAGS) -c parser.tab.c

parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

lex.yy.o: lex.yy.c lexer.l parser.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: lexer.l parser.tab.h
	$(LEX) lexer.l

ChainedSymbolTable.o: ChainedSymbolTable.c ChainedSymbolTable.h
	$(CC) $(CFLAGS) -c ChainedSymbolTable.c

intermediateCode.o: intermediateCode.c intermediateCode.h
	$(CC) $(CFLAGS) -c intermediateCode.c

typeCheck.o: typeCheck.c typeCheck.h
	$(CC) $(CFLAGS) -c typeCheck.c

clean:
	rm -f $(TARGET) $(OBJS) parser.tab.c parser.tab.h lex.yy.c