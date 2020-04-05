#ifndef AST_AST_H
#define AST_AST_H

#include <iostream>
#include <vector>
#include "SymbolTable.h"

enum TYPES {INT, CHAR, NBTYPES};

class BasicBlock;

class CFG;

class IRInstr;

class Type;

namespace AST {
    class Bloc;

    namespace Expr {
        class Expr {
        public:
            virtual int getValue() = 0;

            virtual std::string buildIR(bool not_flag) = 0;

            virtual void exists(SymbolTable &st) = 0;

            virtual void buildReturnIR() = 0;

            virtual void display() = 0;
        };

        class Add : public Expr {
        public:
            Add(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Add(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line),
                    column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Sub : public Expr {
        public:
            Sub(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Sub(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line),
                    column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Mult : public Expr {
        public:
            Mult(Expr *lValue, Expr *rValue) : lValue(lValue),
                                               rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Mult(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line),
                    column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Minus : public Expr {
        public:
            Minus(Expr *value, unsigned line, unsigned column) : value(value),
                                                                 line(line),
                                                                 column(column) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class And : public Expr {
        public:
            And(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            And(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Or : public Expr {
        public:
            Or(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Or(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Xor : public Expr {
        public:
            Xor(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Xor(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            Expr *lValue;
            Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Const : public Expr {
        public:
            Const(int value) : value(value) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Const(int value, unsigned line, unsigned column) :
                    value(value), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            int value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class ConstChar : public Expr {
        public:
            ConstChar(char value) : value(value) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            ConstChar(char value, unsigned line, unsigned column) :
                    value(value), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            char value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Name : public Expr {
        public:
            Name(std::string name) : name(name) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void exists(SymbolTable &st) override;

            Name(std::string name, unsigned line, unsigned column) :
                    name(name), line(line), column(column) {};

            void buildReturnIR() override;

            void display() override;

        private:
            std::string name;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        //COMPARAISONS ET BOOLEENS

        class Eq : public Expr {
        public:
            Eq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line,
               unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            int getValue() override;

            std::string buildIR(bool not_flag) override;

            void exists(SymbolTable &st) override;

            void buildReturnIR() override {};

            void display() override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Neq : public Expr {
        public:
            Neq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line,
                unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;


            std::string buildIR(bool not_flag) override;

            void exists(SymbolTable &st) override;

            void buildReturnIR() override {};

            int getValue() override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Leq : public Expr {
        public:
            Leq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line,
                unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            std::string buildIR(bool not_flag) override;

            void exists(SymbolTable &st) override;

            int getValue() override;

            void buildReturnIR() override {};

            void display() override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Low : public Expr {
        public:
            Low(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line,
                unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            virtual void display() override;

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void buildReturnIR() override {};

            void exists(SymbolTable &st) override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Geq : public Expr {
        public:
            Geq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line,
                unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void buildReturnIR() override {};

            void exists(SymbolTable &st) override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Great : public Expr {
        public:
            Great(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue,
                  unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void buildReturnIR() override {};

            void exists(SymbolTable &st) override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Not : public Expr {
        public:
            Not(Expr *value, unsigned line, unsigned column) :
                    value(value), line(line), column(column) {};

            std::string buildIR(bool not_flag) override;

            int getValue() override;

            void display() override;

            void buildReturnIR() override {};

            void exists(SymbolTable &st) override;

        private:
            Expr *value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };
    }


    namespace Instr {
        class Instr {
        public:
            virtual std::string buildIR() = 0;

            virtual void display() = 0;

            virtual bool wrongReturnType(bool returnType) = 0;
        };

        class DeclInt : public Instr {
        public:
            DeclInt(std::vector<std::string> names, unsigned line, unsigned column) :
                    names(names), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::vector<std::string> names;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class DeclChar : public Instr {
        public:
            DeclChar(std::vector<std::string> names, unsigned line, unsigned column) :
                    names(names), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::vector<std::string> names;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class DefInt : public Instr {
        public:
            DefInt(std::string name, Expr::Expr *expr, unsigned line, unsigned column) :
                    name(name), expr(expr), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::string name;
            Expr::Expr *expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class DefChar : public Instr {
        public:
            DefChar(std::string name, Expr::Expr *expr, unsigned line, unsigned column) :
                    name(name), expr(expr), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::string name;
            Expr::Expr *expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Affct : public Instr {
        public:
            Affct(std::string name, Expr::Expr *expr, unsigned line,
                  unsigned column) :
                    name(name), expr(expr), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::string name;
            Expr::Expr *expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class If : public Instr {
        public:
            If(Expr::Expr *expr, AST::Bloc *bloc) :
                    expr(expr), bloc(bloc) {};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            Expr::Expr *expr;
            AST::Bloc *bloc;
        };

        class IfElse : public Instr {
        public:
            IfElse(Expr::Expr *expr, AST::Bloc *ifBloc, AST::Bloc *elseBloc) :
                    expr(expr), ifBloc(ifBloc), elseBloc(elseBloc) {};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            Expr::Expr *expr;
            AST::Bloc *ifBloc;
            AST::Bloc *elseBloc;
        };

        class While : public Instr {
        public:
            While(Expr::Expr *expr, AST::Bloc *bloc) :
                    expr(expr), bloc(bloc) {};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            Expr::Expr *expr;
            AST::Bloc *bloc;
        };

        class Bloc : public Instr {
        public:
            Bloc(AST::Bloc *bloc) :
                    bloc(bloc) {};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            AST::Bloc *bloc;
        };

        class CallProc : public Instr {
        public:
            CallProc(std::string procName, std::vector<std::string> args):
            procName(procName), args(args){};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            std::string procName;
            std::vector<std::string> args;
        };

        class Return : public Instr {
        public:
            Return(unsigned line, unsigned column):
            line(line), column(column){};
            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class ReturnExpr : public Instr {
        public:
            ReturnExpr(Expr::Expr* expr, unsigned line, unsigned column):
            expr(expr), line(line), column(column){};

            void display() override;

            std::string buildIR() override;

            bool wrongReturnType(bool returnType) override;

        private:
            Expr::Expr* expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };
    }

    namespace InitInstr{
        class InitInstr {
        public:
            virtual std::string buildIR() = 0;

            virtual void display() = 0;
        };

        class DefProc : public InitInstr {
        public:
            DefProc(std::string procName, AST::Bloc* bloc, unsigned line, unsigned column) :
                    procName(procName), bloc(bloc), line(line), column(column) {};

            void pushArg(std::string type, std::string name);

            std::string buildIR() override;

            void display() override;

        private:
            std::string procName;
            std::vector<TYPES> types;
            std::vector<std::string> names;
            Bloc* bloc;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };
    }

    class InitBloc {
    public:
        std::string buildIR();

        void pushInstr(InitInstr::InitInstr *instr);

        void display();

    private:
        std::vector<InitInstr::InitInstr *> blocinstr;
    };

    class Bloc {
    public:
        std::string buildIR();

        void pushInstr(Instr::Instr *instr);

        void display();

        bool wrongReturnType(bool returnType);

    private:
        std::vector<Instr::Instr *> blocinstr;
    };

    class Prog {
    public:
        Prog(InitBloc* initBloc, Bloc *bloc, Expr::Expr *returnValue):
        initBloc(initBloc), bloc(bloc), returnValue(returnValue) {};

        std::string buildIR();

        bool create_symbol_table();

        std::vector<CFG *> generateIR();

        std::string getErrorMsg();

        void display();

    private:
        InitBloc* initBloc;
        Bloc* bloc;
        Expr::Expr *returnValue;
        SymbolTable table;
    };
}

#endif //AST_AST_H
