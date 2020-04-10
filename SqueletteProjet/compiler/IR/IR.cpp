#include <sstream>
#include "IR.h"

// Généré à partir de IR.h



//------------------------------IRInstr---------------------------------

IRInstr::IRInstr(BasicBlock *bb_, Operation op_, Type t_,
                 vector<string> params_) : bb(bb_), op(op_), t(t_),
                                           params(params_) {}

void IRInstr::gen_asm(ostream &o) {
    // Suffix of assembly code corresponding to the Type
    std::string type = t.get_suffix();
    // Ast::Bloc of the BasicBlock
    AST::Bloc *bloc = bb->bloc;
    vector<std::string> registers = {"%edi", "%esi", "%edx", "%ecx", "%r8d",
                                     "%r9d"};
    switch (op) {
        case Operation::ldconst : {
            // For const : params = [ name | value ]

            // Get the "-Index(%rbp)" corresponding to params
            std::string regString = bb->cfg->IR_reg_to_asm(bloc, params[0]);

            // Create assembly code
            o << "\tmov" + type + " $" << params[1] << ", " << regString
              << endl;
            break;
        }

        case Operation::copy: {
            // copy params [0] into params [1]

            // Get the "-Index(%rbp)" corresponding to params
            std::string reg_tmp_var;
            if (params[0] == "%eax") {
                reg_tmp_var = params[0];
            } else {
                reg_tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            }
            std::string reg_variable = bb->cfg->IR_reg_to_asm(bloc, params[1]);

            // Create assembly code
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
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tsubl " << reg2String << ", %eax" << "# " << params[1]
              << " - " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::mul: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\timull " << reg2String << ", %eax" << " # " << params[1]
              << " * " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::add : {
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\taddl " << reg2String << ", %eax" << " # " << params[1]
              << " + " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::and_: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tand " << reg2String << ", %eax" << " # " << params[1]
              << " and " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::xor_: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\txor " << reg2String << ", %eax" << " # " << params[1]
              << " xor " << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::or_: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string regDestString = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(bloc, params[2]);

            // Create assembly code
            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tor " << reg2String << ", %eax" << " # " << params[1]
              << " or" << params[2] << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::if_: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string expr = bb->cfg->IR_reg_to_asm(bloc, params[0]);

            // Create assembly code
            o << "\tcmpl $1, " << expr << endl;
            o << "\tje " << bb->exit_true->label << endl;
            o << "\tjmp " << bb->exit_false->label << endl;
            break;
        }
        case Operation::cmp_eq: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            // Create assembly code
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
            // Get the "-Index(%rbp)" corresponding to params
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            // Create assembly code
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
            // Get the "-Index(%rbp)" corresponding to params
            std::string dest_location = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(bloc, params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(bloc, params[2]);
            bool equal = !(params[3].compare("eq"));

            // Create assembly code
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
            // Get the "-Index(%rbp)" corresponding to params
            std::string tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            std::string dest_var = bb->cfg->IR_reg_to_asm(bloc, params[1]);

            // Create assembly code
            o << "\tmovl " << tmp_var << ", %eax" << endl;
            o << "\tNEG %eax" << endl;
            o << "\tmovl %eax, " << dest_var << endl;
            break;
        }
        case Operation::jmp: {
            std::string basic_block = params[0];

            // Create assembly code
            o << "\t jmp " << basic_block << endl;
            break;
        }
        case Operation::add_fct_param: {
            // copy params [0] into params [1]
            string registers[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d",
                                  "%r9d"};
            int num = std::stoi(params[1]);
            // Get the "-Index(%rbp)" corresponding to params
            std::string reg_tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);

            // Create assembly code
            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << reg_tmp_var << ", "
                      << registers[num]
                      << " # fct param " << params[0] << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovl " << reg_tmp_var << ", " << registers[num]
                      << " # fct param " << params[0] << endl;
                    break;
                }
            }
            break;
        }
        case Operation::add_fct_param_stack: {
            // copy params [0] into params [1]
            // Get the "-Index(%rbp)" corresponding to params
            std::string reg_tmp_var = bb->cfg->IR_reg_to_asm(bloc, params[0]);
            int offset = std::stoi(params[1]);

            // Create assembly code
            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << reg_tmp_var << ", "
                      << "%eax" << endl;
                    o << "\tmovl %eax, " << offset << "(%rbp)"
                      << " # fct param " << params[0] << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovl " << reg_tmp_var << ", "
                      << "%eax" << endl;
                    o << "\tmovl %eax, " << offset << "(%rbp)"
                      << " # fct param " << params[0] << endl;
                    break;
                }
            }
            break;
        }
        case Operation::call_fct: {
            std::string fct_name = params[0];
            // Get the "-Index(%rbp)" corresponding to params
            std::string location_dest = bb->cfg->IR_reg_to_asm(bloc, params[1]);

            // Create assembly code
            o << "\tcall " << fct_name << endl;
            switch (t.type_) {
                case Type::type_char : {
                    o << "\tmovb %al, " << location_dest << endl;
                    break;
                }
                default:
                    o << "\tmovl %eax, " << location_dest << endl;
            }
            break;
        }
        case Operation::call_proc: {
            std::string fct_name = params[0];

            // Create assembly code
            o << "\tcall " << fct_name << endl;
            break;
        }
        case Operation::get_arg: {
            // Arguments will be passed from left to right by the caller in the
            // registers :
            int num_arg = std::stoi(params[0]);
            // Get the "-Index(%rbp)" corresponding to params
            std::string location_arg = bb->cfg->IR_reg_to_asm(bloc, params[1]);

            // Create assembly code
            switch (t.type_) {
                case Type::type_int : {
                    o << "\tmovl " << registers[num_arg] << ", " << location_arg
                      << "# write arg " << params[1] << endl;
                    break;
                }
                case Type::type_char : {
                    o << "\tmovl " << registers[num_arg] << ", " << "%eax"
                      << "# relocate because arg is a char: " << params[1]
                      << endl;
                    o << "\tmovb %al, " << location_arg
                      << "# write arg " << params[1] << endl;
                    break;
                }
            }
            break;
        }

        case Operation::return_: {
            // Create assembly code
            o << "\tnop" << endl;
            std::string epilogue_label = "." + this->bb->cfg->name + "_ret";
            o << "\t jmp " << epilogue_label << endl;
            break;
        }
        case Operation::return_expr: {
            if (params[0] == "%eax") {
                o << "\tnop" << endl;
            } else {
                std::string return_address = bb->cfg->IR_reg_to_asm(bloc,
                                                                    params[0]);
                o << "\tmovl " + return_address + ", %eax" << endl;
            }
            std::string epilogue_label = "." + this->bb->cfg->name + "_ret";
            o << "\t jmp " << epilogue_label << endl;
            break;
        }
        case Operation::putchar: {
            // Get the "-Index(%rbp)" corresponding to params
            std::string location_arg = bb->cfg->IR_reg_to_asm(bloc, params[0]);

            // Create assembly code
            o<<"\tmovsbl "<<location_arg<<", %eax"<<std::endl
            <<"\tmovl %eax, %edi"<<std::endl
            <<"\tcall putchar"<<std::endl;
            break;
        }
    }
}


//------------------------------BasicBlock---------------------------------


BasicBlock::BasicBlock(CFG *cfg, string entry_label) : cfg(cfg),
                                                       label(entry_label) {}

void BasicBlock::gen_asm(ostream &o) {
    std::string label = this->label;
    // Add the label of the BasicBlock if it exists
    if (!label.empty()) {
        o << this->label << ": " << endl;
    }
    // Generate assembly code for each instruction contained in the instrs vector
    for (auto instr : instrs) {
        instr->gen_asm(o);
    }
}

void
BasicBlock::add_IRInstr(int line, int column, IRInstr::Operation op, Type t,
                        vector<string> params) {
    // Syntactic analysis:
    // Find out if the variable placed in params has already been declared
    // if offset == 12000, it hasn't been declared
    for (std::string param : params) {
        if (param != "%eax") {
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
            if (offset == 12000) {
                std::string erreur =
                        "error line " + std::to_string(line) + " column " +
                        std::to_string(column) +
                        " : cannot find the offset, the variable " + param +
                        " has not been declared \n";
                this->cfg->addErreur(erreur);
            }
        }
    }
    // If there is no error, we can push the instruction to the instrs vector
    instrs.push_back(new IRInstr(this, op, t, params));
}


//------------------------------CFG---------------------------------


CFG::CFG(AST::Bloc *ast_, std::string name) : nextFreeSymbolIndex(0),
                                              nextBBnumber(0), ast(ast_) {
    // Create a BasicBlock
    auto firstBB = new BasicBlock(this, "");
    // Add the firstBB to the BasicBlocks vector
    this->add_bb(firstBB);
    this->name = name;

    // Create just one block with no next Block
    firstBB->exit_false = nullptr;
    firstBB->exit_true = nullptr;

    // Set the current Block
    current_bb = firstBB;
}

void CFG::add_bb(BasicBlock *bb) {
    basic_blocs.push_back(bb);
}

void CFG::gen_asm(ostream &o) {
    // Generate assembly code of the prologue
    gen_asm_prologue(o);
    // Generate assembly code for each BasicBlock contained in the CFG
    for (auto bb : basic_blocs) {
        bb->gen_asm(o);
    }
    // Generate assembly code of the epilogue
    gen_asm_epilogue(o);
}


std::string CFG::IR_reg_to_asm(AST::Bloc *bloc, string reg) {
    // Take a variable and transform it to "-offset(%rbp)"
    // Get the offset of the variable
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
    o << "\tsubq $" << this->nextFreeSymbolIndex * (-1) << ", %rsp" << endl;
}

void CFG::gen_asm_epilogue(ostream &o) {
    std::string epilogue_label = "." + this->name + "_ret";
    o << epilogue_label << ":" << endl;
    o << "\taddq $" << this->nextFreeSymbolIndex * (-1) << ", %rsp" << endl;
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
    // Get the nex free index in the SymbolIndex
    nextFreeSymbolIndex -= t.get_offset();

    switch (t.type_) {
        case Type::type_int: {    
            type = "int";
            break;
        }
        case Type::type_char: {
            type = "char";
            break;
        }
    }

    // Redefine the name of the variable, in order to identify it via it's bloc
    // pointer
    std::string new_name = get_var_name(bloc, name);

    if (SymbolIndex.find(new_name) == SymbolIndex.end()) {
        // The new_name has not been found in the SymbolIndex
        // We can add new_name to SymbolIndex and SymbolType
        SymbolType[new_name] = t;
        SymbolIndex[new_name] = nextFreeSymbolIndex;
    } else {
        // The new_name already exists in the SymbolIndex

        std::string erreur =
                "error line " + std::to_string(line) + " column " +
                std::to_string(column) + " : " + type + " " + name +
                " has already been defined\n";
        error.addErrorMessage(erreur);
    }
}

std::string CFG::create_new_temp_var(Type t) {
    // Get the nex free index in the SymbolIndex
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
        // The name has not been found in the SymbolIndex
        // An error should be raised : here return 12000
        return 12000;
    } else {
        // The name has been found in the SymbolIndex
        // Return the index corresponding to the name
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
        // The name has not been found in the SymbolIndex
        // An error should be raised
        std::string error =
                "error : cannot find the type, the variable " + realName +
                " has not been declared \n";
        this->addErreur(error);
        return Type();
    } else {
        // The name has been found in the SymbolIndex
        // Return the index corresponding to the name
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
    // Return the index corresponding to the new_name
    return SymbolType.at(new_name);
}

std::string CFG::new_BB_name() {
    return ".L" + this->name + std::to_string(nextBBnumber++);
}

BasicBlock *CFG::get_bb_before_last() {
    return this->basic_blocs.end()[-2];
}

//------------------------------Erreur---------------------------------

void CFG::addErreur(std::string message) {
    this->error.addErrorMessage(message);
}

Erreur CFG::getErreur() {
    return error;
}

bool CFG::hasError() {
    return error.getError();
}

std::string CFG::getErrorMessage() {
    return error.getMessage();
}
