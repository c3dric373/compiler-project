#include "AST.h"

int INT_OFFSET = -4;
int DOUBLE_OFFSET = -8;
int offset =0;


std::string AST::Expr::Expr::makeAssembly(){
    return "";
}

std::string AST::Expr::Add::makeAssembly(){
    return "";
}
//AST::Expr::Add::Add(AST::Expr::Expr* lValue, AST::Expr::Expr* rValue): lValue(lValue), rValue(rValue){}

std::string AST::Expr::Sub::makeAssembly(){
    return "";
}

std::string AST::Expr::Mult::makeAssembly(){
    return "";
}

std::string AST::Expr::Minus::makeAssembly(){
    return "";
}

//std::string AST::Expr::Par::makeAssembly(){
//    return "";
//}

std::string AST::Expr::Const::makeAssembly(){
    return "";
}

std::string AST::Expr::Name::makeAssembly(){
    return "";
}

std::string AST::Def::makeAssembly(SymbolTable st){
   int value = this->expr.getValeur();
   string name = this->name; 
   int  offset = st.getOffset(0,name);
   assembler_code = "mov" + " $" + std::to_string(value) +" "+  std::to_strin(offset) + "(%rbp)";
    return assembler_code
        // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, ) 
        // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset  
}



int AST::Expr::Add::getValeur(){
   return this->lvalue.getValeur() + this->rvalue.getValeur();
}

int AST::Expr::Const::getValeur(){
    return this->value;
}

std::string AST::Bloc::makeAssembly(){
    return "";
}
void AST::Bloc::pushDef(AST::Def* def){
    defs.push_back(def);
}

std::string AST::Prog::makeAssembly(){
    return "";
}

void AST::Prog::create_symbol_table(){
  this->symbolTable = SymbolTable();
  Bloc child = this->bloc; 
  child.addToTable(this->symbolTable);

}
void Bloc::addToTable(SymbolTable st){
    for(auto& it : defs){
         it->addToTable(st);
    }
} 

void Def::addToTable(SymbolTable st){
    st.addSymbol(0, this->name , offset = offset-INT_OFFSET);
    // offset comme atribue de la table de symbole 
}
