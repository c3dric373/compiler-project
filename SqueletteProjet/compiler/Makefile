OUTPUT=output
GENERATED=antlr4-generated
GRAMMAR=ifcc.g4

#override with your local installation
ANTLR4_BINDIR=/shares/public/tp/ANTLR4-CPP/bin
ANTLR4_INCDIR=/shares/public/tp/ANTLR4-CPP/antlr4-runtime
ANTLR4_LIBDIR=/shares/public/tp/ANTLR4-CPP/lib

CC=clang++
CCARGS=-g -c -I $(ANTLR4_INCDIR) -I $(GENERATED) -std=c++11 -Wno-defaulted-function-deleted -Wno-unknown-warning-option
LDARGS=-g

all: ifcc

ifcc: dirs antlr  main.cpp visitor.cpp visitor.h AST/AST.cpp AST/AST.h IR/IR.h IR/IR.cpp Erreur/Erreur.h Erreur/Erreur.cpp
	$(CC) $(CCARGS) main.cpp  -o $(OUTPUT)/main.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccBaseVisitor.cpp -o $(OUTPUT)/ifccBaseVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccLexer.cpp -o $(OUTPUT)/ifccLexer.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccVisitor.cpp -o $(OUTPUT)/ifccVisitor.o 
	$(CC) $(CCARGS) $(GENERATED)/ifccParser.cpp -o $(OUTPUT)/ifccParser.o 
	$(CC) $(CCARGS) visitor.cpp -o $(OUTPUT)/visitor.o 
	$(CC) $(CCARGS) Erreur/Erreur.cpp -o $(OUTPUT)/Erreur.o
	$(CC) $(CCARGS) AST/AST.cpp -o $(OUTPUT)/AST.o 
	$(CC) $(CCARGS) IR/IR.cpp -o $(OUTPUT)/IR.o
	$(CC) $(LDARGS) $(OUTPUT)/main.o $(OUTPUT)/ifccBaseVisitor.o $(OUTPUT)/AST.o $(OUTPUT)/Erreur.o $(OUTPUT)/IR.o $(OUTPUT)/ifccLexer.o $(OUTPUT)/ifccVisitor.o $(OUTPUT)/ifccParser.o $(OUTPUT)/visitor.o $(ANTLR4_LIBDIR)/libantlr4-runtime.a -o ifcc

antlr: $(GRAMMAR)
	$(ANTLR4_BINDIR)/antlr4 -visitor -no-listener -Dlanguage=Cpp -o $(GENERATED) $(GRAMMAR)

dirs:
	mkdir -p $(OUTPUT)
	mkdir -p $(GENERATED)

clean:
	rm -rf $(OUTPUT)
	rm -rf $(GENERATED)

test:
	@bash -c "cd ../tests; sh test_if.sh"
