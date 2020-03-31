#ifndef AST_AST_H
#define AST_AST_H

#include <iostream>
#include <vector>
#include "SymbolTable.h"

class BasicBlock;
class CFG;
class IRInstr;
class Type;

namespace AST{
    class Bloc;

    namespace Expr {
        class Expr {
        public:
            virtual int getValeur() = 0;

            virtual std::string buildIR() = 0;

            virtual void exists(SymbolTable &st) = 0;

			virtual void buildReturnIR() = 0;

            virtual void display() = 0;
        };

        class Add : public Expr {
        public:
            Add(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR() override;

            int getValeur() override;

            void exists(SymbolTable &st) override;

            Add(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

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

            std::string buildIR() override;

            int getValeur() override;

            void exists(SymbolTable &st) override;

            Sub(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

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
            Mult(Expr *lValue, Expr *rValue) : lValue(lValue), rValue(rValue) {};

            std::string buildIR() override;

            int getValeur() override;

            void exists(SymbolTable &st) override;

            Mult(Expr *lValue, Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue), line(line), column(column) {};

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
            Minus(Expr *value, unsigned line, unsigned column) : value(value), line(line), column(column) {};

            std::string buildIR() override;

            int getValeur() override;

            void exists(SymbolTable &st) override;

			void buildReturnIR() override {};

            void display() override;

        private:
            Expr *value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Const : public Expr {
        public:
            Const(int value) : value(value) {};

            std::string buildIR() override;

            int getValeur() override;

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

        class Name : public Expr {
        public:
            Name(std::string name) : name(name) {};

            std::string buildIR() override;

            int getValeur() override;

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
            Eq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            int getValeur() override;

            std::string buildIR() override;

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
            Neq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;

            std::string buildIR() override;

            void exists(SymbolTable &st) override;

			void buildReturnIR() override {};

            int getValeur() override;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Leq : public Expr {
        public:
            Leq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            std::string buildIR() override;

            void exists(SymbolTable &st) override;

            int getValeur() override;

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
            Low(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            virtual void display() override;

            std::string buildIR() override;

            int getValeur() override;

			void buildReturnIR() override {};

            void exists(SymbolTable &st) override ;

        private:
            AST::Expr::Expr *lValue;
            AST::Expr::Expr *rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Geq : public Expr {
        public:
            Geq(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;

            std::string buildIR() override;

            int getValeur() override;

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
            Great(AST::Expr::Expr *lValue, AST::Expr::Expr *rValue, unsigned line, unsigned column) :
                    lValue(lValue), rValue(rValue) {};

            void display() override;

            std::string buildIR() override;

            int getValeur() override;

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

            std::string buildIR() override;

            int getValeur() override;

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

            virtual void addToTable(SymbolTable &st) = 0;

            virtual void display() = 0;
        };

        class Decl : public Instr {
        public:
            Decl(std::vector<std::string> names, unsigned line, unsigned column) :
                    names(names), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            void addToTable(SymbolTable &table) override;

        private:
            std::vector<std::string> names;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Def : public Instr {
        public:
            Def(std::string name, Expr::Expr *expr, unsigned line, unsigned column) :
                    name(name), expr(expr), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            void addToTable(SymbolTable &table) override;

        private:
            std::string name;
            Expr::Expr *expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Affct : public Instr {
        public:
            Affct(std::string name, Expr::Expr *expr, unsigned line, unsigned column) :
                    name(name), expr(expr), line(line), column(column) {};

            std::string buildIR() override;

            void display() override;

            void addToTable(SymbolTable &table) override;

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

            void addToTable(SymbolTable &table) override;

            std::string buildIR() override;

        private:
            Expr::Expr *expr;
            AST::Bloc *bloc;
        };

        class While : public Instr {
        public:
            While(Expr::Expr *expr, AST::Bloc *bloc) :
                    expr(expr), bloc(bloc) {};

            void display() override;

            void addToTable(SymbolTable &table) override;

            std::string buildIR() override;

        private:
            Expr::Expr *expr;
            AST::Bloc *bloc;
        };
    }

    class Bloc {
    public:
        std::string buildIR();

        void pushInstr(Instr::Instr *instr);

        void addToTable(SymbolTable &st);

        void display();

    private:
        std::vector<Instr::Instr *> blocinstr;
    };

    class Prog {
    public:
        Prog(Bloc *bloc, Expr::Expr *returnValue) : bloc(bloc), returnValue(returnValue) {};

        std::string buildIR();

        bool create_symbol_table();
	
	std::vector<CFG*> generateIR();

        std::string getErrorMsg();

        void display();

    private:
        Bloc* bloc;
        Expr::Expr* returnValue;
        SymbolTable table;
    };
}

#endif //AST_AST_H
