#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include "../AST/AST.h"

// Declarations from the parser -- replace with your own
class Type;

class BasicBlock;

class CFG;

using namespace std;


//bullshit class just to compile
class Type {
public:
    Type() = default;;
};

//! The class for one 3-address instruction
class IRInstr {

public:
    /** The instructions themselves -- feel free to subclass instead */
    typedef enum {
        ldconst,
        jmp,
        and_,
        xor_,
        or_,
        copy,
        add,
        sub,
        mul,
        rmem,
        wmem,
        call,
        if_,
        cmp_eq,
        cmp_low,
        cmp_great,
        ret,
        neg
    } Operation;


    /**  constructor */
    IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params);

    /** Actual code generation */
    void
    gen_asm(ostream &o); /**< x86 assembly code generation for this IR instruction */

    BasicBlock *bb;
private:
    /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
    Operation op;
    Type t;
    vector<string> params; /**< For 3-op instrs: d, x, y; for ldconst: d, c;  For call: label, d, params;  for wmem and rmem: choose yourself */
    // if you subclass IRInstr, each IRInstr subclass has its parameters and the previous (very important) comment becomes useless: it would be a better design.
};






/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then
		    if  exit_true  is a  nullptr,
            the epilogue is generated
        else if exit_false is a nullptr,
          an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
          an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting
  the if, while, etc of the AST  to IR.

Possible optimization:
     a cmp_* comparison instructions, if it is the last instruction of its block,
       generates an actual assembly comparison
       followed by a conditional jump to the exit_false branch
*/

class BasicBlock {
public:
    BasicBlock(CFG *cfg, string entry_label);

    void
    gen_asm(ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

    void add_IRInstr(IRInstr::Operation op, Type t, vector<string> params);

    // No encapsulation whatsoever here. Feel free to do better.
    BasicBlock *exit_true;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */
    BasicBlock *exit_false; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */
    string label; /**< label of the BB, also will be the label in the generated code */
    CFG *cfg; /** < the CFG where this block belongs */
    vector<IRInstr *> instrs; /** < the instructions themselves. */
    string test_var_name;  /** < when generating IR code for an if(expr) or while(expr) etc,
												 store here the name of the variable that holds the value of expr */
    AST::Bloc *bloc; /** bloc to which the bb belongs, needed for the symbol table*/

protected:


};




/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of basic_blocs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
public:
    CFG(AST::Bloc *ast);

    AST::Bloc *ast; /**< The AST this CFG comes from */

    void add_bb(BasicBlock *bb);

    // x86 code generation: could be encapsulated in a processor class in a retargetable compiler
    void gen_asm(ostream &o);

    string IR_reg_to_asm(AST::Bloc *bloc,
                         string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */
    void gen_asm_prologue(ostream &o);

    void gen_asm_epilogue(ostream &o);

    // symbol table methods
    void add_to_symbol_table(AST::Bloc *bloc, string name, Type t);

    string create_new_temp_var(Type t);

    int get_var_index(AST::Bloc *bloc, string name);

    Type get_var_type(string name);

    // basic block management
    string new_BB_name();

    BasicBlock *current_bb;

    BasicBlock *get_bb_before_last();

    void cleanSymbolTable(AST::Bloc *bloc);

protected:
    map<string, Type> SymbolType; /**< part of the symbol table  */
    map<string, int> SymbolIndex; /**< part of the symbol table  */
    int nextFreeSymbolIndex; /**< to allocate new symbols in the symbol table */
    int nextBBnumber; /**< just for naming */

    vector<BasicBlock *> basic_blocs; /**< all the basic blocks of this CFG*/
private:
    void deleteSymbol(AST::Bloc *bloc,std::string name);
    std::string create_var_name(AST::Bloc *bloc, std::string name);
};


#endif
