#include "SymbolTable.h"

void SymbolTable::addSymbol(unsigned depth, std::string& symbol, std::string& address, std::string& offset){
    std::string newName = std::to_string(depth) + symbol;
    addressMap[newName] = address;
    offsetMap[newName] = offset;
}
std::string SymbolTable::getMem(unsigned depth, std::string& symbol){
    std::string newName = std::to_string(depth) + symbol;
    return addressMap[newName];
}
std::string SymbolTable::getOffset(unsigned depth, std::string& symbol){
    std::string newName = std::to_string(depth) + symbol;
    return offsetMap[newName];
}
