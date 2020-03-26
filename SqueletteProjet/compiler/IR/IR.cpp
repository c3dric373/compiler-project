#include "IR.h"

//nothing to add here
IRInstr::IRInstr(BasicBlock* bb_, Operation op_, Type t_, vector<string> params_) : bb(bb_), op(op_), t(t_), params(params_) {}

void IRInstr::gen_asm(ostream &o){
	 /* Exemple de ce qu'il faut mettre ici, la + longue méthode*/
	switch(op) {
        case Operation::ldconst :
			// for const : params = [ name | value ]
            offset = bb->cfg->get_var_index(params[0]);
            o << "movl $" << params[1] << "," << offset <<"(%rbp)" << endl;
            break;
		case operation::copy:
			break;
		case operation::sub:
			break;
		case operation::mul:
			break;
        case Operation::add :
            offsetDest = bb->cfg->get_var_index(params[0]);
            offsetParam1 = bb->cfg->get_var_index(params[1]);
            offsetParam2 = bb->cfg->get_var_index(params[2]);

            o << "\tmovl "<< offsetParam1 << "(%rbp), %eax\n" << endl;
            o << "\taddl " << offsetParam2 << "(%rbp), %eax\n" << endl;
            o << "movq %eax, " << offsetDest << "(%rbp)" << endl;
            break;
		case operation::rmem:
			break;
		case operation::wmem:
			break;
		case operation::call:
			break;
		case operation::cmp_eq:
			break;
		case operation::cmp_lt:
			break;
		case operation::cmp_le:
			break;

}

//nothing to add here
BasicBlock::BasicBlock(CFG* cfg, string entry_label : cfg(cfg), label(entry_label) {}

void BasicBlock::gen_asm(ostream& o) {

}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params) {
	instrs.push_back(new IRInstr(this, op, t, params));
}

CFG::CFG(DefFonction* ast){

}

//nothing to add here
void CFG::add_bb(BasicBlock* bb){
	bbs.push_back(bb);
}

//nothing to add here
void CFG::gen_asm(ostream& o){
	for (auto bb : bbs) {
        bb->gen_asm(o);
    }
}

std::string CFG::IR_reg_to_asm(string reg){
	return "";
}

void CFG::gen_asm_prologue(ostream& o){

}

void CFG::gen_asm_epilogue(ostream& o){

}

void CFG::add_to_symbol_table(string name, Type t){

}

string CFG::create_new_tempvar(Type t){
	return "";
}

//nothing to add here
int CFG::get_var_index(string name){
	return SymbolIndex.at(name);
}

//nothing to add here
Type CFG::get_var_type(string name){
	return SymbolType.at(name);
}

std::string CFG::new_BB_name(){
	return "";
}




