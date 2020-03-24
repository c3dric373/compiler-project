#ifndef AST_AST_H
#define AST_AST_H

#include <iostream>
#include <vector>
#include "SymbolTable.h"
namespace AST{

    namespace Expr{
        class Expr{
        public:
            virtual std::string makeAssembly();
            //virtual int getValeur();
        };

        class Add: public Expr{
       public:
            Add(Expr* lValue, Expr* rValue, unsigned line, unsigned column):
            lValue(lValue), rValue(rValue), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Sub: public Expr{
        public:
            Sub(Expr* lValue, Expr* rValue, unsigned line, unsigned column):
            lValue(lValue), rValue(rValue), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Mult: public Expr{
        public:
            Mult(Expr* lValue, Expr* rValue, unsigned line, unsigned column):
            lValue(lValue), rValue(rValue), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Minus: public Expr{
        public:
            Minus(Expr* value, unsigned line, unsigned column):
            value(value), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            Expr* value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Const: public Expr{
        public:
            Const(int value, unsigned line, unsigned column):
            value(value), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            int value;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Name: public Expr{
        public:
            Name(std::string name, unsigned line, unsigned column):
            name(name), line(line), column(column){};
            std::string makeAssembly() override;
        private:
            std::string name;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };
    }


    namespace Instr{
        class Instr{
        public:
            //virtual std::string makeAssembly(SymbolTable st);
        };

        class Decl: public Instr{
        public:
            Decl(std::vector<std::string> names, unsigned line, unsigned column):
            names(names), line(line), column(column){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::vector<std::string> names;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };


        class Def: public Instr{
        public:
            Def(std::string name, Expr::Expr* expr, unsigned line, unsigned column):
            name(name), expr(expr), line(line), column(column){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::string name;
            Expr::Expr* expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };

        class Affct: public Instr{
        public:
            Affct(std::string name, Expr::Expr* expr, unsigned line, unsigned column):
            name(name), expr(expr), line(line), column(column){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::string name;
            Expr::Expr* expr;
            unsigned line; // the line of the expression
            unsigned column; // even more: the column in this line
        };
    }

    class Bloc{
    public:
        std::string makeAssembly();
        void pushInstr(Instr::Instr* instr);
        void addToTable(SymbolTable st);
    private:
        std::vector<Instr::Instr*> blocinstr;
    };

    class Prog{
    public:
        Prog(Bloc* bloc, Expr::Expr* returnValue): bloc(bloc), returnValue(returnValue){};
        std::string makeAssembly();
        void create_symbol_table();
    private:
        Bloc* bloc;
        Expr::Expr* returnValue;
        SymbolTable table; 
    };
}

#endif //AST_AST_H
