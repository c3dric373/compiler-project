#include "AST.h"
#include "../IR/IR.h"


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
    // Build cfgs for defined functions
    AST::InitBloc *pInitBloc = this->initBloc;
    initBloc->buildIR();

    // Build cfg for main function
    Bloc *child = this->bloc;
    CFG *cfg = new CFG(child, "main");
    currentCFG = cfg;
    cfgs.push_back(cfg);
    currentCFG->current_bb->bloc = child;
    // Construit les CFGs
    child->buildIR(nullptr);

    this->returnValue->buildReturnIR();
    return "";
}


std::string AST::Bloc::buildIR(AST::Bloc *previousBloc) {
    this->parent_bloc = previousBloc;
    for (auto &it : blocinstr) {
        // Todo add bloc pointer to build ir as parameter to have the index for variables
        it->buildIR();
    }
    return "";
}

std::string AST::InitBloc::buildIR() {
    for (auto &function : initFuns) {
        AST::Bloc *child = function->get_bloc();
        std::string();
        CFG *cfg = new CFG(child, function->get_name());
        cfgs.push_back(cfg);
        currentCFG = cfg;
        cfg->add_to_symbol_table(0,0, nullptr,"!%eax",Type());
        currentCFG->current_bb->bloc = child;
        function->buildIR();
    }
    return std::string();
}





//-----------------------------INSTRUCTIONS-------------------------------------


/**---------------------------FUNCTIONS---------------------------------------*/

std::string AST::InitInstr::DefProc::buildIR() {

    vector<TYPES>::iterator ptr = this->types.begin();
    Type t;
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    int i = 16;
    for (auto &name : this->names) {
        switch (*ptr) {
            case INT:
                t = Type(Type::type_int);
                break;
            case CHAR:
                t = Type(Type::type_char);
                break;
                // Ajout de la variable name à la table des symboles de currentCFG

        }
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        name, t);
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::get_arg, Type(),
                                            {std::to_string(i), name});
        i += 8;
        ptr++;
    }

    this->bloc->buildIR(nullptr);
    return "";
}


std::string AST::Expr::CallFun::buildIR(bool not_flag) {
    int offset = currentCFG->getNextFreeSymbolIndex();
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    int i = 0;
    for (auto it = this->args.begin(); it != this->args.end(); it++) {
        std::string arg = *it;
        Type t = currentCFG->get_var_type(current_bloc, arg);
        offset -= 4;
        std::string rbp = to_string(offset) + "(%rbp)";
        // Ajout de l'instruction au current_block
        currentCFG->current_bb->add_IRInstr(0, 0, IRInstr::add_fct_param, t,
                                            {arg, std::to_string(i)});
        i++;
    }
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());

    currentCFG->current_bb->add_IRInstr(0, 0, IRInstr::call_fct, Type(),
                                        {this->funName,tmp_dest});


    return tmp_dest;
}


std::string AST::InitInstr::DefFun::buildIR() {
    vector<TYPES>::iterator ptr = this->types.begin();
    Type type_current;
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    int i = 0;

    for (auto &name : this->names) {
        switch (*ptr) {
            case INT:
                type_current = Type(Type::type_int);
                break;
            case CHAR:
                type_current = Type(Type::type_char);
                break;
        }

        // Ajout de la variable name à la table des symboles de currentCFG
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        name, type_current);
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::get_arg, type_current,
                                            {std::to_string(i), name});
        i++;
        ptr++;
    }
    this->bloc->buildIR(nullptr);
    return "";
}

std::string AST::InitInstr::DeclFun::buildIR() {
    return "";
}


std::string AST::InitInstr::DeclProc::buildIR() {
    return "";
}

std::string AST::Instr::Return::buildIR() {
    currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                        IRInstr::return_, Type(), {});
    return "";
}


std::string AST::Instr::CallProc::buildIR() {
    int offset = currentCFG->getNextFreeSymbolIndex();
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    for (std::string &name : this->args) {
        const std::string &name_expr = name;
        Type t = currentCFG->get_var_type(current_bloc, name_expr);
        offset -= t.get_offset();
        std::string rbp = to_string(offset) + "(%rbp)";
        // Ajout de l'instruction au current_block
        currentCFG->current_bb->add_IRInstr(0, 0, IRInstr::add_fct_param, t,
                                            {name_expr, rbp});
    }
    currentCFG->current_bb->add_IRInstr(0, 0, IRInstr::call_fct, Type(),
                                        {this->procName});
    return "";
}

std::string AST::Instr::ReturnExpr::buildIR() {
    std::string res = this->expr->buildIR(false);
    currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                        IRInstr::return_expr, Type(), {res});

    return "";
}


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
    currentCFG->current_bb->add_IRInstr(-1, -1, IRInstr::if_, Type(),
                                        {res});
    currentCFG->current_bb = bb_true;
    currentCFG->add_bb(bb_true);
    this->bloc->buildIR(currentBloc);
    currentCFG->add_bb(bb_false);
    currentCFG->current_bb = bb_false;
    return std::string();
}

std::string AST::Instr::While::buildIR() {
    // create new basic bloc where the condition will be tested in order to test
    // the condition again when we will have be done with the bloc inside of the
    // loop
    auto start_block = new BasicBlock(currentCFG, currentCFG->new_BB_name());
    start_block->bloc = currentCFG->current_bb->bloc;
    currentCFG->current_bb = start_block;
    currentCFG->add_bb(start_block);
    // create if condition to which we will loop back
    auto if_condition = new AST::Instr::If(this->expr, this->bloc);
    if_condition->buildIR();

    // We need to add the jump back to the if condition therefore we will need
    // to go one block before the last one in our cfg (the if condition will
    // already have added the bloc after the if condition)
    currentCFG->get_bb_before_last()->add_IRInstr(-1, -1, IRInstr::jmp, Type(),
                                                  {start_block->label});

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
    currentCFG->current_bb->add_IRInstr(-1, -1, IRInstr::if_, Type(), {res});

    // if bloc
    currentCFG->current_bb = bb_if;
    currentCFG->add_bb(bb_if);
    this->ifBloc->buildIR(startBloc);

    // after the if we need to jump above the else bloc
    bb_if->add_IRInstr(-1, -1, IRInstr::jmp, Type(), {bb_continuation->label});


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
    currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                    this->name, Type::type_int);
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::copy,
                                        Type::type_int,
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::DefChar::buildIR() {
    // récupérer le nom de la variable temporaire dans laquelle est stockée l'expr
    std::string name_expr = this->expr->buildIR(false);
    // Ajout de la variable name à la table des symboles de currentCFG
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                    this->name, Type::type_char);
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::copy,
                                        Type::type_char,
            // Ajout de l'instruction au current_block
                                        {name_expr, this->name});
    return "";
}

std::string AST::Instr::Affct::buildIR() {
    std::string name_expr = this->expr->buildIR(false);
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc, this->name);
    // Ajout de l'instruction au current_block
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::copy,
                                        t,
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

//-----------------------------EXPRESSIONS--------------------------------------


std::string AST::Expr::And::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::and_,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}


std::string AST::Expr::Xor::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::xor_,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Or::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::or_,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Add::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::add,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Sub::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::sub,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Mult::buildIR(bool not_flag) {
    std::string tmp_expr1 = this->lValue->buildIR(not_flag);
    std::string tmp_expr2 = this->rValue->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::mul,
                                        Type(),
                                        {tmp_dest, tmp_expr1, tmp_expr2});
    return tmp_dest;
}

std::string AST::Expr::Name::buildIR(bool not_flag) {
    return this->name;
}

std::string AST::Expr::Minus::buildIR(bool not_flag) {
    std::string value_expr = this->value->buildIR(not_flag);
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::neg,
                                        Type(),
                                        {value_expr, tmp_dest});
    return tmp_dest;
}

std::string AST::Expr::Const::buildIR(bool not_flag) {
    std::string value_expr = std::to_string(this->value);
    std::string temp = currentCFG->create_new_temp_var(Type::type_int);
    currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                        IRInstr::ldconst, Type::type_int,
                                        {temp, value_expr});
    return temp;
}

std::string AST::Expr::ConstChar::buildIR(bool not_flag) {
    std::string value_expr = std::to_string((int) this->value);
    std::string temp = currentCFG->create_new_temp_var(Type::type_char);
    currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                        IRInstr::ldconst, Type::type_char,
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
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_eq, Type(),
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
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_eq, Type(),
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_eq, Type(),
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

    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc, name_lValue);

    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_low, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_great, t,
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

    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc, name_lValue);

    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_low, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_great, t,
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

    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc, name_lValue);

    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_great, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_low, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    }
    return tmp_dest;
}


std::string AST::Expr::Leq::buildIR(bool not_flag) {
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_lValue = this->lValue->buildIR(not_flag);
    // récupérer le nom de la variable temporaire dans laquelle est stockée lValue
    std::string name_rValue = this->rValue->buildIR(not_flag);
    // create tmp var to store result of expression
    std::string tmp_dest = currentCFG->create_new_temp_var(Type());

    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc, name_lValue);

    // Put instruction into current block
    if (not_flag) {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_great, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "neq"});
    } else {
        currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                            IRInstr::cmp_low, t,
                                            {tmp_dest, name_lValue, name_rValue,
                                             "eq"});
    }

    return tmp_dest;
}


std::string AST::Expr::Not::buildIR(bool not_flag) {
    return this->value->buildIR(true);
}

std::string AST::Expr::Expr::buildIR(bool not_flag) {
    return "";
}

std::string AST::Instr::DeclInt::buildIR() {
    for (auto &it : this->names) {
        // Ajout de la variable it à la table des symboles de currentCFG
        AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        it, Type::type_int);
    }
    return std::string();
}

std::string AST::Instr::DeclChar::buildIR() {
    for (auto &it : this->names) {
        // Ajout de la variable it à la table des symboles de currentCFG
        AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        it, Type::type_char);
    }
    return std::string();
}

std::string AST::Expr::TabAccess::buildIR(bool not_flag) {
    std::string _name = to_string(this->index->getValue()) + this->name;
    return _name;
}

void AST::Bloc::pushInstr(Instr::Instr *instr) {
    blocinstr.push_back(instr);
}


//------------------buildReturnIR------------------

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
    this->buildIR(true);
}

void AST::Expr::Or::buildReturnIR() {
    this->buildIR(true);
}

void AST::Expr::Xor::buildReturnIR() {
    this->buildIR(true);
}

void AST::Expr::Const::buildReturnIR() {
    std::string value = std::to_string(this->value);
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::ret,
                                        Type(), {"!" + value});
}

void AST::Expr::ConstChar::buildReturnIR() {
    std::string value = std::to_string(this->value);
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::ret,
                                        Type(), {"!" + value});
}

void AST::Expr::Name::buildReturnIR() {
    auto ntm = currentCFG->current_bb;
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::ret,
                                        Type(), {this->name});
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

bool AST::Prog::getError() {
    bool error = false;
    for (auto &it : cfgs) {
        bool e = it->getErreur().getError();
        error = error || e;
    }
    return error;
}

std::string AST::Prog::getErrorMsg() {
    std::string errorMessage;
    for (auto &it : cfgs) {
        errorMessage += it->getErreur().getMessage();
    }
    return errorMessage;
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

int AST::Expr::Leq::getValue() {
    return 0;
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


void AST::InitBloc::pushInstr(AST::InitInstr::InitInstr *instr) {
    initFuns.push_back(instr);
}

void AST::InitBloc::display() {
    std::cout << "(IBLOC " << std::flush;
    for (auto &it : initFuns) {
        it->display();
    }
    std::cout << ')' << std::flush;
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

void AST::Instr::CallProc::display() {
    std::cout << "(CALLP " << std::flush;
    for (auto &it : args) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}


void AST::Instr::ReturnExpr::display() {
    std::cout << "(RET " << std::flush;
    expr->display();
    std::cout << ')' << std::flush;
}


bool AST::Instr::DeclInt::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::DeclChar::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::DefInt::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::DefChar::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::Affct::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::If::wrongReturnType(bool returnType) {
    return bloc->wrongReturnType(returnType);
}

bool AST::Instr::IfElse::wrongReturnType(bool returnType) {
    bool a = ifBloc->wrongReturnType(returnType);
    bool b = elseBloc->wrongReturnType(returnType);
    return a || b;
}

bool AST::Instr::While::wrongReturnType(bool returnType) {
    return bloc->wrongReturnType(returnType);
}

bool AST::Instr::Bloci::wrongReturnType(bool returnType) {
    return bloc->wrongReturnType(returnType);
}

bool AST::Instr::CallProc::wrongReturnType(bool returnType) {
    return false;
}

bool AST::Instr::Return::wrongReturnType(bool returnType) {
    if (returnType) {
        std::string errorMessage =
                "line" + std::to_string(line) + ':' + std::to_string(column)
                + " expecting an expression to return";
        std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
    }
    return returnType;
}

bool AST::Instr::ReturnExpr::wrongReturnType(bool returnType) {
    if (!returnType) {
        std::string errorMessage =
                "line" + std::to_string(line) + ':' + std::to_string(column)
                + " expecting a void return";
        std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
    }
    return !returnType;
}

bool AST::Bloc::wrongReturnType(bool returnType) {
    bool res = false;
    for (auto &it : blocinstr) {
        if (it->wrongReturnType(returnType)) {
            res = true;
        }
    }
    return res;
}

// here comes the fun todododo (j'espère que vous avez la ref)
AST::InitInstr::DefFun::DefFun(std::string returnType_, std::string procName,
                               AST::Bloc *bloc, unsigned line, unsigned column)
        :
        funName(procName), bloc(bloc), line(line), column(column) {
    if (returnType_ == "int") {
        returnType = INT;
    } else if (returnType_ == "char") {
        returnType = CHAR;
    }
}

void AST::InitInstr::DefFun::pushArg(std::string type, std::string name) {
    if (type == "int") {
        types.push_back(INT);
    } else if (type == "char") {
        types.push_back(CHAR);
    }
    names.push_back(name);
}


void AST::InitInstr::DefFun::display() {
    std::cout << "(DEFF " << returnType << ' ' << funName << ' ' << std::flush;
    for (unsigned i = 0; i < names.size(); ++i) {
        std::cout << types[i] << ' ' << names[i] << ' ' << std::flush;
    }
    bloc->display();
    std::cout << ')' << std::flush;
}


int AST::Expr::CallFun::getValue() {
    return 0;
}


void AST::Expr::CallFun::buildReturnIR() {
    std::string res = this->buildIR(false);
    currentCFG->current_bb->add_IRInstr(this->line, this->column,
                                        IRInstr::return_expr, Type(), {res});
}


void AST::InitInstr::DeclProc::pushArg(std::string type, std::string name) {
    if (type == "int") {
        types.push_back(INT);
    } else if (type == "char") {
        types.push_back(CHAR);
    }
    names.push_back(name);
}

void AST::InitInstr::DeclProc::display() {
    std::cout << "(DECLP " << procName << ' ' << std::flush;
    for (unsigned i = 0; i < names.size(); ++i) {
        std::cout << types[i] << ' ' << names[i] << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

AST::InitInstr::DeclFun::DeclFun(std::string returnType_, std::string procName,
                                 unsigned line, unsigned column) :
        funName(procName), line(line), column(column) {
    if (returnType_ == "int") {
        returnType = INT;
    } else if (returnType_ == "char") {
        returnType = CHAR;
    }
}

void AST::InitInstr::DeclFun::pushArg(std::string type, std::string name) {
    if (type == "int") {
        types.push_back(INT);
    } else if (type == "char") {
        types.push_back(CHAR);
    }
    names.push_back(name);
}

void AST::InitInstr::DeclFun::display() {
    std::cout << "(DECLF " << returnType << ' ' << funName << ' ' << std::flush;
    for (unsigned i = 0; i < names.size(); ++i) {
        std::cout << types[i] << ' ' << names[i] << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

void AST::Expr::CallFun::display() {
    std::cout << "(CALLF " << std::flush;
    for (auto &it : args) {
        std::cout << it << ' ' << std::flush;
    }
    std::cout << ')' << std::flush;
}

std::string AST::InitInstr::DefFun::get_name() {
    return this->funName;
}


std::string AST::InitInstr::DefProc::get_name() {
    return this->procName;
}


std::string AST::InitInstr::DeclProc::get_name() {
    return this->procName;
}

std::string AST::InitInstr::DeclFun::get_name() {
    return this->funName;
}

AST::Bloc *AST::InitInstr::DefFun::get_bloc() {
    return this->bloc;
}

AST::Bloc *AST::InitInstr::DeclFun::get_bloc() {
    return nullptr;
}

AST::Bloc *AST::InitInstr::DefProc::get_bloc() {
    return this->bloc;
}

AST::Bloc *AST::InitInstr::DeclProc::get_bloc() {
    return nullptr;
}

//Ajout des tableaux
std::string AST::Instr::DeclIntTab::buildIR() {
    int _size = this->size->getValue();
    for (int i = 0; i < _size; i++) {
        // Ajout de la variable it à la table des symboles de currentCFG
        AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        to_string(i) + this->name,
                                        Type::type_int);

    }
    return std::string();
}

void AST::Instr::DeclIntTab::display() {
    std::cout << "(DECLIT " << name << ' ' << std::flush;
    size->display();
    std::cout << ')' << std::flush;
}

bool AST::Instr::DeclIntTab::wrongReturnType(bool returnType) {
    return false;
}

std::string AST::Instr::DeclCharTab::buildIR() {
    int _size = this->size->getValue();
    for (int i = 0; i < _size; i++) {
        // Ajout de la variable it à la table des symboles de currentCFG
        AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
        currentCFG->add_to_symbol_table(this->line, this->column, current_bloc,
                                        to_string(i) + this->name,
                                        Type::type_char);

    }
    return std::string();
}

void AST::Instr::DeclCharTab::display() {
    std::cout << "(DECLCT " << name << ' ' << std::flush;
    size->display();
    std::cout << ')' << std::flush;
}

bool AST::Instr::DeclCharTab::wrongReturnType(bool returnType) {
    return false;
}

std::string AST::Instr::AffctTab::buildIR() {
    std::string name_expr = this->expr->buildIR(false);
    // Ajout de l'instruction au current_block
    AST::Bloc *current_bloc = currentCFG->current_bb->bloc;
    Type t = currentCFG->get_var_type(current_bloc,
                                      to_string(this->index->getValue()) +
                                      this->name);
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::copy,
                                        t,
                                        {name_expr,
                                         to_string(this->index->getValue()) +
                                         this->name});
    return "";
}

void AST::Instr::AffctTab::display() {
    std::cout << "(AFFT " << name << ' ' << std::flush;
    index->display();
    expr->display();
    std::cout << ')' << std::flush;
}

bool AST::Instr::AffctTab::wrongReturnType(bool returnType) {
    return false;
}


int AST::Expr::TabAccess::getValue() {
    return 0;
}


void AST::Expr::TabAccess::buildReturnIR() {
    currentCFG->current_bb->add_IRInstr(this->line, this->column, IRInstr::ret,
                                        Type(),
                                        {to_string(this->index->getValue()) +
                                         this->name});
}

void AST::Expr::TabAccess::display() {
    std::cout << "(TA " << name << ' ' << std::flush;
    index->display();
    std::cout << ')' << std::flush;
}


//Optimisations

bool AST::Expr::Add::isConst(){
    return false;
}
bool AST::Expr::Sub::isConst(){
    return false;
}
bool AST::Expr::Mult::isConst(){
    return false;
}
bool AST::Expr::Minus::isConst(){
    return false;
}
bool AST::Expr::And::isConst(){
    return false;
}
bool AST::Expr::Or::isConst(){
    return false;
}
bool AST::Expr::Xor::isConst(){
    return false;
}
bool AST::Expr::Const::isConst(){
    return true;
}
bool AST::Expr::ConstChar::isConst(){
    return false;
}
bool AST::Expr::Name::isConst(){
    return false;
}
bool AST::Expr::TabAccess::isConst(){
    return false;
}
bool AST::Expr::CallFun::isConst(){
    return false;
}
bool AST::Expr::Eq::isConst(){
    return false;
}
bool AST::Expr::Neq::isConst(){
    return false;
}
bool AST::Expr::Leq::isConst(){
    return false;
}
bool AST::Expr::Geq::isConst(){
    return false;
}
bool AST::Expr::Low::isConst(){
    return false;
}
bool AST::Expr::Great::isConst(){
    return false;
}
bool AST::Expr::Not::isConst(){
    return false;
}
