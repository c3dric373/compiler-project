#include "AST.h"
#include "../IR/IR.h"

int INT_OFFSET = 4;
int offset = 0;

// new attribute
// TODO maybe think about putting them as attributes and not global variables
std::vector<CFG *> cfgs;
CFG *currentCFG;

//-------------------generateIR-----------------------

std::vector<CFG *> AST::Prog::generateIR() {
    this->buildIR();
    return cfgs;
}

//-------------------buildIR-----------------------

std::string AST::Prog::buildIR() {
    // Plus tard : déplacer ça dans ASP::Fonct
    Bloc *child = this->bloc;
    CFG *cfg = new CFG(child);
    currentCFG = cfg;
    cfgs.push_back(cfg);

    // Construit les CFGs
    child->buildIR();
    this->returnValue->buildReturnIR();
    return "";
}

std::string AST::Expr::Add::buildIR() {
    std::string tmp_expr1 = this->lValue->buildIR();
    std::string tmp_expr2 = this->rValue->buildIR();
    std::string tmp_dest = currentCFG->create_new_tempvar(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::add, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Sub::buildIR() {
    std::string tmp_expr1 = this->lValue->buildIR();
    std::string tmp_expr2 = this->rValue->buildIR();
    std::string tmp_dest = currentCFG->create_new_tempvar(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::sub, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Mult::buildIR() {
    std::string tmp_expr1 = this->lValue->buildIR();
    std::string tmp_expr2 = this->rValue->buildIR();
    std::string tmp_dest = currentCFG->create_new_tempvar(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::mul, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Name::buildIR() {
    return this->name;
}

std::string AST::Expr::Minus::buildIR() {
    std::string value_expr = this->value->buildIR();
    std::string tmp_dest = currentCFG->create_new_tempvar(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::neg, Type(),
                                        {value_expr, tmp_dest});
    return tmp_dest;
}

std::string AST::Expr::Const::buildIR() {
    std::string value_expr = std::to_string(this->value);
    std::string temp = currentCFG->create_new_tempvar(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::ldconst, Type(),
                                        {temp, value_expr});
    return temp;
}

std::string AST::Bloc::buildIR() {
    for (auto &it : blocinstr) {
        it->buildIR();
    }
    return "";
}

std::string AST::Instr::Def::buildIR() {
    // récupérer le nom de la variable temporaire dans laquelle est stockée l'expr
    std::string name_expr = this->expr->buildIR();
    // Ajout de la variable name à la table des symboles de currentCFG
    currentCFG->add_to_symbol_table(this->name, Type());
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(IRInstr::copy, Type(),
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::Affct::buildIR() {
    std::string name_expr = this->expr->buildIR();
    // Ajout de l'instruction au current_block 
    currentCFG->current_bb->add_IRInstr(IRInstr::copy, Type(),
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::While::buildIR() {
    return std::string();
}

std::string AST::Instr::If::buildIR() {
    // récupérer le nom de la variable temporaire dans laquelle est stockée l'expr
    this->expr->buildIR();
    auto bb_true = new BasicBlock(currentCFG,"if_true");
    currentCFG->current_bb->exit_true = bb_true;
    auto bb_false = new BasicBlock(currentCFG,"if_false");
    currentCFG->current_bb->exit_false = bb_false;
    currentCFG->current_bb = bb_true;
    currentCFG->add_bb(bb_true);
    currentCFG->add_bb(bb_false);
    this->bloc->buildIR();
    currentCFG->current_bb = bb_false;
    return std::string();
}

std::string AST::Expr::Eq::buildIR() {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR();
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR();
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(IRInstr::cmp_eq, Type(),
                                        {name_lValue, name_rValue});
    return "";

}


std::string AST::Expr::Not::buildIR() {
    return Expr::buildIR();
}

std::string AST::Expr::Expr::buildIR() {
    return "";
}

std::string AST::Instr::Decl::buildIR() {
    for (auto &it : this->names) {
        // Ajout de la variable it à la table des symboles de currentCFG
        currentCFG->add_to_symbol_table(it, Type());
    }
    return std::string();
}

std::string AST::Expr::Geq::buildIR() {
    return std::string();
}

std::string AST::Expr::Low::buildIR() {
    return std::string();
}

std::string AST::Expr::Great::buildIR() {
    return std::string();
}

std::string AST::Expr::Neq::buildIR() {
    return std::string();
}


std::string AST::Expr::Leq::buildIR() {
    return std::string();
}


void AST::Bloc::pushInstr(Instr::Instr *instr) {
    blocinstr.push_back(instr);
}


//------------------buildReturnIR------------------

void AST::Expr::Add::buildReturnIR() {
    this->buildIR();
}

void AST::Expr::Sub::buildReturnIR() {
    this->buildIR();
}

void AST::Expr::Mult::buildReturnIR() {
    this->buildIR();
}

void AST::Expr::Const::buildReturnIR() {
    std::string value = std::to_string(this->value);
    currentCFG->current_bb->add_IRInstr(IRInstr::ret, Type(), {"!" + value});
}

void AST::Expr::Name::buildReturnIR() {
    currentCFG->current_bb->add_IRInstr(IRInstr::ret, Type(), {this->name});
}

void AST::Expr::Minus::buildReturnIR() {
    this->buildIR();
}

//------------------SymbolTable------------------
//####################################################################
// NOT NEEDED ANYMORE !!!!!
//####################################################################

/*void AST::Instr::Decl::addToTable(SymbolTable &st) {
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
*/

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
        std::string error =
                "error : variable " + this->name + " has not been declared\n";
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


void AST::Expr::Mult::display() {
    std::cout << "(MULT " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

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

int AST::Expr::Leq::getValue() {
    return 0;
}

void AST::Expr::Leq::exists(SymbolTable &st) {

}

int AST::Expr::Geq::getValue() {
    return 0;
}

int AST::Expr::Low::getValue() {
    return 0;
}


int AST::Expr::Great::getValue() {
    return 0;
}

int AST::Expr::Neq::getValue() {
    return 0;
}

int AST::Expr::Not::getValue() {
    return 0;
}

int AST::Expr::Sub::getValue() {
    return 0;
}

int AST::Expr::Minus::getValue() {
    return 0;
}

int AST::Expr::Mult::getValue() {
    return 0;
}

int AST::Expr::Name::getValue() {
    return 0;
}

int AST::Expr::Add::getValue() {
    return 0;
}

int AST::Expr::Const::getValue() {
    return this->value;
}


int AST::Expr::Eq::getValue() {
    return 0;
}
