# C compiler with antlr4/c++

## Supported features 
-Types allowed : int and char
-Expressions allowed: arythmetic and binary 
-Arrays : Mono-dimentional arrays of constant size
-Loops : if, if/else, while, for(even without the 2nd and/or 3rd arguments)
-Procedures : simples, nested, recursives
-Functions : simples, nested, recursives

## Instructions
1. Compiling the environnement
Go to "compiler" folder and execute one of the 3 scripts of the section "Compilation scripts" below.
2. Launching the compiler on a file
To launch the compiler on a c file that is placed in "compiler" folder execute the command  "./ifcc file.c"

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed.

## Source Files
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser on the  file name provided in the command line.
- `visitor.h` is a visitor of the parse tree that produces an assembly-language output






