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
   int value = this->expr->getValeur();
   std::string name = this->name;
   int  offset = st.getOffset(0,name);
   std::string assembler_code = "mov $" + std::to_string(value) +" "+  std::to_string(offset) + "(%rbp)";
    return assembler_code;
        // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, ) 
        // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset  
}

int AST::Expr::Sub::getValeur(){
   return this->lValue->getValeur() + this->rValue->getValeur();
}

int AST::Expr::Minus::getValeur(){
   return 0;
}
int AST::Expr::Mult::getValeur(){
   return this->lValue->getValeur() + this->rValue->getValeur();
}

int AST::Expr::Name::getValeur(){
   return 0;
}




int AST::Expr::Add::getValeur(){
   return this->lValue->getValeur() + this->rValue->getValeur();
}

int AST::Expr::Const::getValeur(){
    return this->value;
}

std::string AST::Bloc::makeAssembly(SymbolTable st){
    std::string assembler_code = "";
      for(auto& it : defs){
          assembler_code += it->makeAssembly(st);
      }

    return "";
}
void AST::Bloc::pushDef(AST::Def* def){
       defs.push_back(def);
}

std::string AST::Prog::makeAssembly(){
    std::string prolog = "pushq   %rbp\n     movq    %rsp, %rbp\n";
    Bloc* child = this->bloc;    
    std::string assembler_code = child->makeAssembly(this->table);
    std::string epilog = "popq    %rbp\n     ret";
    return prolog + assembler_code + epilog;
}

void AST::Prog::create_symbol_table(){
  //this->table =  SymbolTable();
  Bloc* child = this->bloc;
  child->addToTable(table);

}
void AST::Bloc::addToTable(SymbolTable st){
    for(auto& it : defs){
         it->addToTable(st);
    }
} 

void AST::Def::addToTable(SymbolTable st){
    st.addSymbol(0, this->name , offset = offset-INT_OFFSET);
    // offset comme atribue de la table de symbole 
}
