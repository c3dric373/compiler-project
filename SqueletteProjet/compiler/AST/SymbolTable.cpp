#include "SymbolTable.h"


void SymbolTable::addSymbol(unsigned depth, std::string& symbol,  int offset){
    std::string newName = std::to_string(depth) + symbol;
    offsetMap[newName] = offset;
}

void SymbolTable::dispTable(){
	for (auto const& pair: offsetMap) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

bool SymbolTable::exists(unsigned depth,std::string &symbol) {
    std::string newName = std::to_string(depth) + symbol;
    if ( offsetMap.find(newName) == offsetMap.end() )
        return false;

    return true;
}


//----------------------------------------setters et getters------------------------------------------------

int SymbolTable::getOffset(unsigned depth, std::string& symbol){
    std::string newName = std::to_string(depth) + symbol;
    return offsetMap[newName];
}

void SymbolTable::setErrorTrue() {
    this->error=true;
}

void SymbolTable::addErrorMsg(std::string & msg) {
    errorMsg+=msg;
}

bool SymbolTable::getError() {
    return error;
}

std::string SymbolTable::getErrorMsg() {
    return errorMsg;
}
