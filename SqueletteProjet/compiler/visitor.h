
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include "AST/AST.h"

/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */

// The visitors will return nodes of the AST that will be used to build an AST while parsing the code
class Visitor : public ifccVisitor{
public:

    virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext* ctx) override{
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitProg(ifccParser::ProgContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::InitBloc* astInitBloc = visit(ctx->initbloc());
        AST::Bloc* astBloc = visit(ctx->bloc());
        // check if the eventual return in the main is not a void return
        astBloc->wrongReturnType(true);

        return new AST::Prog(astInitBloc, astBloc);
    }

    virtual antlrcpp::Any visitBlocinit(ifccParser::BlocinitContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::InitBloc* astInitBloc = new AST::InitBloc;
        for(auto& it : ctx->initfun()){// add all parsed instructions
            astInitBloc->pushInstr(visit(it));
        }

        return astInitBloc;
    }

    //INITFUN

    virtual antlrcpp::Any visitDeclproc(ifccParser::DeclprocContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper parts of the AST
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DeclProc* astDeclProc = new AST::InitInstr::DeclProc(procName, line, column);
        for(unsigned i = 0; i < ctx->type().size(); ++i){// add all parsed arguments
            astDeclProc->pushArg(ctx->type()[i]->getText(), ctx->NAME()[i + 1]->getText());
        }

        return (AST::InitInstr::InitInstr*) astDeclProc;
    }

    virtual antlrcpp::Any visitDeclfun(ifccParser::DeclfunContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper parts of the AST
        std::string returnType = ctx->type()[0]->getText();
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DeclFun* astDeclFun = new AST::InitInstr::DeclFun(returnType, procName, line, column);
        for(unsigned i = 1; i < ctx->type().size(); ++i){// add all parsed arguments
            astDeclFun->pushArg(ctx->type()[i]->getText(), ctx->NAME()[i]->getText());
        }

        return (AST::InitInstr::InitInstr*) astDeclFun;
    }

    virtual antlrcpp::Any visitDefproc(ifccParser::DefprocContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Bloc* astBloc = visit(ctx->bloc());
        astBloc->wrongReturnType(false);
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DefProc* astDefProc = new AST::InitInstr::DefProc(procName, astBloc, line, column);
        for(unsigned i = 0; i < ctx->type().size(); ++i){// add all parsed arguments
            astDefProc->pushArg(ctx->type()[i]->getText(), ctx->NAME()[i + 1]->getText());
        }

        return (AST::InitInstr::InitInstr*) astDefProc;
    }

    virtual antlrcpp::Any visitDeffun(ifccParser::DeffunContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper parts of the AST
        AST::Bloc* astBloc = visit(ctx->bloc());
        astBloc->wrongReturnType(true);
        std::string returnType = ctx->type()[0]->getText();
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DefFun* astDefFun = new AST::InitInstr::DefFun(returnType, procName, astBloc, line, column);
        for(unsigned i = 1; i < ctx->type().size(); ++i){
            astDefFun->pushArg(ctx->type()[i]->getText(), ctx->NAME()[i]->getText());
        }

        return (AST::InitInstr::InitInstr*) astDefFun;
    }

    //TYPE
    // these two visitors will never be called because the getText() method is enough
    // but we still need to make an implementation not to have an abstract class

    virtual antlrcpp::Any visitInt(ifccParser::IntContext* ctx) override{
        return nullptr;
    }

    virtual antlrcpp::Any visitChar(ifccParser::CharContext* ctx) override{
        return nullptr;
    }

    //BLOC

    virtual antlrcpp::Any visitBlocinstr(ifccParser::BlocinstrContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::Bloc* astBloc = new AST::Bloc();
        for(auto& it : ctx->instr()){
            AST::Instr::Instr* astInstr = visit(it);
            if(astInstr != nullptr){// sometimes, we will ignore some instructions (to ignore unreachable code)
                astBloc->pushInstr(astInstr);
            }
        }

        return astBloc;
    }

    //INSTR

    virtual antlrcpp::Any visitDeclint(ifccParser::DeclintContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclInt(names, line, column);
    }

    virtual antlrcpp::Any visitDeclchar(ifccParser::DeclcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclChar(names, line, column);
    }

    virtual antlrcpp::Any visitDeclinttab(ifccParser::DeclinttabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        if(astExpr->getType() != CONST){// the size of the tab has to be constant, can be improved later
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " array size must be a constant";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclIntTab(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitDeclchartab(ifccParser::DeclchartabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::DeclCharTab(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitDefint(ifccParser::DefintContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::DefInt(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitDefchar(ifccParser::DefcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::DefChar(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitAffexpr(ifccParser::AffexprContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitAfftab(ifccParser::AfftabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);

        return (AST::Instr::Instr*) new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column);
    }

    virtual antlrcpp::Any visitIfbloc(ifccParser::IfblocContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astBloc = visit(ctx->bloc());
        //optimization : ignore if statement if the code is unreachable
        if(astExpr->getType() == CONST && astExpr->getValue() == 0){
            return (AST::Instr::Instr*) nullptr;
        }
        //optimisation : replace if statement by a bloc if the code is always reached
        if(astExpr->getType() == CONST && astExpr->getValue() > 0){
            return (AST::Instr::Instr*) new AST::Instr::Bloci(astBloc);
        }

        return (AST::Instr::Instr*) new AST::Instr::If(astExpr, astBloc);
    }

    virtual antlrcpp::Any visitIfelsebloc(ifccParser::IfelseblocContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astIfBloc = visit(ctx->bloc()[0]);
        AST::Bloc* astElseBloc = visit(ctx->bloc()[1]);
        //optimization : ignore if statement if the code is unreachable
        if(astExpr->getType() == CONST && astExpr->getValue() == 0){
            return (AST::Instr::Instr*) new AST::Instr::Bloci(astElseBloc);
        }
        //optimization : ignore else statement if the code is unreachable
        if(astExpr->getType() == CONST && astExpr->getValue() > 0){
            return (AST::Instr::Instr*) new AST::Instr::Bloci(astIfBloc);
        }

        return (AST::Instr::Instr*) new AST::Instr::IfElse(astExpr, astIfBloc, astElseBloc);
    }

    virtual antlrcpp::Any visitWhilebloc(ifccParser::WhileblocContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astBloc = visit(ctx->bloc());
        //optimization : ignore while statement if the code is unreachable
        if(astExpr->getType() == CONST && astExpr->getValue() == 0){
            return (AST::Instr::Instr*) nullptr;
        }
        //warning : detection some endless loops, the ones with no reachable return in it
        if(astExpr->getType() == CONST && astExpr->getValue() > 0 && !astBloc->containsReturn()){
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " warning : endless loop";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        return (AST::Instr::Instr*) new AST::Instr::While(astExpr, astBloc);
    }

    virtual antlrcpp::Any visitInstrbloc(ifccParser::InstrblocContext* ctx) override{
        // recursive build of the deeper part of the AST
        AST::Bloc* astBloc = visit(ctx->bloc());
        return (AST::Instr::Instr*) new AST::Instr::Bloci(astBloc);
    }

    virtual antlrcpp::Any visitCallproc(ifccParser::CallprocContext* ctx) override{
        // build the node
        std::vector<std::string> args = std::vector<std::string>();
        for(unsigned i = 1; i < ctx->NAME().size(); ++i){
            args.push_back(ctx->NAME()[i]->getText());
        }

        return (AST::Instr::Instr*) new AST::Instr::CallProc(ctx->NAME()[0]->getText(), args);
    }

    virtual antlrcpp::Any visitPutchar(ifccParser::PutcharContext* ctx) override{
        // build the node
        return (AST::Instr::Instr*) new AST::Instr::Putchar(ctx->NAME()->getText());
    }

    virtual antlrcpp::Any visitReturn(ifccParser::ReturnContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        return (AST::Instr::Instr*) new AST::Instr::Return(line, column);
    }

    virtual antlrcpp::Any visitReturnexpr(ifccParser::ReturnexprContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::ReturnExpr(astExpr, line, column);
    }

    //FOR LOOP

    virtual antlrcpp::Any visitForbloc(ifccParser::ForblocContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // there is no for node in the AST
        // instead we build a while with an initialisation before
        // we will detail the construction of the code "for(initialization; bool; loopupdate){bloc}"
        AST::Bloc* astForBloc = new AST::Bloc();
        // 1. the initialization
        if(ctx->initfor() != nullptr){
            astForBloc->pushInstr(visit(ctx->initfor()));
        }
        // 2. the boolean that ends the loop
        AST::Expr::Expr* astExpr;
        if(ctx->expr() != nullptr){
            astExpr = visit(ctx->expr());
        }else{// if the boolean is not defined, it is true by default
            astExpr = new AST::Expr::Const(1);
        }
        // 3. the construction of the while bloc
        // 3.1 the instructions in the bloc
        AST::Bloc* astBloc = visit(ctx->bloc());
        // 3.2 the loop instructions
        for(auto& it : ctx->loopinstr()){
            astBloc->pushInstr(visit(it));
        }
        //optimization : ignore for statement if the code is unreachable
        if(astExpr->getType() == CONST && astExpr->getValue() == 0){
            return (AST::Instr::Instr*) nullptr;
        }
        //warning : detection some endless loops, the ones with no reachable return in it
        if(astExpr->getType() == CONST && astExpr->getValue() > 0 && !astBloc->containsReturn()){
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " warning : endless loop";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        AST::Instr::While* astWhile = new AST::Instr::While(astExpr, astBloc);
        astForBloc->pushInstr(astWhile);
        return (AST::Instr::Instr*) new AST::Instr::Bloci(astForBloc);
    }

    virtual antlrcpp::Any visitFordeclint(ifccParser::FordeclintContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclInt(names, line, column);
    }

    virtual antlrcpp::Any visitFordeclchar(ifccParser::FordeclcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }

        return (AST::Instr::Instr*) (new AST::Instr::DeclChar(names, line, column));
    }

    virtual antlrcpp::Any visitFordeclinttab(ifccParser::FordeclinttabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        if(astExpr->getType() != CONST){// the size of the tab has to be constant, can be improved later
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " array size must be a constant";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclIntTab(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitFordeclchartab(ifccParser::FordeclchartabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        if(astExpr->getType() != CONST){// the size of the tab has to be constant, can be improved later
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " array size must be a constant";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        return (AST::Instr::Instr*) new AST::Instr::DeclCharTab(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitFordefint(ifccParser::FordefintContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::DefInt(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitFordefchar(ifccParser::FordefcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::DefChar(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitForaffexpr(ifccParser::ForaffexprContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitForafftab(ifccParser::ForafftabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);

        return (AST::Instr::Instr*) new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column);
    }

    virtual antlrcpp::Any visitLoopaff(ifccParser::LoopaffContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());

        return (AST::Instr::Instr*) new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitLoopafftab(ifccParser::LoopafftabContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);

        return (AST::Instr::Instr*) (new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column));
    }

    //EXPRESSIONS

    virtual antlrcpp::Any visitPar(ifccParser::ParContext* ctx) override{
        return visit(ctx->expr());
    }

    virtual antlrcpp::Any visitMinus(ifccParser::MinusContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        // optimisation : constant propagation
        if(astExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(-astExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Minus(astExpr, line, column);
    }

    virtual antlrcpp::Any visitMult(ifccParser::MultContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() * astRightExpr->getValue());
        }
        //optimisation : neutrality of 1
        if(astLeftExpr->getType() == CONST && astLeftExpr->getValue() == 1){
            return astRightExpr;
        }
        if(astRightExpr->getType() == CONST && astRightExpr->getValue() == 1){
            return astLeftExpr;
        }
        //optimisation : 0 absorbing element
        if((astLeftExpr->getType() == CONST && astLeftExpr->getValue() == 0) ||
           (astRightExpr->getType() == CONST && astRightExpr->getValue() == 1)){
            return (AST::Expr::Expr*) new AST::Expr::Const(0);
        }
        // optimisation : constant propagation and associativity of *
        // all expression we get that are multiplications cant be the multiplication of two constants
        // to handle the associativity, we will always put the only possible constant on the right of a multiplication
        // we can do that because the multiplication between integers is commutative (the one on floats is not)
        // hence in the next blocs we have to merge the potential constants
        if(astLeftExpr->getType() == MULT && astLeftExpr->getRValue()->getType() == CONST){
            // first case, we have a multiplication on left with a constant to merge ...
            if(astRightExpr->getType() == CONST){// ... with a constant on right
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 * const2);
                return (AST::Expr::Expr*) new AST::Expr::Mult(astLeftExpr->getLValue(), astConst, line, column);
            }
            if(astRightExpr->getType() == MULT && astRightExpr->getRValue()->getType() == CONST){
                // ... with the other constant of a lvalue of another multiplication
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getRValue()->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 * const2);
                AST::Expr::Mult* astMult = new AST::Expr::Mult(astLeftExpr->getLValue(), astRightExpr->getLValue());
                return (AST::Expr::Expr*) new AST::Expr::Mult(astMult, astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Mult* astMult = new AST::Expr::Mult(astLeftExpr->getLValue(), astRightExpr);
            return (AST::Expr::Expr*) new AST::Expr::Mult(astMult, astLeftExpr->getRValue(), line, column);
        }
        if(astRightExpr->getType() == MULT && astRightExpr->getRValue()->getType() == CONST){
            // scond case we have a multiplication on the right with a constant to merge ...
            if(astLeftExpr->getType() == CONST){// ... with a constant on left
                int const1 = astRightExpr->getRValue()->getValue();
                int const2 = astLeftExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 * const2);
                return (AST::Expr::Expr*) new AST::Expr::Mult(astRightExpr->getLValue(), astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Mult* astMult = new AST::Expr::Mult(astRightExpr->getLValue(), astLeftExpr);
            return (AST::Expr::Expr*) new AST::Expr::Mult(astMult, astRightExpr->getRValue(), line, column);
        }
        // and in the case of a constant multiplied by anything else, we keep the constant on the right
        if(astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Mult(astRightExpr, astLeftExpr, line, column);
        }
        return (AST::Expr::Expr*) new AST::Expr::Mult(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitSub(ifccParser::SubContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        // optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() - astRightExpr->getValue());
        }
        // optimisation : neutrality of 0
        if(astLeftExpr->getType() == CONST && astLeftExpr->getValue() == 0){
            return (AST::Expr::Expr*) new AST::Expr::Minus(astRightExpr, line, column);
        }
        if(astRightExpr->getType() == CONST && astRightExpr->getValue() == 0){
            return astLeftExpr;
        }
        // optimisation : replace a-const by a+(-const)
        // will be useful in the constant propagation with the associativity of +
        if(astRightExpr->getType() == CONST){
            AST::Expr::Const* astConst = new AST::Expr::Const(- astRightExpr->getValue());
            return (AST::Expr::Expr*) new AST::Expr::Add(astLeftExpr, astConst, line, column);
        }

        return (AST::Expr::Expr*) new AST::Expr::Sub(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitAdd(ifccParser::AddContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() + astRightExpr->getValue());
        }
        //optimisation : neutrality of 0
        if(astLeftExpr->getType() == CONST && astLeftExpr->getValue() == 0){
            return astRightExpr;
        }
        if(astRightExpr->getType() == CONST && astRightExpr->getValue() == 0){
            return astLeftExpr;
        }
        // optimisation : constant propagation and associativity of +
        // all expression we get that are additions cant be the addition of two constants
        // to handle the associativity, we will always put the only possible constant on the right of an addition
        // we can do that because the addition between integers is commutative (the one on floats is not)
        // hence in the next blocs we have to merge the potential constants
        if(astLeftExpr->getType() == ADD && astLeftExpr->getRValue()->getType() == CONST){
            // first case, we have an addition on left with a constant to merge ...
            if(astRightExpr->getType() == CONST){// ... with a constant on right
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 + const2);
                return (AST::Expr::Expr*) new AST::Expr::Add(astLeftExpr->getLValue(), astConst, line, column);
            }
            if(astRightExpr->getType() == ADD && astRightExpr->getRValue()->getType() == CONST){
                // ... with the other constant of a lvalue of another addition
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getRValue()->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 + const2);
                AST::Expr::Add* astAdd = new AST::Expr::Add(astLeftExpr->getLValue(), astRightExpr->getLValue());
                return (AST::Expr::Expr*) new AST::Expr::Add(astAdd, astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Add* astAdd = new AST::Expr::Add(astLeftExpr->getLValue(), astRightExpr);
            return (AST::Expr::Expr*) new AST::Expr::Add(astAdd, astLeftExpr->getRValue(), line, column);
        }
        if(astRightExpr->getType() == ADD && astRightExpr->getRValue()->getType() == CONST){
            // scond case we have an addition on the right with a constant to merge ...
            if(astLeftExpr->getType() == CONST){// ... with a constant on left
                int const1 = astRightExpr->getRValue()->getValue();
                int const2 = astLeftExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 + const2);
                return (AST::Expr::Expr*) new AST::Expr::Add(astRightExpr->getLValue(), astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Add* astAdd = new AST::Expr::Add(astRightExpr->getLValue(), astLeftExpr);
            return (AST::Expr::Expr*) new AST::Expr::Add(astAdd, astRightExpr->getRValue(), line, column);
        }
        // and in the case of a constant added to anything else, we keep the constant on the right
        if(astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Add(astRightExpr, astLeftExpr, line, column);
        }
        return (AST::Expr::Expr*) new AST::Expr::Add(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNot(ifccParser::NotContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        //optimisation : constant propagation
        if(astExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(!astExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Not(astExpr, line, column);
    }

    virtual antlrcpp::Any visitEq(ifccParser::EqContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() == astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Eq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNeq(ifccParser::NeqContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        // optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() != astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Neq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLeq(ifccParser::LeqContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        // optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() <= astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Leq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeq(ifccParser::GeqContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() >= astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Geq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLow(ifccParser::LowContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() < astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Low(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeat(ifccParser::GeatContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() > astRightExpr->getValue());
        }

        return (AST::Expr::Expr*) new AST::Expr::Great(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitAnd(ifccParser::AndContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() & astRightExpr->getValue());
        }
        // optimisation : constant propagation and associativity of &
        // all expression we get that are bitwise and cant be the addition of two constants
        // to handle the associativity, we will always put the only possible constant on the right of a bitwise and
        // we can do that because the bitwise and is commutative
        // hence in the next blocs we have to merge the potential constants
        if(astLeftExpr->getType() == AND && astLeftExpr->getRValue()->getType() == CONST){
            // first case, we have a bitwise and on left with a constant to merge ...
            if(astRightExpr->getType() == CONST){// ... with a constant on right
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 & const2);
                return (AST::Expr::Expr*) new AST::Expr::And(astLeftExpr->getLValue(), astConst, line, column);
            }
            if(astRightExpr->getType() == AND && astRightExpr->getRValue()->getType() == CONST){
                // ... with the other constant of a lvalue of another bitwise and
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getRValue()->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 & const2);
                AST::Expr::And* astAnd = new AST::Expr::And(astLeftExpr->getLValue(), astRightExpr->getLValue());
                return (AST::Expr::Expr*) new AST::Expr::And(astAnd, astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::And* astAnd = new AST::Expr::And(astLeftExpr->getLValue(), astRightExpr);
            return (AST::Expr::Expr*) new AST::Expr::And(astAnd, astLeftExpr->getRValue(), line, column);
        }
        if(astRightExpr->getType() == AND && astRightExpr->getRValue()->getType() == CONST){
            // scond case we have a bitwise and on the right with a constant to merge ...
            if(astLeftExpr->getType() == CONST){// ... with a constant on left
                int const1 = astRightExpr->getRValue()->getValue();
                int const2 = astLeftExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 & const2);
                return (AST::Expr::Expr*) new AST::Expr::And(astRightExpr->getLValue(), astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::And* astAnd = new AST::Expr::And(astRightExpr->getLValue(), astLeftExpr);
            return (AST::Expr::Expr*) new AST::Expr::And(astAnd, astRightExpr->getRValue(), line, column);
        }
        // and in the case of a constant bitwise and anything else, we keep the constant on the right
        if(astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::And(astRightExpr, astLeftExpr, line, column);
        }
        return (AST::Expr::Expr*) new AST::Expr::And(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitXor(ifccParser::XorContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() ^ astRightExpr->getValue());
        }
        // optimisation : constant propagation and associativity of ^
        // all expression we get that are bitwise xor cant be the addition of two constants
        // to handle the associativity, we will always put the only possible constant on the right of a bitwise xor
        // we can do that because the bitwise xor is commutative
        // hence in the next blocs we have to merge the potential constants
        if(astLeftExpr->getType() == XOR && astLeftExpr->getRValue()->getType() == CONST){
            // first case, we have a bitwise xor on left with a constant to merge ...
            if(astRightExpr->getType() == CONST){// ... with a constant on right
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 ^ const2);
                return (AST::Expr::Expr*) new AST::Expr::Xor(astLeftExpr->getLValue(), astConst, line, column);
            }
            if(astRightExpr->getType() == XOR && astRightExpr->getRValue()->getType() == CONST){
                // ... with the other constant of a lvalue of another bitwise xor
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getRValue()->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 ^ const2);
                AST::Expr::Xor* astXor = new AST::Expr::Xor(astLeftExpr->getLValue(), astRightExpr->getLValue());
                return (AST::Expr::Expr*) new AST::Expr::Xor(astXor, astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Xor* astXor = new AST::Expr::Xor(astLeftExpr->getLValue(), astRightExpr);
            return (AST::Expr::Expr*) new AST::Expr::Xor(astXor, astLeftExpr->getRValue(), line, column);
        }
        if(astRightExpr->getType() == XOR && astRightExpr->getRValue()->getType() == CONST){
            // scond case we have a bitwise xor on the right with a constant to merge ...
            if(astLeftExpr->getType() == CONST){// ... with a constant on left
                int const1 = astRightExpr->getRValue()->getValue();
                int const2 = astLeftExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 ^ const2);
                return (AST::Expr::Expr*) new AST::Expr::Xor(astRightExpr->getLValue(), astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Xor* astXor = new AST::Expr::Xor(astRightExpr->getLValue(), astLeftExpr);
            return (AST::Expr::Expr*) new AST::Expr::Xor(astXor, astRightExpr->getRValue(), line, column);
        }
        // and in the case of a constant bitwise xor anything else, we keep the constant on the right
        if(astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Xor(astRightExpr, astLeftExpr, line, column);
        }
        return (AST::Expr::Expr*) new AST::Expr::Xor(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitOr(ifccParser::OrContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->getType() == CONST && astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Const(astLeftExpr->getValue() | astRightExpr->getValue());
        }
        //optimisation : neutrality of 0
        if(astLeftExpr->getType() == CONST && astLeftExpr->getValue() == 0){
            return astRightExpr;
        }
        if(astRightExpr->getType() == CONST && astRightExpr->getValue() == 0){
            return astLeftExpr;
        }
        // optimisation : constant propagation and associativity of |
        // all expression we get that are bitwise or cant be the addition of two constants
        // to handle the associativity, we will always put the only possible constant on the right of a bitwise or
        // we can do that because the bitwise or is commutative
        // hence in the next blocs we have to merge the potential constants
        if(astLeftExpr->getType() == OR && astLeftExpr->getRValue()->getType() == CONST){
            // first case, we have a bitwise or on left with a constant to merge ...
            if(astRightExpr->getType() == CONST){// ... with a constant on right
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 | const2);
                return (AST::Expr::Expr*) new AST::Expr::Or(astLeftExpr->getLValue(), astConst, line, column);
            }
            if(astRightExpr->getType() == OR && astRightExpr->getRValue()->getType() == CONST){
                // ... with the other constant of a lvalue of another bitwise or
                int const1 = astLeftExpr->getRValue()->getValue();
                int const2 = astRightExpr->getRValue()->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 | const2);
                AST::Expr::Or* astOr = new AST::Expr::Or(astLeftExpr->getLValue(), astRightExpr->getLValue());
                return (AST::Expr::Expr*) new AST::Expr::Or(astOr, astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Or* astOr = new AST::Expr::Or(astLeftExpr->getLValue(), astRightExpr);
            return (AST::Expr::Expr*) new AST::Expr::Or(astOr, astLeftExpr->getRValue(), line, column);
        }
        if(astRightExpr->getType() == OR && astRightExpr->getRValue()->getType() == CONST){
            // scond case we have a bitwise or on the right with a constant to merge ...
            if(astLeftExpr->getType() == CONST){// ... with a constant on left
                int const1 = astRightExpr->getRValue()->getValue();
                int const2 = astLeftExpr->getValue();
                AST::Expr::Const* astConst = new AST::Expr::Const(const1 | const2);
                return (AST::Expr::Expr*) new AST::Expr::Or(astRightExpr->getLValue(), astConst, line, column);
            }
            // ... with nothing, hence we keep the constant on the right
            AST::Expr::Or* astOr = new AST::Expr::Or(astRightExpr->getLValue(), astLeftExpr);
            return (AST::Expr::Expr*) new AST::Expr::Or(astOr, astRightExpr->getRValue(), line, column);
        }
        // and in the case of a constant bitwise or anything else, we keep the constant on the right
        if(astLeftExpr->getType() == CONST){
            return (AST::Expr::Expr*) new AST::Expr::Or(astRightExpr, astLeftExpr, line, column);
        }
        return (AST::Expr::Expr*) new AST::Expr::Or(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitCallfun(ifccParser::CallfunContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // build the node
        std::vector<std::string> args = std::vector<std::string>();
        for(unsigned i = 1; i < ctx->NAME().size(); ++i){
            args.push_back(ctx->NAME()[i]->getText());
        }

        return (AST::Expr::Expr*) new AST::Expr::CallFun(ctx->NAME()[0]->getText(), args, line, column);
    }

    virtual antlrcpp::Any visitGetchar(ifccParser::GetcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();

        return (AST::Expr::Expr*) new AST::Expr::GetChar(line, column);
    }

    virtual antlrcpp::Any visitConst(ifccParser::ConstContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();

        return (AST::Expr::Expr*) new AST::Expr::Const(std::stoi(ctx->CONST()->getText()), line, column);
    }

    virtual antlrcpp::Any visitConstchar(ifccParser::ConstcharContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();

        return (AST::Expr::Expr*) new AST::Expr::ConstChar(ctx->CONSTCHAR()->getText()[1], line, column);
    }

    virtual antlrcpp::Any visitName(ifccParser::NameContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();

        return (AST::Expr::Expr*) new AST::Expr::Name(ctx->NAME()->getText(), line, column);
    }

    virtual antlrcpp::Any visitTabaccess(ifccParser::TabaccessContext* ctx) override{
        // get the position in the code
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        // recursive build of the deeper part of the AST
        AST::Expr::Expr* astIndex = visit(ctx->expr());

        return (AST::Expr::Expr*) new AST::Expr::TabAccess(ctx->NAME()->getText(), astIndex, line, column);
    }
};

