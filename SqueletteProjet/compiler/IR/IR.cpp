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
C'est la méthode create_new_tempvar de l'IR qui s'occupera d'insérer la variable temporaire dans la table des symboles.

*/

int INTOFFSET = 4;

IRInstr::IRInstr(BasicBlock *bb_, Operation op_, Type t_,
                 vector<string> params_) : bb(bb_), op(op_), t(t_),
                                           params(params_) {}

// TODO
void IRInstr::gen_asm(ostream &o) {
    /* Exemple de ce qu'il faut mettre ici, la + longue méthode*/
    switch (op) {
        case Operation::ldconst : {
            // for const : params = [ name | value ]
            std::string regString = bb->cfg->IR_reg_to_asm(params[0]);
            o << "\tmovl $" << params[1] << ", " << regString << endl;
            break;
        }
        case Operation::copy: {
            // copy params [0] into params [1]
            std::string reg_tmp_var = bb->cfg->IR_reg_to_asm(params[0]);
            std::string reg_variable = bb->cfg->IR_reg_to_asm(params[1]);
            o << "\tmovl " << reg_tmp_var << ", %eax" << endl;
            o << "\tmovl %eax , " << reg_variable << endl;
            break;
        }
        case Operation::sub: {
            std::string regDestString = bb->cfg->IR_reg_to_asm(params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\tsubl " << reg2String << ", %eax" << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::mul: {
            std::string regDestString = bb->cfg->IR_reg_to_asm(params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\timull " << reg2String << ", %eax" << endl;
            o << "\tmovl %eax, " << regDestString << endl;
            break;
        }
        case Operation::add : {
            std::string regDestString = bb->cfg->IR_reg_to_asm(params[0]);
            std::string reg1String = bb->cfg->IR_reg_to_asm(params[1]);
            std::string reg2String = bb->cfg->IR_reg_to_asm(params[2]);

            o << "\tmovl " << reg1String << " , %eax" << endl;
            o << "\taddl " << reg2String << ", %eax" << endl;
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
            std::string dest_location = bb->cfg->IR_reg_to_asm(params[0]);
            o << "\tcmp $1, " << dest_location  << endl;
            o << "\tjne " << bb->exit_true->label << endl;
            o << "\tjmp " << bb->exit_false->label << endl;
            break;
        }
        case Operation::cmp_eq: {
            std::string dest_location = bb->cfg->IR_reg_to_asm(params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(params[2]);
            bool equal = params[3]=="eq";

            o << "\tmovl " <<  lValue << ", %eax" << endl;
            o << "\tcmp  %eax, " << rValue << endl;
            if(equal){
                o << "\tsete %dl" << endl;
            }else{
                o << "\tsetne %dl" << endl;
                }
            o << "\tmov %dl, " << dest_location << endl;
            break;
        }

        case Operation::cmp_low: {
            std::string dest_location = bb->cfg->IR_reg_to_asm(params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(params[2]);
            bool equal = params[3]=="eq";

            o << "\tmovl " <<  rValue << ", %eax" << endl;
            o << "\tcmp  %eax, " << lValue << endl;
            if(equal){
                o << "\tsetbe %dl" << endl;
            }else{
                o << "\tsetb %dl" << endl;
            }
            o << "\tmov %dl, " << dest_location << endl;
            break;

        }
        case Operation::cmp_great: {
            std::string dest_location = bb->cfg->IR_reg_to_asm(params[0]);
            std::string lValue = bb->cfg->IR_reg_to_asm(params[1]);
            std::string rValue = bb->cfg->IR_reg_to_asm(params[2]);
            bool equal = params[3]=="eq";

            o << "\tmovl " <<  lValue << ", %eax" << endl;
            o << "\tcmp  %eax, " << rValue << endl;
            if(equal){
                o << "\tsetae %dl" << endl;
            }else{
                o << "\tsetna %dl" << endl;
            }
            o << "\tmov %dl, " << dest_location << endl;
            break;

        }
        case Operation::ret: {
            // Récupère le paramètre
            std::string param = params[0];
            //Si le paramètre ne contient pas de ! c'est que c'est une variable
            if (param.at(0) != '!') {
                std::string regString = bb->cfg->IR_reg_to_asm(params[0]);
                o << "\tmovl " << regString << ", %eax" << endl;
            } else {
                // Le paramètre est une constante, on enlève le ! et on mets la constante dans %eax
                std::string value = param.erase(0, 1);
                o << "\tmovl $" << value << ", %eax" << endl;
            }
            break;
        }
        case Operation::neg: {
            std::string tmp_var = bb->cfg->IR_reg_to_asm(params[0]);
            std::string dest_var = bb->cfg->IR_reg_to_asm(params[1]);
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
    }
}

BasicBlock::BasicBlock(CFG *cfg, string entry_label) : cfg(cfg),
                                                       label(entry_label) {}

void BasicBlock::gen_asm(ostream &o) {
    std::string label = this-> label;
    if(label != "essai"){
        o << this->label << ": " << endl;
    }
    for (auto instr : instrs) {
        instr->gen_asm(o);
    }

}

void
BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
    instrs.push_back(new IRInstr(this, op, t, params));
}

CFG::CFG(AST::Bloc *ast_) : nextFreeSymbolIndex(0), nextBBnumber(0), ast(ast_) {
    auto firstBB = new BasicBlock(this, "essai");
    this->add_bb(firstBB);

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
std::string CFG::IR_reg_to_asm(string reg) {
    int offset = this->get_var_index(reg);
    std::string regString = std::to_string(offset) + "(%rbp)";
    return regString;
}

void CFG::gen_asm_prologue(ostream &o) {
    std::string label = this->current_bb->label;
        o << ".globl\tmain" << endl;
        o << "main:" << endl;
        o << "\tpushq %rbp" << endl;
        o << "\tmovq %rsp, %rbp" << endl;
}

void CFG::gen_asm_epilogue(ostream &o) {
    o << "\tpopq %rbp" << endl;
    o << "\tret" << endl;
}

void CFG::add_to_symbol_table(string name, Type t) {
    nextFreeSymbolIndex -= INTOFFSET;

    if (SymbolIndex.find(name) == SymbolIndex.end()) {
        SymbolType[name] = t;
        SymbolIndex[name] = nextFreeSymbolIndex;
    } else {
        std::string error =
                "error : int " + name + " has already been defined\n";
        cout << error << endl;
    }
}

std::string CFG::create_new_tempvar(Type t) {
    nextFreeSymbolIndex -= INTOFFSET;

    // nextFreeSymbolIndex is negative, so we put -nextFreeSymbolIndex in the tmp name
    std::string name_var_temp = "!tmp" + std::to_string(-nextFreeSymbolIndex);

    // Add new tmp var to the symbole table
    SymbolType[name_var_temp] = t;
    SymbolIndex[name_var_temp] = nextFreeSymbolIndex;
    return name_var_temp;
}

int CFG::get_var_index(string name) {
    return SymbolIndex.at(name);
}

Type CFG::get_var_type(string name) {
    return SymbolType.at(name);
}

std::string CFG::new_BB_name() {
    return ".L" + std::to_string(nextBBnumber++);
}




