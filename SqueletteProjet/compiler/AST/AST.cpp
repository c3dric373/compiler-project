#include "AST.h"

int INT_OFFSET = 4;
int offset = 0;


//-------------------MakeAssembly-----------------------


std::string AST::Instr::While::makeAssembly(SymbolTable &st) {
    return std::string();
}


std::string AST::Expr::Add::makeAssembly(SymbolTable &st) {
    // Return value of expression always in eax
    std::string lValue_code = this->lValue->makeAssembly(st);
    std::string name_var_temp = "!tmp" + std::to_string(offset);
    st.addSymbol(0, name_var_temp, offset += INT_OFFSET);
    int start_offset = offset;
    std::string move_lValue = "\tmovl %eax, -" + std::to_string(start_offset) + " (%rbp)\n";
    std::string rValue_code = this->rValue->makeAssembly(st);
    std::string addition_code = "\taddl -" + std::to_string(start_offset) + " (%rbp) , %eax\n";
    return lValue_code + move_lValue + rValue_code + addition_code;
}

std::string AST::Expr::Sub::makeAssembly(SymbolTable &st) {
    // Return value of expression always in eax
    // Calculate rValue first in order to facilitate the result calculation
    std::string lValue_code = this->lValue->makeAssembly(st);
    std::string name_var_temp = "!tmp" + std::to_string(offset);
    st.addSymbol(0, name_var_temp, offset += INT_OFFSET);
    int start_offset = offset;
    std::string move_lValue = "\tmovl %eax, -" + std::to_string(start_offset) + " (%rbp)\n";
    std::string rValue_code = this->rValue->makeAssembly(st);
    std::string name_var_temp1 = "!tmp" + std::to_string(offset);
    st.addSymbol(0, name_var_temp1, offset += INT_OFFSET);
    int start_offset1 = offset;
    std::string move_rValue = "\tmovl %eax, -" + std::to_string(start_offset1) + " (%rbp)\n";
    std::string moveLValue_eax = "\tmovl -" + std::to_string(start_offset) + " (%rbp), %eax\n";
    std::string substraction_code = "\tsubl -" + std::to_string(start_offset1) + " (%rbp), %eax\n";
    return lValue_code + move_lValue + rValue_code + move_rValue + moveLValue_eax + substraction_code;
}

std::string AST::Expr::Mult::makeAssembly(SymbolTable &st) {
    // Return value of expression always in eax
    std::string lValue_code = this->lValue->makeAssembly(st);
    std::string name_var_temp = "!tmp" + std::to_string(offset);
    st.addSymbol(0, name_var_temp, offset += INT_OFFSET);
    int start_offset = offset;
    std::string move_lValue = "\tmovl %eax, -" + std::to_string(start_offset) + " (%rbp)\n";
    std::string rValue_code = this->rValue->makeAssembly(st);
    std::string multiplication_code = "\timull -" + std::to_string(start_offset) + " (%rbp) , %eax\n";
    return lValue_code + move_lValue + rValue_code + multiplication_code;
}
//AST::Expr::Add::Add(AST::Expr::Expr* lValue, AST::Expr::Expr* rValue): lValue(lValue), rValue(rValue){}



std::string AST::Expr::Name::makeAssembly(SymbolTable &st) {
    int value = st.getOffset(0, this->name);
    std::string code_move_variable = "\tmovl -" + std::to_string(value) + " (%rbp) " + ", %eax\n";
    return code_move_variable;
}

void AST::Expr::Mult::display() {
    std::cout << "(MULT " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

std::string AST::Expr::Const::makeAssembly(SymbolTable &st) {
    int val = this->value;
    std::string assembler_code = "\tmovl $" + std::to_string(val) + ", %eax\n";
    return assembler_code;
}

std::string AST::Expr::Expr::makeAssembly(SymbolTable &st) {
    return "";
}

std::string AST::Expr::Minus::makeAssembly(SymbolTable &st) {
    std::string value_code = this->value->makeAssembly(st);
    std::string neg_code = "\tNEG %eax\n";
    return value_code + neg_code;
}

std::string AST::Bloc::makeAssembly(SymbolTable &st) {
    std::string assembler_code = "";
    for (auto &it : blocinstr) {
        assembler_code += it->makeAssembly(st);
    }

    return assembler_code;
}

std::string AST::Prog::makeAssembly() {
    std::string prolog = ".globl\tmain\nmain:\n\tpushq %rbp\n\tmovq %rsp, %rbp\n";
    Bloc *child = this->bloc;
    std::string assembler_code = child->makeAssembly(this->table);
    std::string assembler_code_return = this->returnValue->makeAssembly(this->table);
    std::string epilog = assembler_code_return + "\tpopq %rbp\n\tret\n";
    return prolog + assembler_code + epilog;
}


std::string AST::Instr::Def::makeAssembly(SymbolTable &st) {
    std::string valeur_code = this->expr->makeAssembly(st);
    std::string name = this->name;
    int offset = st.getOffset(0, name);
    std::string assembler_code = "\tmovl %eax, -" + std::to_string(offset) + "(%rbp)\n";
    return valeur_code + assembler_code;
    // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, )
    // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset
}

std::string AST::Instr::Affct::makeAssembly(SymbolTable &st) {
    std::string assembleur_expr = this->expr->makeAssembly(st);
    std::string name = this->name;
    int offset = st.getOffset(0, name);
    std::string assembler_code = assembleur_expr + "\tmovl  %eax,  -" + std::to_string(offset) + "(%rbp)\n";
    return assembler_code;
    // offset du rbp gcc -O0 variables c'est une case memoire la case est emmoire est dans lenregistremend dact de la fonction on lattrtape par loffset (distance par rapport au debuet de lenre => rbp, dabord ajouter offset a rbp et apres ecrire dans cette valeur, )
    // for constant creer varaible temp  dans st et pas de duplicat (!xys_offset), stocker a l'offset
}


std::string AST::Instr::If::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Not::makeAssembly(SymbolTable &st) {
    return Expr::makeAssembly(st);
}


std::string AST::Instr::Decl::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Eq::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Geq::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Low::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Great::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Neq::makeAssembly(SymbolTable &st) {
    return std::string();
}

std::string AST::Expr::Leq::makeAssembly(SymbolTable &st) {
    return std::string();
}


void AST::Bloc::pushInstr(Instr::Instr *instr) {
    blocinstr.push_back(instr);
}

//------------------SymbolTable------------------

bool AST::Prog::create_symbol_table() {
    this->table = SymbolTable();
    Bloc *child = this->bloc;
    child->addToTable(table);
    return this->table.getError();
}

void AST::Bloc::addToTable(SymbolTable &st) {
    for (auto &it : blocinstr) {
        it->addToTable(st);
    }
}

void AST::Instr::Def::addToTable(SymbolTable &st) {
    if (st.exists(0, this->name)) {
        st.setErrorTrue();
        std::string error = "error : int " + this->name + " has already been defined\n";
        st.addErrorMsg(error);
    } else {
        st.addSymbol(0, this->name, offset = offset + INT_OFFSET);
    }
    this->expr->exists(st);
    // offset comme atribue de la table de symbole
}

void AST::Instr::Decl::addToTable(SymbolTable &st) {
    for (auto &it : this->names) {
        if (st.exists(0, it)) {
            st.setErrorTrue();
            std::string error = "error : int " + it + " has already been defined\n";
            st.addErrorMsg(error);
        } else {
            st.addSymbol(0, it, offset = offset + INT_OFFSET);
        }
    }
}

void AST::Instr::While::addToTable(SymbolTable &table) {
}

void AST::Instr::If::addToTable(SymbolTable &table) {
}

std::string AST::Prog::getErrorMsg() {
    return this->table.getErrorMsg();
}

//------------------Exists--------------------

void AST::Expr::Sub::exists(SymbolTable &st) {
    this->lValue->exists(st);
    this->rValue->exists(st);
}

void AST::Expr::Const::exists(SymbolTable &st) {}


void AST::Expr::Minus::exists(SymbolTable &st) {
    this->value->exists(st);
}

void AST::Expr::Mult::exists(SymbolTable &st) {
    this->lValue->exists(st);
    this->rValue->exists(st);
}


void AST::Expr::Name::exists(SymbolTable &st) {
    if (!st.exists(0, this->name)) {
        st.setErrorTrue();
        std::string error = "error : variable " + this->name + " has not been declared\n";
        st.addErrorMsg(error);
    }
}

void AST::Expr::Add::exists(SymbolTable &st) {
    this->lValue->exists(st);
    this->rValue->exists(st);
}

void AST::Expr::Geq::exists(SymbolTable &st) {
}

void AST::Expr::Low::exists(SymbolTable &st) {
}

void AST::Expr::Great::exists(SymbolTable &st) {
}

void AST::Expr::Neq::exists(SymbolTable &st) {
}

void AST::Expr::Not::exists(SymbolTable &st) {
}

//-------------DISPLAY-----------------------

void AST::Expr::Name::display() {
    std::cout << "(NAME " << name << ')' << std::flush;
}

void AST::Bloc::display() {
    std::cout << "(BLOC " << std::flush;
    for (auto &it : blocinstr) {
        it->display();
    }
    std::cout << ')' << std::flush;
}


void AST::Expr::Sub::display() {
    std::cout << "(SUB " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Minus::display() {
    std::cout << "(MIN " << std::flush;
    value->display();
    std::cout << ')' << std::flush;
}


void AST::Expr::Const::display() {
    std::cout << "(CONST " << value << ')' << std::flush;
}

void AST::Expr::Add::display() {
    std::cout << "(ADD " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}


void AST::Instr::Decl::display() {
    std::cout << "(DECL " << std::flush;
    for (auto &it : names) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

void AST::Instr::Def::display() {
    std::cout << "(DEF " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}


void AST::Prog::display() {
    std::cout << "(AST " << std::flush;
    bloc->display();
    std::cout << ", " << std::flush;
    returnValue->display();
    std::cout << ")" << std::endl;
}

void AST::Instr::Affct::display() {
    std::cout << "(AFF " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}

void AST::Instr::Affct::addToTable(SymbolTable &table) {
}

void AST::Instr::If::display() {
    std::cout << "(IF " << std::flush;
    expr->display();
    bloc->display();
    std::cout << ')' << std::flush;
}


void AST::Instr::While::display() {
    std::cout << "(WHL " << std::flush;
    expr->display();
    bloc->display();
    std::cout << ')' << std::flush;
}


void AST::Instr::Instr::display() {

}

void AST::Expr::Eq::display() {
    std::cout << "(EQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}


void AST::Expr::Neq::display() {
    std::cout << "(NEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Leq::display() {
    std::cout << "(LEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Low::display() {
    std::cout << "(LOW " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Geq::display() {
    std::cout << "(GEQ " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Great::display() {
    std::cout << "(GRT " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::Not::display() {
    std::cout << "(NOT " << std::flush;
    value->display();
    std::cout << ')' << std::flush;
}


void AST::Expr::Eq::exists(SymbolTable &st) {
}

int AST::Expr::Leq::getValeur() {
    return 0;
}

void AST::Expr::Leq::exists(SymbolTable &st) {

}

int AST::Expr::Geq::getValeur() {
    return 0;
}

int AST::Expr::Low::getValeur() {
    return 0;
}


int AST::Expr::Great::getValeur() {
    return 0;
}

int AST::Expr::Neq::getValeur() {
    return 0;
}

int AST::Expr::Not::getValeur() {
    return 0;
}

int AST::Expr::Sub::getValeur() {
    return 0;
}

int AST::Expr::Minus::getValeur() {
    return 0;
}

int AST::Expr::Mult::getValeur() {
    return 0;
}

int AST::Expr::Name::getValeur() {
    return 0;
}

int AST::Expr::Add::getValeur() {
    return 0;
}

int AST::Expr::Const::getValeur() {
    return this->value;
}


int AST::Expr::Eq::getValeur() {
    return 0;
}