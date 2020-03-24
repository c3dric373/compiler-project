#include "AST.h"

int INT_OFFSET = 4;
int offset =0;


std::string AST::Expr::Expr::makeAssembly(SymbolTable &st){
    return "";
}

std::string AST::Expr::Add::makeAssembly(SymbolTable &st){
    // Return value of expression always in eax
    std::string lValue_code= this-> lValue->makeAssembly(st);
    std::string move_lValue =  "\tmovl %eax, %ebx\n";
    std::string rValue_code = this-> rValue->makeAssembly(st);
    std::string addition_code = "\taddl %ebx, %eax\n";
    return lValue_code + move_lValue + rValue_code + addition_code;
}

std::string AST::Expr::Sub::makeAssembly(SymbolTable &st){
    return "";
}

std::string AST::Expr::Mult::makeAssembly(SymbolTable &st){
    return "";
}

std::string AST::Expr::Minus::makeAssembly(SymbolTable &st){
    return "";
}

std::string AST::Expr::Const::makeAssembly(SymbolTable &st){
   int value = this->value;
    std::string assembler_code = "\tmovl $" + std::to_string(value) + ", %eax\n";
    return assembler_code;
}

std::string AST::Expr::Name::makeAssembly(SymbolTable &st){
    int value = st.getOffset(0,name);
    std::string code_move_variable = "\tmovl -" + std::to_string(value) + " (%rbp) " + ", %eax\n";
    return code_move_variable;
}

std::string AST::Instr::Def::makeAssembly(SymbolTable &st){
   std::string valeur_code = this->expr->makeAssembly(st);
   std::string name = this->name;
   int  offset = st.getOffset(0,name);
    std::string assembler_code = "\tmovl %eax, -"+  std::to_string(offset) + "(%rbp)\n";
    return valeur_code + assembler_code;
        // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, ) 
        // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset  
}

std::string AST::Instr::Affct::makeAssembly(SymbolTable &st){
    std::string assembleur_expr = this->expr->makeAssembly(st);
    std::string name = this->name;
    int  offset = st.getOffset(0,name);
    std::string assembler_code = assembleur_expr + "\tmovl  %eax,  -"+  std::to_string(offset) + "(%rbp)\n";
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
   return 55;
}

int AST::Expr::Const::getValeur(){
    return this->value;
}

std::string AST::Bloc::makeAssembly(SymbolTable& st){
    std::string assembler_code = "";
      for(auto& it : blocinstr){
          assembler_code += it->makeAssembly(st);
      }

    return assembler_code;
}

void AST::Bloc::pushInstr(Instr::Instr* instr){
    blocinstr.push_back(instr);
}

std::string AST::Prog::makeAssembly(){
    std::string prolog = ".globl\tmain\nmain:\n\tpushq %rbp\n\tmovq %rsp, %rbp\n";
    Bloc* child = this->bloc;    
    std::string assembler_code = child->makeAssembly(this->table);
	std::string assembler_code_return = this->returnValue->makeAssembly(this->table);
    std::string epilog = assembler_code_return+"\tpopq %rbp\n\tret\n";
    return prolog + assembler_code + epilog;
}

void AST::Prog::create_symbol_table(){
  this->table =  SymbolTable();
  Bloc* child = this->bloc;
  child->addToTable(table);

}

void AST::Bloc::addToTable(SymbolTable &st) {
    for (auto &it : blocinstr) {
        it->addToTable(st);
        }
    }

    void AST::Instr::Def::addToTable(SymbolTable &st) {
        st.addSymbol(0, this->name, offset = offset + INT_OFFSET);
        // offset comme atribue de la table de symbole
}
void AST::Instr::Decl::addToTable(SymbolTable &st) {
    for (auto &it : this->names) {
        st.addSymbol(0, it, offset = offset + INT_OFFSET);
    }
}
void AST::Instr::Affct::addToTable(SymbolTable &st) {

}
std::string AST::Instr::Decl::makeAssembly(SymbolTable& st){
    return "";
}






