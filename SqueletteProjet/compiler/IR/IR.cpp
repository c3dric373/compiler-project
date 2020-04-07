#include <sstream>
#include "IR.h"

// Généré à partir de IR.h

/*
	Pour utiliser l'IR, il faut ajouter 2 attributs à l'AST:
		- Un attribut CFG* sur le CFG actuellement utilisé
		- Un attribut vector<CFG*> qui stockerait les CFGs

EN GROS:
	Les fonctions de l'IR sont appelées dans l'AST, et l'IR traduit les instructions en langage assembleur
Lors du parcours de l'AST :
	-Un nouveau CFG est créé à chaque nouvelle fonction
	-Pour tout autre élément, la visite de l'élément ajoutera juste une instruction à l'attribut current_bb du CFG grâce à la méthode add_IRInstr OU ajoutera la variable à la table des symboles en faisant un appel à la fonction add_to_symbol_table du current CFG

Il est important de préciser que les variables temporaires seront crées dans l'AST avant d'être passées en paramètre à la méthode de l'IR correspondante.
C'est la méthode create_new_temp_var de l'IR qui s'occupera d'insérer la variable temporaire dans la table des symboles.

*/


IRInstr::IRInstr(BasicBlock *bb_, Operation op_, Type t_,
                 vector<string> params_) : bb(bb_), op(op_), t(t_),
                                           params(params_) {}

// TODO
void IRInstr::gen_asm(ostream &o) {
    /* Exemple de ce qu'il faut mettre ici, la + longue méthode*/
    std::string type = t.get_suffix();
    switch (op) {
        case Operation::ldconst : {
            AST::Bloc *bloc = bb->bloc;
            // for const : params = [ name | value ]
            std::string regString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            o << "\tmov" + type + " $" << params[1] << ", " << regString
              << endl;
            break;
        }
        case Operation::add_fct_param: {
            AST::Bloc *bloc = bb->bloc;
            // copy params [0] into params [1]
            std::string reg_tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg_variable =  params[1];
            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << reg_tmp_var << ", %eax" << endl;
                    o << "\tmovl %eax , " << reg_variable << " # fct param " << params[1]
                      << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovl " << reg_tmp_var << ", %eax" << endl;
                    o << "\tmovb %al , " << reg_variable << " # fct param " << params[1]
                      << endl;
                    break;
                }
            }
            break;
        }
        case Operation::call_fct: {
            std::string fct_name =  params[0];
            o << "\tcall " << fct_name << endl;
            break;
        }
        case Operation::copy: {
            AST::Bloc *bloc = bb->bloc;
            // copy params [0] into params [1]
            std::string reg_tmp_var;
            if(params[0]=="%eax"){
                 reg_tmp_var = params[0];
            }else{
                reg_tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            }
            std::string reg_variable = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << reg_tmp_var << ", %eax" << endl;
                    o << "\tmovl %eax , " << reg_variable << " # " << params[1]
                      << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovl " << reg_tmp_var << ", %eax" << endl;
                    o << "\tmovb %al , " << reg_variable << " # " << params[1]
                      << endl;
                    break;
                }
            }
            break;
        }
        case Operation::sub: {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tsubl " << reg2String << ", %eax" << "# " << params[1]
              << " - " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::mul: {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\timull " << reg2String << ", %eax" << " # " << params[1]
              << " * " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::add : {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\taddl " << reg2String << ", %eax" << " # " << params[1]
              << " + " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::and_: {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tand " << reg2String << ", %eax" << " # " << params[1]
              << " and " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::xor_: {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\txor " << reg2String << ", %eax" << " # " << params[1]
              << " xor " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::or_: {
            AST::Bloc *bloc = bb->bloc;
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tor " << reg2String << ", %eax" << " # " << params[1]
              << " or" << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::rmem: {
            break;
        }
        case Operation::wmem: {
            break;
        }
        case Operation::call: {
            break;
        }
        case Operation::if_: {
            AST::Bloc *bloc = bb->bloc;
            std::string expr = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            o << "\tcmpl $1, " << expr << endl;
            o << "\tje " << bb->exit_true->label << endl;
            o << "\tjmp " << bb->exit_false->label << endl;
            break;
        }
        case Operation::cmp_eq: {
            AST::Bloc *bloc = bb->bloc;
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            o << "\tmovl " << lValue << ", %eax" << endl;
            o << "\tcmpl  %eax, " << rValue << endl;
            if (equal) {
                o << "\tsete %dl" << " # " << params[1] << "==" << params[2]
                  << endl;
            } else {
                o << "\tsetne %dl" << " # " << params[1] << "!=" << params[2]
                  << endl;
            }
            o << "\tmovzbl %dl, %eax" << endl;
            o << "\tmovl %eax, " << dest_location << endl;
            break;
        }

        case Operation::cmp_low: {
            AST::Bloc *bloc = bb->bloc;
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << rValue << ", %eax" << endl;
                    o << "\tcmp  %eax, " << lValue << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovzbl " << rValue << ", %eax" << endl;
                    o << "\tcmpb  %al, " << lValue << endl;
                    break;
                }
            }

            if (equal) {
                o << "\tsetbe %dl" << " # " << params[1] << "<=" << params[2]
                  << endl;
            } else {
                o << "\tsetb %dl" << " # " << params[1] << "<" << params[2]
                  << endl;
            }
            o << "\tmovzbl %dl, %eax" << endl;
            o << "\tmovl %eax, " << dest_location << endl;
            break;

        }
        case Operation::cmp_great: {
            AST::Bloc *bloc = bb->bloc;
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << rValue << ", %eax" << endl;
                    o << "\tcmp  %eax, " << lValue << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovzbl " << rValue << ", %eax" << endl;
                    o << "\tcmpb  %al, " << lValue << endl;
                    break;
                }
            }

            if (equal) {
                o << "\tsetae %dl" << " # " << params[1] << ">=" << params[2]
                  << endl;
            } else {
                o << "\tseta %dl" << " # " << params[1] << ">" << params[2]
                  << endl;
            }
            o << "\tmovzbl %dl, %eax" << endl;
            o << "\tmovl %eax, " << dest_location << endl;
            break;

        }
        case Operation::ret: {
            AST::Bloc *bloc = bb->bloc;
            // Récupère le paramètre
            std::string param = params[0];
            //Si le paramètre ne contient pas de ! c'est que c'est une variable
            if (param.at(0) != '!') {
                std::string regString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
                o << "\tmovl " << regString << ", %eax" << endl;
            } else {
                // Le paramètre est une constante, on enlève le ! et on mets la constante dans %eax
                std::string value = param.erase(0, 1);
                o << "\tmovl $" << value << ", %eax" << endl;
            }
            break;
        }
        case Operation::neg: {
            AST::Bloc *bloc = bb->bloc;
            std::string tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string dest_var = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            o << "\tmovl " << tmp_var << ", %eax" << endl;
            o << "\tNEG %eax" << endl;
            o << "\tmovl %eax, " << dest_var << endl;
            break;
        }
        case Operation::jmp: {
            std::string basic_block = params[0];
            o << "\t jmp " << basic_block << endl;
            break;
        }
        case Operation::call_proc: {

            break;
        }
        case Operation::return_: {
            o << "\tnop" << endl;
            break;
        }
        case Operation::return_expr: {
            AST::Bloc *bloc = bb->bloc;
            std::string return_address =  bb->cfg->IR_reg_to_asm(bloc, params[0]);;
            o << "\tmovl " + return_address + ", %eax" << endl;
            break;
        }
    }
}

BasicBlock::BasicBlock(CFG *cfg, string entry_label) : cfg(cfg),
                                                       label(entry_label) {}

void BasicBlock::gen_asm(ostream &o) {
    std::string label = this->label;
    if (!label.empty()) {
        o << this->label << ": " << endl;
    }
    for (auto instr : instrs) {
        instr->gen_asm(o);
    }
}

void
BasicBlock::add_IRInstr(int line, int column, IRInstr::Operation op, Type t,
                        vector<string> params) {
    // Analyse statique :
    // Find out if the variable placed in params has already been declared
    // if offset == 1, it hasn't been declared
    for (std::string param : params) {
        int offset = 0;
        switch (op) {
            case IRInstr::copy :
            case IRInstr::and_ :
            case IRInstr::xor_ :
            case IRInstr::or_ :
            case IRInstr::add :
            case IRInstr::sub :
            case IRInstr::mul :
            case IRInstr::neg :
                offset = this->cfg->get_var_index(this->bloc, param);
                break;
            case IRInstr::ret :
                // if the param doesn't contain a !, this is not a constant
                if (param.at(0) != '!') {
                    offset = this->cfg->get_var_index(this->bloc, param);
                }
                break;
            case IRInstr::cmp_eq :
            case IRInstr::cmp_low :
            case IRInstr::cmp_great :
                if (param.compare("eq") != 0 && param.compare("neq") != 0) {
                    offset = this->cfg->get_var_index(this->bloc, param);
                }
                break;
                // Do nothing
            default:
                break;
        }
        // if param has not been declared, launch an error
        if (offset == 1) {
            std::string erreur =
                    "error line " + std::to_string(line) + " column " +
                    std::to_string(column) +
                    " : cannot find the offset, the variable " + param +
                    " has not been declared \n";
            this->cfg->addErreur(erreur);
        }
    }
    instrs.push_back(new IRInstr(this, op, t, params));
}

CFG::CFG(AST::Bloc *ast_, std::string name) : nextFreeSymbolIndex(0),
                                              nextBBnumber(0), ast(ast_) {
    auto firstBB = new BasicBlock(this, "");
    this->add_bb(firstBB);
    this->name = name;

    // Create just one block
    // In the future, we must create one more
    firstBB->exit_false = nullptr;
    firstBB->exit_true = nullptr;

    current_bb = firstBB;
}

void CFG::add_bb(BasicBlock *bb) {
    basic_blocs.push_back(bb);
}

void CFG::gen_asm(ostream &o) {
    gen_asm_prologue(o);
    for (auto bb : basic_blocs) {
        bb->gen_asm(o);
    }
    gen_asm_epilogue(o);
}

// take a variable and transform it to "-offset(%rbp)"
std::string CFG::IR_reg_to_asm(AST::Bloc *bloc, string reg) {
    int offset = this->get_var_index(bloc, reg);
    std::string regString = std::to_string(offset) + "(%rbp)";
    return regString;
}

void CFG::set_name(std::string name) {
    this->name = name;
}

int CFG::getNextFreeSymbolIndex() { return nextFreeSymbolIndex; }


std::string CFG::get_name() {
    return this->name;
}

void CFG::gen_asm_prologue(ostream &o) {
    std::string label = this->name;
    if (label == "main") {
        o << ".globl\tmain" << endl;
    }
    o << this->name << ":" << endl;
    o << "\tpushq %rbp" << endl;
    o << "\tmovq %rsp, %rbp" << endl;
    o << "\tsubq $" << this->nextFreeSymbolIndex*(-1) << ", %rsp" << endl;
}

void CFG::gen_asm_epilogue(ostream &o) {
    o << "\taddq $" << this->nextFreeSymbolIndex*(-1) << ", %rsp" << endl;
    o << "\tpopq %rbp" << endl;
    o << "\tret" << endl;
}


static std::string get_var_name(AST::Bloc *bloc, std::string name) {
    // Convert the bloc pointer to a string
    const void *parent_bloc_address = static_cast<const void *>(bloc);
    std::stringstream ss1;
    ss1 << parent_bloc_address;
    std::string address_new_bloc = ss1.str();
    std::string new_name = address_new_bloc + name;
    return new_name;
}


void
CFG::add_to_symbol_table(int line, int column, AST::Bloc *bloc, string name,
                         Type t) {
    std::string type;
    switch (t.type_) {
        case Type::type_int: {
            nextFreeSymbolIndex -= t.get_offset();
            type = "int";
            break;
        }
        case Type::type_char: {
            nextFreeSymbolIndex -= t.get_offset();
            type = "char";
            break;
        }
    }

    // Redefine the name of the variable, in order to identify it via it's bloc
    // pointer
    std::string new_name = get_var_name(bloc, name);


    if (SymbolIndex.find(new_name) == SymbolIndex.end()) {
        SymbolType[new_name] = t;
        SymbolIndex[new_name] = nextFreeSymbolIndex;
    } else {
        std::string erreur =
                "error line " + std::to_string(line) + " column " +
                std::to_string(column) + " : " + type + " " + name +
                " has already been defined\n";
        error.addErrorMessage(erreur);
    }
}

std::string CFG::create_new_temp_var(Type t) {

    nextFreeSymbolIndex -= t.get_offset();

    // nextFreeSymbolIndex is negative, so we put -nextFreeSymbolIndex in the tmp name
    std::string name_var_temp = "!tmp" + std::to_string(-nextFreeSymbolIndex);

    // Add new tmp var to the symbole table
    SymbolType[name_var_temp] = t;
    SymbolIndex[name_var_temp] = nextFreeSymbolIndex;
    return name_var_temp;
}

int CFG::find_index(string name) {
    if (SymbolIndex.find(name) == SymbolIndex.end()) {
        return 100;
    } else {
        return SymbolIndex.at(name);
    }
}


int CFG::get_var_index(AST::Bloc *bloc, string name) {
    // If it's a tmp variable created by ourselves we do not need to add the
    // bloc pointer to identify it.
    if (name.rfind('!', 0) == 0) {
        return find_index(name);
    }

    // Redefine the name of the variable, in order to identify it via it's bloc
    // pointer
    std::string new_name = get_var_name(bloc, name);
    if (bloc->parent_bloc == nullptr) {
        return find_index(new_name);
    }
    while (SymbolIndex.find(new_name) == SymbolIndex.end()) {
        AST::Bloc *parent_bloc = bloc->parent_bloc;
        // We need to do the last check inside of the loop else we will get
        // a nullptr exception
        if (parent_bloc == nullptr) {
            return find_index(new_name);
        } else {
            // Convert the bloc pointer to a string
            new_name = get_var_name(parent_bloc, name);
            bloc = parent_bloc;
        }
    }
    return SymbolIndex.at(new_name);
}

Type CFG::find_type(string name, string realName) {
    if (SymbolType.find(name) == SymbolType.end()) {
        std::string error =
                "error : cannot find the type, the variable " + realName +
                " has not been declared \n";
        this->addErreur(error);
        return Type();
    } else {
        return SymbolType.at(name);
    }
}

Type CFG::get_var_type(AST::Bloc *bloc, string name) {
    // If it's a tmp variable created by ourselves we do not need to add the
    // bloc pointer to identify it.
    if (name.rfind('!', 0) == 0) {
        return find_type(name, name);
    }

    // Redefine the name of the variable, in order to identify it via it's bloc
    // pointer
    std::string new_name = get_var_name(bloc, name);
    if (bloc->parent_bloc == nullptr) {
        return find_type(new_name, name);

    }

    while (SymbolType.find(new_name) == SymbolType.end()) {
        AST::Bloc *parent_bloc = bloc->parent_bloc;
        // We need to do the last check inside of the loop else we will get
        // a nullptr exception
        if (parent_bloc == nullptr) {
            return find_type(new_name, name);
        } else {
            new_name = get_var_name(parent_bloc, name);
            bloc = parent_bloc;

        }
    }
    return SymbolType.at(new_name);
}

std::string CFG::new_BB_name() {
    return ".L" + this->name + std::to_string(nextBBnumber++);
}

BasicBlock *CFG::get_bb_before_last() {
    return this->basic_blocs.end()[-2];
}

void CFG::addErreur(std::string message) {
    this->error.addErrorMessage(message);
}

Erreur CFG::getErreur() {
    return error;
}
