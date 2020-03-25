#include "AST.h"

int INT_OFFSET = -4;
int DOUBLE_OFFSET = -8;
int offset =0;


std::string AST::Expr::Expr::makeAssembly(){
    return "";
}
void AST::Expr::Expr::display(){

}

std::string AST::Expr::Add::makeAssembly(){
    return "";
}
void AST::Expr::Add::display(){
    std::cout << "(ADD " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
//AST::Expr::Add::Add(AST::Expr::Expr* lValue, AST::Expr::Expr* rValue): lValue(lValue), rValue(rValue){}

std::string AST::Expr::Sub::makeAssembly(){
    return "";
}
void AST::Expr::Sub::display(){
    std::cout << "(SUB " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

std::string AST::Expr::Mult::makeAssembly(){
    return "";
}
void AST::Expr::Mult::display(){
    std::cout << "(MULT " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

std::string AST::Expr::Minus::makeAssembly(){
    return "";
}
void AST::Expr::Minus::display(){
    std::cout << "(MIN " << std::flush;
    value->display();
    std::cout << ')' << std::flush;
}

std::string AST::Expr::Const::makeAssembly(){
    return "";
}
void AST::Expr::Const::display(){
    std::cout << "(CONST " << value << ')' << std::flush;
}

std::string AST::Expr::Name::makeAssembly(){
    return "";
}
void AST::Expr::Name::display(){
    std::cout << "(NAME " << name << ')' << std::flush;
}
/*
std::string AST::Instr::Def::makeAssembly(SymbolTable st){
   int value = this->expr.getValeur();
   string name = this->name; 
   int  offset = st.getOffset(0,name);
   assembler_code = "mov" + " $" + std::to_string(value) +" "+  std::to_strin(offset) + "(%rbp)";
    return assembler_code
        // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, ) 
        // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset  
}*/


/*
int AST::Expr::Add::getValeur(){
   return this->lvalue.getValeur() + this->rvalue.getValeur();
}

int AST::Expr::Const::getValeur(){
    return this->value;
}
*/
std::string AST::Bloc::makeAssembly(){
    return "";
}
void AST::Bloc::pushInstr(Instr::Instr* instr){
    blocinstr.push_back(instr);
}
void AST::Bloc::display(){
    std::cout << "(BLOC " << std::flush;
    for(auto& it : blocinstr){
        it->display();
    }
    std::cout << ')' << std::flush;
}

std::string AST::Prog::makeAssembly(){
    return "";
}
void AST::Prog::display(){
    std::cout << "(AST " << std::flush;
    bloc->display();
    std::cout << ", " << std::flush;
    returnValue->display();
    std::cout << ")" << std::endl;
    }
/*
void AST::Prog::create_symbol_table(){
  this->symbolTable = SymbolTable();
  Bloc child = this->bloc; 
  child.addToTable(this->symbolTable);

}
void AST::Bloc::addToTable(SymbolTable st){
    for(auto& it : blocinstr){
         it->addToTable(st);
    }
}

void Def::addToTable(SymbolTable st){
    st.addSymbol(0, this->name , offset = offset-INT_OFFSET);
    // offset comme atribue de la table de symbole 
}*/
void AST::Instr::Decl::display(){
    std::cout << "(DECL " << std::flush;
    for(auto& it : names){
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}
void AST::Instr::Def::display(){
    std::cout << "(DEF " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}
void AST::Instr::Affct::display(){
    std::cout << "(AFF " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}
void AST::Instr::If::display(){
    std::cout << "(IF " << std::flush;
    expr->display();
    bloc->display();
    std::cout << ')' << std::flush;
}
void AST::Instr::Instr::display(){

}
void AST::Expr::Eq::display(){
    std::cout << "(EQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Neq::display(){
    std::cout << "(NEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Leq::display(){
    std::cout << "(LEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Low::display(){
    std::cout << "(LOW " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Geq::display(){
    std::cout << "(GEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Great::display(){
    std::cout << "(GRT " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}
void AST::Expr::Not::display(){
    std::cout << "(NOT " << std::flush;
    value->display();
    std::cout << ')' << std::flush;
}
std::string AST::Expr::Not::makeAssembly(){
    return Expr::makeAssembly();
}
