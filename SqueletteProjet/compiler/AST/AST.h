#ifndef AST_AST_H
#define AST_AST_H

#include <iostream>
#include <vector>
#include "SymbolTable.h"
namespace AST{

    namespace Expr{
        class Expr{
        public:
            virtual int getValeur()=0;
            virtual std::string makeAssembly()=0;
        private:
        };

        class Add: public Expr{
       public:
            Add(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
            int getValeur();
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Sub: public Expr{
        public:
            Sub(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
            int getValeur() override;
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Mult: public Expr{
        public:
            Mult(Expr* lValue, Expr* rValue): lValue(lValue), rValue(rValue){};
            std::string makeAssembly() override;
            int getValeur() override;
        private:
            Expr* lValue;
            Expr* rValue;
        };

        class Minus: public Expr{
        public:
            Minus(Expr* value): value(value){};
            std::string makeAssembly() override;
            int getValeur() override;
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
            int getValeur() override;
        private:
            int value;
        };

        class Name: public Expr{
        public:
            Name(std::string name): name(name){}
            std::string makeAssembly() override;
            int getValeur() override;
        private:
            std::string name;
        };
    }

    class Def{
    public:
        Def(std::string name, Expr::Expr* expr): name(name), expr(expr){};
        std::string makeAssembly(SymbolTable st);
        void addToTable(SymbolTable table);
    private:
        std::string name;
        Expr::Expr* expr;
    };

    class Bloc{
    public:
        std::string makeAssembly();
        void pushDef(Def* def);
        void addToTable(SymbolTable table);
    private:
        std::vector<Def*> defs;
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
