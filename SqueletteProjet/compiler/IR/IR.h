#ifndef IR_H
#define IR_H

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include <map>
#include "../AST/AST.h"
#include "../Erreur/Erreur.h"



class Type;

class BasicBlock;

class CFG;

using namespace std;


/** class Type 
  * Type can be of 2 Types : char and int
*/
class Type {

public:
    typedef enum {
        type_int,
        type_char
    } type_enum;

    /**
     * @brief Type constructor
     * @param type_enum_
     */
    Type(type_enum type_enum_) : type_(type_enum_){};

    /**  default constructor */
    Type()=default;
	
    /**
     * @brief get_suffix
     * @return the suffix corresponding to the type
     *
     * Get the suffix needed by the assembly command
     */
    std::string get_suffix(){
        std::string suffix;
        switch (type_) {
            case type_enum::type_int: {
                suffix="l";
                break;
            }
            case type_enum::type_char: {
                suffix="b";
                break;
            }
        }
        return suffix;
    }

    /**
     * @brief get_offset
     * @return the offset corresponding to the type
     *
     * Get the suffix to know the offset for "-X(%rbp)
     */
    int get_offset(){
            int offset;
            switch (type_) {
                    case type_enum::type_int: {
                            offset=INTOFFSET;
                            break;
                    }
                    case type_enum::type_char: {
                            offset=CHAROFFSET;
                            break;
                    }
            }
            return offset;
    }

    //------Attributs--------

    type_enum type_;

    /** Size of an int (in bytes) */
    int INTOFFSET = 4;

    /** Size of a char (in bytes) */
    int CHAROFFSET=1;

};


/** class IRInstr for one 3-address instruction 
*/ 
class IRInstr {

public:
    /** The instructions that are accepted */
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
        if_,
        cmp_eq,
        cmp_low,
        cmp_great,
        ret,
        return_,
        return_expr,
        call_proc,
        add_fct_param,
        add_fct_param_stack,
        call_fct,
        get_arg,
        neg,
        putchar
    } Operation;


    /**
     * @brief IRInstr constructor
     * @param bb_ the BasicBlock this instruction belongs to
     * @param op Operator corresponding to the instruction
     * @param t Type of the instruction ( int or char )
     * @param params vector containing the variables
     */
    IRInstr(BasicBlock *bb_, Operation op, Type t, vector<string> params);

    /**
     * @brief gen_asm
     * @param o outpustream where the assembly code will be written
     *
     * Write the x86 assembly code for this instruction
     */
    void gen_asm(ostream &o);

private:
    /** The BB this instruction belongs to,
     * which provides a pointer to the CFG this instruction belong to */
    BasicBlock *bb;

    /** Operator corresponding to the instruction */
    Operation op;

    /** Type of the instruction ( int or char ) */
    Type t;

    /** ector containing the variables
     * For 3-op instrs: d, x, y; for ldconst: d, c ; ... */
    vector<string> params;
};


/** class BasicBlock
*/
class BasicBlock {
public:

    /**
     * @brief BasicBlock constructor
     * @param cfg the CFG where the block belongs
     * @param entry_label
     */
    BasicBlock(CFG *cfg, string entry_label);

    /**
     * @brief gen_asm
     * @param o outpustream where the assembly code will be written
     *
     * Write the x86 assembly code for this basic block
     */
    void gen_asm(ostream &o);

    /**
     * @brief add_IRInstr
     * @param line where the instruction has been written ( in the .c file)
     * @param column where the instruction has been written ( in the .c file)
     * @param op Operator corresponding to the instruction
     * @param t Type of the instruction ( int or char )
     * @param params vector containing the variables
     *
     * Add instruction to the instrs vector
     */
    void add_IRInstr(int line, int column, IRInstr::Operation op, Type t, vector<string> params);

    //-------------------Attributs---------------------

    /** Pointer to the next basic block, true branch.
      * If nullptr, return from procedure */
    BasicBlock *exit_true;

    /** Pointer to the next basic block, false branch.
      *  If null_ptr, the basic block ends with an unconditional jump */
    BasicBlock *exit_false;

    /** Label of the BB, also will be the label in the generated code */
    string label;

    /**  The CFG where this block belongs */
    CFG *cfg;

    /**  Vector containing the instructions of the block */
    vector<IRInstr *> instrs;

    /** Bloc to which the bb belongs, needed for the symbol table*/
    AST::Bloc *bloc;

protected:
};




/** Control Flow Graph
*/
class CFG {
public:
    /**
     * @brief CFG constructor
     * @param ast AST::Bloc where the CFG comes from
     * @param name of the CFG
     */
    CFG(AST::Bloc *ast, std::string name);

    /**
     * @brief add_bb
     * @param bb BasicBlock
     *
     * Add the bb to the basic_blocs vector
     */
    void add_bb(BasicBlock *bb);

    /**
     * @brief gen_asm
     * @param o outpustream where the assembly code will be written
     *
     * Write the x86 assembly code generation for this basic block
     */
    void gen_asm(ostream &o);

    /**
     * @brief IR_reg_to_asm
     * @param bloc AST::Bloc to which the bb belongs
     * @param reg string to which we must find the index
     * @return regString string that looks like "-Index(%rbp)"
     */
    string IR_reg_to_asm(AST::Bloc *bloc, string reg);

    /**
     * @brief gen_asm_prologue
     * @param o outpustream where the assembly code will be written
     *
     * Write the x86 assembly prologue code for this CFG
     */
    void gen_asm_prologue(ostream &o);

    /**
     * @brief gen_asm_epilogue
     * @param o outpustream where the assembly code will be written
     *
     * Write the x86 assembly epilogue code for this CFG
     */
    void gen_asm_epilogue(ostream &o);

    /**
     * @brief add_to_symbol_table
     * @param line where the instruction has been written ( in the .c file)
     * @param column where the instruction has been written ( in the .c file)
     * @param bloc AST::Bloc to which the bb belongs
     * @param name of the variable
     * @param t Type of the instruction ( int or char )
     *
     * Add the variable to the SymbolIndex and SymbolType
     * If it already exists, add the error to Erreur
     */
    void add_to_symbol_table(int line, int column, AST::Bloc *bloc, string name, Type t);

    /**
     * @brief create_new_temp_var
     * @param t Type of the instruction ( int or char )
     * @return the name of the new temp variable
     */
    string create_new_temp_var(Type t);

    /**
     * @brief get_var_index
     * @param bloc AST::Bloc to which the bb belongs
     * @param name of the variable
     * @return int, the index of the SymbolIndex corresponding to the name
     */
    int get_var_index(AST::Bloc *bloc, string name);

    /**
     * @brief get_var_type
     * @param bloc AST::Bloc to which the bb belongs
     * @param name of the variable
     * @return Type, the Type of the SymbolType corresponding to the name
     */
    Type get_var_type(AST::Bloc *bloc, string name);

    /**
     * @brief new_BB_name
     * @return the name of the new BasicBlock
     */
    string new_BB_name();

    /**
     * @brief get_bb_before_last
     * @return the BasicBlock that is before the last BasicBlock
     */
    BasicBlock *get_bb_before_last();

    /**
     * @brief find_index
     * @param name of the variable
     * @return int, the index of the SymbolIndex corresponding to the name
     *
     * The name is the name of the variable to which we have added the num of the AST:Bloc
     * to allow the user to give the same name to variables that are in different AST::Bloc
     */
    int find_index(string name);

    /**
     * @brief find_type
     * @param name of the variable
     * @param realName of the variable
     * @return Type, the Type of the SymbolIndex corresponding to the name
     *
     * The realName is the name used in the .c code, we need it to display the error
     *
     * The name is the name of the variable to which we have added the num of the AST:Bloc
     * to allow the user to give the same name to variables that are in different AST::Bloc
     */
    Type find_type(string name, string realName);

    /**
     * @brief get_name
     * @return string, the name of the CFG
     */
    std::string get_name();

    /**
     * @brief set_name
     * @param name
     *
     * Set the name of the CFG
     */
    void set_name(std::string name);

    /**
     * @brief getNextFreeSymbolIndex
     * @return int, the index of the next free symbol
     */
    int getNextFreeSymbolIndex();

    /**
     * @brief getErreur
     * @return Erreur, the error of the CFG
     */
    Erreur getErreur();

    /**
     * @brief addErreur
     * @param message, error message
     *
     * Add the message to the error message of the object Erreur
     */
    void addErreur(std::string message);

    /**
     * @brief hasError
     * @return boo
     *
     * Return true if an error has been raised
     * Else return False
     */
    bool hasError();

    /**
     * @brief getErrorMessage
     * @return string, corresponding to the concatenation of
     * all of the messages that the error contains
     */
    std::string getErrorMessage();


    //-------------------------Attributs--------------------------

    /** The AST::Bloc this CFG comes from */
    AST::Bloc *ast;

    /** Current BasicBlock of the CFG */
    BasicBlock *current_bb;

    /** Name of the CFG */
    std::string name;

protected:
    /** Part of the symbol table  */
    map<string, Type> SymbolType;

    /** Part of the symbol table  */
    map<string, int> SymbolIndex;

    /** The index of the next free symbol in the Symbol table */
    int nextFreeSymbolIndex;

    /** Num of the next BasicBlock */
    int nextBBnumber;

    /** Vector containing the BasicBlocks of the CFG */
    vector<BasicBlock *> basic_blocs;

    /** Error raised by the CFG */
    Erreur error;
};


#endif
