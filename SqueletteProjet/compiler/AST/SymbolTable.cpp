#include "SymbolTable.h"


void SymbolTable::addSymbol(unsigned depth, std::string& symbol,  int offset){
    std::string newName = std::to_string(depth) + symbol;
    offsetMap[newName] = offset;
}

int SymbolTable::getOffset(unsigned depth, std::string& symbol){
    std::string newName = std::to_string(depth) + symbol;
    return offsetMap[newName];
}
