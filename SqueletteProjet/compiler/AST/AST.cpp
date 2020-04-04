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

/**---------------------------------------------------------------------------*/
/**------------------------------buildIr--------------------------------------*/
/**---------------------------------------------------------------------------*/

std::string AST::Prog::buildIR() {
    // Plus tard : déplacer ça dans ASP::Fonct
    Bloc *child = this->bloc;
    CFG *cfg = new CFG(child);
    currentCFG = cfg;
    cfgs.push_back(cfg);
    currentCFG->current_bb->bloc = child;
    // Construit les CFGs
    child->buildIR(nullptr);
    this->returnValue->buildReturnIR();
    return "";
}

std::string AST::Expr::ConstChar::buildIR(bool not_flag) {
    return "";
}

std::string AST::Bloc::buildIR(AST::Bloc *previousBloc) {
    this->parent_bloc = previousBloc;
    for (auto &it : blocinstr) {
        // Todo add bloc pointer to build ir as parameter to have the index for variables
        it->buildIR();
    }
    currentCFG->cleanSymbolTable(this);
    return "";
}

/**---------------------------------------------------------------------------*/
/**------------------------------INSTRUCTIONS---------------------------------*/
/**---------------------------------------------------------------------------*/
std::string AST::Instr::If::buildIR() {
    // tester la condition
    AST::Bloc *currentBloc = currentCFG->current_bb->bloc;
    std::string res = this->expr->buildIR(false);

    auto bb_true = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    currentCFG->current_bb->exit_true = bb_true;
    bb_true->bloc = this->bloc;
    auto bb_false = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    bb_false->bloc = currentCFG->current_bb->bloc;
    currentCFG->current_bb->exit_false = bb_false;
    currentCFG->current_bb->add_IRInstr(IRInstr::if_, Type(),
                                        {res});
    currentCFG->current_bb = bb_true;
    currentCFG->add_bb(bb_true);
    this->bloc->buildIR(currentBloc);
    currentCFG->add_bb(bb_false);
    currentCFG->current_bb = bb_false;

    // we can also clean the symbol table as we are finished with the if bloc
  //  currentCFG->cleanSymbolTable(this->bloc);
    return std::string();
}

std::string AST::Instr::While::buildIR() {
    // create new basic bloc where the condition will be tested in order to test
    // the condition again when we will be done with the bloc inside of the
    // loop
    AST::Bloc *ast_block = this->bloc;
    auto start_bBlock = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    start_bBlock->bloc = currentCFG->current_bb->bloc;
    currentCFG->current_bb = start_bBlock;
    currentCFG->add_bb(start_bBlock);
    // create if condition to which we will loop back
    auto if_condition = new AST::Instr::If(this->expr, this->bloc);
    if_condition->buildIR();

    // We need to add the jump back to the if condition therefore we will need
    // to go one block before the last one in our cfg (the if condition will
    // already have added the bloc after the if condition)
    currentCFG->get_bb_before_last()->add_IRInstr(IRInstr::jmp, Type(),
                                                  {start_bBlock->label});

    // We need to reset the variables inside of the while bloc, i.e we need to
    // delete all the variables that were defined inside of it. We do this
    // because it will allow us to create them from scratch if we jump back  to
    // the while block.
   // currentCFG->cleanSymbolTable(ast_block);


    return std::string();
}


std::string AST::Instr::IfElse::buildIR() {
    AST::Bloc *startBloc = currentCFG->current_bb->bloc;

    // tester la condition
    std::string res = this->expr->buildIR(false);
    // create basic bloc after if-else here because it's in the same scope as
    // the current basic bloc
    auto bb_continuation = new BasicBlock(currentCFG,
                                          currentCFG->new_BB_name());
    bb_continuation->bloc = currentCFG->current_bb->bloc;
    auto bb_if = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    currentCFG->current_bb->exit_true = bb_if;
    bb_if->bloc = this->ifBloc;
    auto bb_else = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    currentCFG->current_bb->exit_false = bb_else;
    bb_else->bloc = this->elseBloc;
    currentCFG->current_bb->add_IRInstr(IRInstr::if_, Type(), {res});

    // if bloc
    currentCFG->current_bb = bb_if;
    currentCFG->add_bb(bb_if);
    this->ifBloc->buildIR(startBloc);

    // after the if we need to jump above the else bloc
    bb_if->add_IRInstr(IRInstr::jmp, Type(), {bb_continuation->label});


    // else bloc
    currentCFG->current_bb = bb_else;
    currentCFG->add_bb(bb_else);
    this->elseBloc->buildIR(startBloc);


    // here we don't need a jump because the continuation bb is just after the
    // else bb
    currentCFG->current_bb = bb_continuation;
    currentCFG->add_bb(bb_continuation);

    return std::string();
}

std::string AST::Instr::DefInt::buildIR() {
    // récupérer le nom de la variable temporaire dans laquelle est stockée l'expr
    std::string name_expr = this->expr->buildIR(false);
    // Ajout de la variable name à la table des symboles de currentCFG
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    currentCFG->add_to_symbol_table(current_bloc, this->name, Type());
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(IRInstr::copy, Type(),
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::DefChar::buildIR() {
    return "";
}

std::string AST::Instr::Affct::buildIR() {
    std::string name_expr = this->expr->buildIR(false);
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(IRInstr::copy, Type(),
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::Bloci::buildIR() {
    AST::Bloc *startBloc = currentCFG->current_bb->bloc;
    // We need to create a new bb because there is a new variable scope.
    auto new_bb = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    currentCFG->current_bb = new_bb;
    new_bb->bloc = this->bloc;
    currentCFG->add_bb(new_bb);
    this->bloc->buildIR(startBloc);
    return std::string();
}

/**---------------------------------------------------------------------------*/
/**--------------------------------EXPRESSIONS--------------------------------*/
/**---------------------------------------------------------------------------*/

std::string AST::Expr::And::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::and_, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}


std::string AST::Expr::Xor::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::xor_, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Or::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::or_, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Add::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::add, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Sub::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::sub, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Mult::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::mul, Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Name::buildIR(bool not_flag) {
    return this->name;
}

std::string AST::Expr::Minus::buildIR(bool not_flag) {
    std::string value_expr = this->value->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::neg, Type(),
                                        {value_expr, tmp_dest});
    return tmp_dest;
}

std::string AST::Expr::Const::buildIR(bool not_flag) {
    std::string value_expr = std::to_string(this->value);
    std::string temp = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(IRInstr::ldconst, Type(),
                                        {temp, value_expr});
    return temp;
}


std::string AST::Expr::Eq::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    }
    return tmp_dest;

}

std::string AST::Expr::Neq::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    }
    return tmp_dest;
}


std::string AST::Expr::Geq::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_low, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_great, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    }
    return tmp_dest;
}

std::string AST::Expr::Great::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_low, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_great, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    }
    return tmp_dest;
}

std::string AST::Expr::Low::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_great, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_low, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    }
    return tmp_dest;
}


std::string AST::Expr::Leq::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_great, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(IRInstr::cmp_low, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    }
    return tmp_dest;
}


std::string AST::Expr::Not::buildIR(bool not_flag) {
    this->value->buildIR(true);
    return "";
}

std::string AST::Expr::Expr::buildIR(bool not_flag) {
    return "";
}

std::string AST::Instr::DeclInt::buildIR() {
    for (auto &it : this->names) {
        // Ajout de la variable it à la table des symboles de currentCFG
        AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
        currentCFG->add_to_symbol_table(current_bloc, it, Type());
    }
    return std::string();
}


void AST::Bloc::pushInstr(Instr::Instr *instr) {
    blocinstr.push_back(instr);
}


/**---------------------------------------------------------------------------*/
/**------------------------------buildReturnIR--------------------------------*/
/**---------------------------------------------------------------------------*/
void AST::Expr::Add::buildReturnIR() {
    this->buildIR(true);
}

void AST::Expr::Sub::buildReturnIR() {
    this->buildIR(true);
}

void AST::Expr::Mult::buildReturnIR() {
    this->buildIR(true);
}

void AST::Expr::And::buildReturnIR() {

}

void AST::Expr::Or::buildReturnIR() {

}

void AST::Expr::Xor::buildReturnIR() {

}

void AST::Expr::Const::buildReturnIR() {
    std::string value = std::to_string(this->value);
    currentCFG->current_bb->add_IRInstr(IRInstr::ret, Type(), {"!" + value});
}

void AST::Expr::ConstChar::buildReturnIR() {

}

void AST::Expr::Name::buildReturnIR() {
    auto ntm = currentCFG->current_bb;
    currentCFG->current_bb->add_IRInstr(IRInstr::ret, Type(), {this->name});
}

void AST::Expr::Minus::buildReturnIR() {
    this->buildIR(true);
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

/**---------------------------------------------------------------------------*/
/**------------------------------EXISTS---------------------------------------*/
/**---------------------------------------------------------------------------*/
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

void AST::Expr::And::exists(SymbolTable &st) {
}

void AST::Expr::Or::exists(SymbolTable &st) {
}

void AST::Expr::Xor::exists(SymbolTable &st) {
}

void AST::Expr::ConstChar::exists(SymbolTable &st) {
}


/**---------------------------------------------------------------------------*/
/**------------------------------DISPLAY--------------------------------------*/
/**---------------------------------------------------------------------------*/

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

void AST::Expr::ConstChar::display() {
    std::cout << "(CONSTC " << value << ')' << std::flush;
}

int AST::Expr::ConstChar::getValue() {
    return 0;
}

void AST::Expr::Add::display() {
    std::cout << "(ADD " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}

void AST::Expr::And::display() {
    std::cout << "(AND " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}


int AST::Expr::And::getValue() {
    return 0;
}


void AST::Expr::Or::display() {
    std::cout << "(OR " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}


int AST::Expr::Or::getValue() {
    return 0;
}

void AST::Expr::Xor::display() {
    std::cout << "(XOR " << std::flush;
    lValue->display();
    rValue->display();
    std::cout << ')' << std::flush;
}


int AST::Expr::Xor::getValue() {
    return 0;
}

void AST::Instr::DeclInt::display() {
    std::cout << "(DECI " << std::flush;
    for (auto &it : names) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}


void AST::Instr::DeclChar::display() {
    std::cout << "(DECC " << std::flush;
    for (auto &it : names) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

std::string AST::Instr::DeclChar::buildIR() {
    return std::string();
}


void AST::Instr::DefInt::display() {
    std::cout << "(DEFI " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}


void AST::Instr::DefChar::display() {
    std::cout << "(DEFC " << name << ' ' << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}


void AST::Prog::display() {
    std::cout << "(AST " << std::flush;
    initBloc->display();
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

void AST::Instr::Bloci::display() {
    bloc->display();
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


//Les ajouts à la fin comme promis :D
void AST::Instr::IfElse::display() {
    std::cout << "(IFELSE " << std::flush;
    expr->display();
    ifBloc->display();
    elseBloc->display();
    std::cout << ')' << std::flush;
}


std::string AST::InitBloc::buildIR() {
    return "";
}

void AST::InitBloc::pushInstr(AST::InitInstr::InitInstr *instr) {
    blocinstr.push_back(instr);
}

void AST::InitBloc::display() {
    std::cout << "(IBLOC " << std::flush;
    for (auto &it : blocinstr) {
        it->display();
    }
    std::cout << ')' << std::flush;
}

std::string AST::InitInstr::DefProc::buildIR() {
    return "";
}

void AST::InitInstr::DefProc::display() {
    std::cout << "(DEFP " << procName << ' ' << std::flush;
    for (unsigned i = 0; i < names.size(); ++i) {
        std::cout << types[i] << ' ' << names[i] << ' ' << std::flush;
    }
    bloc->display();
    std::cout << ')' << std::flush;
}

void AST::InitInstr::DefProc::pushArg(std::string type, std::string name) {
    if (type == "int") {
        types.push_back(INT);
    } else if (type == "char") {
        types.push_back(CHAR);
    }
    names.push_back(name);
}

void AST::Instr::Return::display() {
    std::cout << "RETURN" << std::endl;
}

std::string AST::Instr::Return::buildIR() {
    return "";
}


void AST::Instr::CallProc::display() {
    std::cout << "(CALLP " << std::flush;
    for (auto &it : args) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

std::string AST::Instr::CallProc::buildIR() {
    return "";
}





/**---------------------------------------------------------------------------*/
/**------------------------------getVarNames----------------------------------*/
/**---------------------------------------------------------------------------*/

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::CallProc::get_var_names(AST::Bloc *bloc) {
    return  std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>();
}


 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Bloc::get_var_names() {
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> result;
    for (auto &it : blocinstr) {
         std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> vars_in_instr =
                it->get_var_names(this);
        result.insert(result.end(), vars_in_instr.begin(), vars_in_instr.end());

    }
    return result;
}


 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::DeclInt::get_var_names(AST::Bloc *bloc) {
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> res;
    res.emplace_back(bloc, this->names);
    return res;
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::DeclChar::get_var_names(AST::Bloc *bloc) {
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> res;
    res.emplace_back(bloc, this->names);
    return res;
}


 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::DefInt::get_var_names(AST::Bloc *bloc) {
    std::vector<std::string> name;
    name.push_back(this->name);
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> res;
    res.emplace_back(bloc, name);
    return res;
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::DefChar::get_var_names(AST::Bloc *bloc) {
    std::vector<std::string> name;
    name.push_back(this->name);
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> res;
    res.emplace_back(bloc, name);
    return res;
}


 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::While::get_var_names(AST::Bloc *bloc) {
    return this->bloc->get_var_names();
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::If::get_var_names(AST::Bloc *bloc) {
    return this->bloc->get_var_names();
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::Bloci::get_var_names(AST::Bloc *bloc) {
    return this->bloc->get_var_names();
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::IfElse::get_var_names(AST::Bloc *bloc) {
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> if_res =
            this->ifBloc->get_var_names();
     std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>> else_res =
            this->elseBloc->get_var_names();
    if_res.insert(if_res.end(), else_res.begin(), else_res.end());
    return if_res;


}


// --- No action necessary -----------------------------------------------------
 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::Affct::get_var_names(AST::Bloc *bloc) {
    return  std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>();
}

 std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>
AST::Instr::Return::get_var_names(AST::Bloc *bloc) {
    return  std::vector<std::tuple<AST::Bloc*, std::vector<std::string>>>();
}
