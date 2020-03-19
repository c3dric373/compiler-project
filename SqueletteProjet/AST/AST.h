#ifndef AST_AST_H
#define AST_AST_H

#include <iostream>

namespace AST{
    namespace Expr{
        class Expr{
        public:
            virtual std::string makeAssembly();
        private:
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
            Name(std::string& name): name(name){}
            std::string makeAssembly() override;
        private:
            std::string name;
        };
    }

    class Def{
    public:
        Def(std::string& name, Expr::Expr* expr): name(name), expr(expr){};
        std::string makeAssembly();
    private:
        std::string name;
        Expr::Expr* expr;
    };

    class Bloc{
    public:
        Bloc(Def* def, Bloc* bloc): def(def), bloc(bloc){};
        std::string makeAssembly();
    private:
        Def* def;
        Bloc* bloc;
    };

    class Prog{
    public:
        Prog(Bloc* bloc, Expr::Expr* returnValue): bloc(bloc), returnValue(returnValue){};
        std::string makeAssembly();
    private:
        Bloc* bloc;
        Expr::Expr* returnValue;
    };
}



#endif //AST_AST_H
