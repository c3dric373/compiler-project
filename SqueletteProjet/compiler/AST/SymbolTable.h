#ifndef AST_SYMBOLTABLE_H
#define AST_SYMBOLTABLE_H

#include <unordered_map>
#include <utility>
#include <iostream>

class SymbolTable{
public:
    void addSymbol(unsigned depth, std::string& symbol, int offset);
    int getOffset(unsigned depth, std::string& symbol);
    bool exists(unsigned depth,std::string& symbol);
    void setErrorTrue();
    bool getError();
    std::string getErrorMsg();
    void addErrorMsg(std::string & msg);
	void dispTable();

private:
    std::unordered_map<std::string, int> offsetMap;
    std::string errorMsg;
    bool error;
};

#endif //AST_SYMBOLTABLE_H
