#ifndef AST_SYMBOLTABLE_H
#define AST_SYMBOLTABLE_H

#include <map>
#include <utility>

class SymbolTable{
public:
    void addSymbol(unsigned depth, std::string& symbol, std::string& address, std::string& offset);
    std::string getMem(unsigned depth, std::string& symbol);
    std::string getOffset(unsigned depth, std::string& symbol);

private:
    std::map<std::string, std::string> addressMap;
    std::map<std::string, std::string> offsetMap;
};

#endif //AST_SYMBOLTABLE_H
