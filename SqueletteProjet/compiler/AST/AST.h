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
            Add(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Sub: public Expr{
        public:
            Sub(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Mult: public Expr{
        public:
            Mult(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Minus: public Expr{
        public:
            Minus(Expr* value): value(value){};
            std::string makeAssembly() override;
        private:
            Expr* value;
        };

//        class Par: public Expr{
//        public:
//            Par(Expr* value): value(value){};
//            std::string makeAssembly() override;
//        private:
//            Expr* value;
//        };

        class Const: public Expr{
        public:
            Const(int value) : value(value){};
            std::string makeAssembly() override;
        private:
            int value;
        };

        class Name: public Expr{
        public:
            Name(std::string name): name(name){};
            std::string makeAssembly() override;
        private:
            std::string name;
        };
    }


    namespace Instr{
        class Instr{
        public:
            //virtual std::string makeAssembly(SymbolTable st);
        };

        class Decl: public Instr{
        public:
            Decl(std::vector<std::string> names): names(names){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::vector<std::string> names;
        };


        class Def: public Instr{
        public:
            Def(std::string name, Expr::Expr* expr): name(name), expr(expr){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::string name;
            Expr::Expr* expr;
        };

        class Affct: public Instr{
        public:
            Affct(std::string name, Expr::Expr* expr): name(name), expr(expr){};
            //std::string makeAssembly(SymbolTable st) override;
        private:
            std::string name;
            Expr::Expr* expr;
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
