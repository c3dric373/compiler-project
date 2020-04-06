
// Generated from ifcc.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "antlr4-generated/ifccVisitor.h"
#include "AST/AST.h"


/**
 * This class provides an empty implementation of ifccVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Visitor : public ifccVisitor {
public:

  virtual antlrcpp::Any visitAxiom(ifccParser::AxiomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    AST::InitBloc* astInitBloc = visit(ctx->initbloc());
    AST::Bloc* astBloc = visit(ctx->bloc());
    astBloc->wrongReturnType(true);
    AST::Expr::Expr* astExpr = visit(ctx->expr());
    return new AST::Prog(astInitBloc, astBloc, astExpr);
  }

    virtual antlrcpp::Any visitBlocinit(ifccParser::BlocinitContext *ctx) override {
      AST::InitBloc* astInitBloc = new AST::InitBloc;
      for(auto& it : ctx->initfun()){
          astInitBloc->pushInstr(visit(it));
      }
      return astInitBloc;
    }

  virtual antlrcpp::Any visitBlocinstr(ifccParser::BlocinstrContext *ctx) override {
    AST::Bloc* astBloc = new AST::Bloc();
    for(auto& it : ctx->instr()){
      astBloc->pushInstr(visit(it));
    }
    return astBloc;
  }

  //INSTRUCTIONS

    virtual antlrcpp::Any visitInstrbloc(ifccParser::InstrblocContext *ctx) override {
        AST::Bloc* astBloc = visit(ctx->bloc());
        return (AST::Instr::Instr*)(new AST::Instr::Bloci(astBloc));
    }

  virtual antlrcpp::Any visitDeclint(ifccParser::DeclintContext *ctx) override {
    auto names = std::vector<std::string>();
    for(auto& it : ctx->NAME()){
      names.push_back(it->getText());
    }
    unsigned line = ctx->getStart()->getLine();
    unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::DeclInt(names, line, column));
  }

    virtual antlrcpp::Any visitDeclchar(ifccParser::DeclcharContext *ctx) override {
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclChar(names, line, column));
    }

  virtual antlrcpp::Any visitAffexpr(ifccParser::AffexprContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column));
  }

  virtual antlrcpp::Any visitDefint(ifccParser::DefintContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::DefInt(ctx->NAME()->getText(), astExpr, line, column));
  }

    virtual antlrcpp::Any visitDefchar(ifccParser::DefcharContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DefChar(ctx->NAME()->getText(), astExpr, line, column));
    }

  virtual antlrcpp::Any visitIfbloc(ifccParser::IfblocContext *ctx) override {
      AST::Expr::Expr* astExpr = visit(ctx->expr());
      AST::Bloc* astBloc = visit(ctx->bloc());
      return (AST::Instr::Instr*)(new AST::Instr::If(astExpr, astBloc));
  }

    virtual antlrcpp::Any visitIfelsebloc(ifccParser::IfelseblocContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astIfBloc = visit(ctx->bloc()[0]);
        AST::Bloc* astElseBloc = visit(ctx->bloc()[1]);
        return (AST::Instr::Instr*)(new AST::Instr::IfElse(astExpr, astIfBloc, astElseBloc));
    }

    virtual antlrcpp::Any visitWhilebloc(ifccParser::WhileblocContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astBloc = visit(ctx->bloc());
        return (AST::Instr::Instr*)(new AST::Instr::While(astExpr, astBloc));
    }

    virtual antlrcpp::Any visitCallproc(ifccParser::CallprocContext *ctx) override {
        std::vector<std::string> args = std::vector<std::string>();
        for(unsigned i = 1; i < ctx->NAME().size(); ++i){
            args[i - 1] = ctx->NAME()[i]->getText();
        }
        return (AST::Instr::Instr*)new AST::Instr::CallProc(ctx->NAME()[0]->getText(), args);
    }

    virtual antlrcpp::Any visitReturn(ifccParser::ReturnContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)new AST::Instr::Return(line, column);
    }

    virtual antlrcpp::Any visitReturnexpr(ifccParser::ReturnexprContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        return (AST::Instr::Instr*)new AST::Instr::ReturnExpr(astExpr, line, column);
    }

    //FOR LOOP

    virtual antlrcpp::Any visitForbloc(ifccParser::ForblocContext *ctx) override {
        AST::Bloc* astForBloc = new AST::Bloc();
        if(ctx->initfor() != nullptr){
            astForBloc->pushInstr(visit(ctx->initfor()));
        }
        AST::Expr::Expr* astExpr;
        if(ctx->expr() != nullptr){
            astExpr = visit(ctx->expr());
        }else{
            astExpr = new AST::Expr::Const(1);
        }
        AST::Bloc* astBloc = visit(ctx->bloc());
        for(auto& it : ctx->loopinstr()){
            astBloc->pushInstr(visit(it));
        }
        AST::Instr::While* astWhile = new AST::Instr::While(astExpr, astBloc);
        astForBloc->pushInstr(astWhile);
        return (AST::Instr::Instr*)new AST::Instr::Bloci(astForBloc);
    }

    virtual antlrcpp::Any visitFordeclint(ifccParser::FordeclintContext *ctx) override {
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclInt(names, line, column));
    }

    virtual antlrcpp::Any visitFordeclchar(ifccParser::FordeclcharContext *ctx) override {
        auto names = std::vector<std::string>();
        for(auto& it : ctx->NAME()){
            names.push_back(it->getText());
        }
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclChar(names, line, column));
    }

    virtual antlrcpp::Any visitFordefint(ifccParser::FordefintContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DefInt(ctx->NAME()->getText(), astExpr, line, column));
    }

    virtual antlrcpp::Any visitFordefchar(ifccParser::FordefcharContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DefChar(ctx->NAME()->getText(), astExpr, line, column));
    }

    virtual antlrcpp::Any visitForaffexpr(ifccParser::ForaffexprContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column));
    }

    virtual antlrcpp::Any visitForaff(ifccParser::ForaffContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column);
    }

    //INIT FUNCTIONS

    virtual antlrcpp::Any visitDeclproc(ifccParser::DeclprocContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DeclProc* astDeclProc = new AST::InitInstr::DeclProc(procName, line, column);
        for(unsigned i = 0; i < ctx->type().size(); ++i){
            astDeclProc->pushArg(visit(ctx->type()[i]), ctx->NAME()[i + 1]->getText());
        }
        return (AST::InitInstr::InitInstr*)astDeclProc;
    }

    virtual antlrcpp::Any visitDeclfun(ifccParser::DeclfunContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        std::string returnType = ctx->type()[0]->getText();
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DeclFun* astDeclFun = new AST::InitInstr::DeclFun(returnType, procName, line, column);
        for(unsigned i = 1; i < ctx->type().size(); ++i){
            astDeclFun->pushArg(visit(ctx->type()[i]), ctx->NAME()[i]->getText());
        }
        return (AST::InitInstr::InitInstr*)astDeclFun;
    }

    virtual antlrcpp::Any visitDefproc(ifccParser::DefprocContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Bloc* astBloc = visit(ctx->bloc());
        astBloc->wrongReturnType(false);
        std::string procName = ctx->NAME()[0]->getText();
      AST::InitInstr::DefProc* astDefProc = new AST::InitInstr::DefProc(procName, astBloc, line, column);
      for(unsigned i = 0; i < ctx->type().size(); ++i){
          astDefProc->pushArg(visit(ctx->type()[i]), ctx->NAME()[i + 1]->getText());
      }
      return (AST::InitInstr::InitInstr*)astDefProc;
    }

    virtual antlrcpp::Any visitDeffun(ifccParser::DeffunContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Bloc* astBloc = visit(ctx->bloc());
        astBloc->wrongReturnType(true);
        std::string returnType = ctx->type()[0]->getText();
        std::string procName = ctx->NAME()[0]->getText();
        AST::InitInstr::DefFun* astDefFun = new AST::InitInstr::DefFun(returnType, procName, astBloc, line, column);
        for(unsigned i = 1; i < ctx->type().size(); ++i){
            astDefFun->pushArg(visit(ctx->type()[i]), ctx->NAME()[i]->getText());
        }
        return (AST::InitInstr::InitInstr*)astDefFun;
    }

    virtual antlrcpp::Any visitInt(ifccParser::IntContext *ctx) override {
        return std::string("int");
    }

    virtual antlrcpp::Any visitChar(ifccParser::CharContext *ctx) override {
        return std::string("char");
    }

  //EXPRESSIONS

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Add(astLeftExpr, astRightExpr, line, column);
  }

  virtual antlrcpp::Any visitSub(ifccParser::SubContext *ctx) override {
      AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Sub(astLeftExpr, astRightExpr, line, column);
  }

  virtual antlrcpp::Any visitMinus(ifccParser::MinusContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Minus(astExpr, line, column);
  }

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Mult(astLeftExpr, astRightExpr, line, column);
  }

    virtual antlrcpp::Any visitAnd(ifccParser::AndContext *ctx) override {
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::And(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitOr(ifccParser::OrContext *ctx) override {
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::Or(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitXor(ifccParser::XorContext *ctx) override {
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::Xor(astLeftExpr, astRightExpr, line, column);
    }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Const(std::stoi(ctx->CONST()->getText()), line, column);
  }

    virtual antlrcpp::Any visitConstchar(ifccParser::ConstcharContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::ConstChar(ctx->CONSTCHAR()->getText()[1], line, column);
    }

  virtual antlrcpp::Any visitName(ifccParser::NameContext *ctx) override {
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Name(ctx->NAME()->getText(), line, column);
  }

  //COMPARAISONS ET BOOLEENS

    virtual antlrcpp::Any visitEq(ifccParser::EqContext *ctx) override {
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::Eq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNeq(ifccParser::NeqContext *ctx) override {
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::Neq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLeq(ifccParser::LeqContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Leq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLow(ifccParser::LowContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Low(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeq(ifccParser::GeqContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Geq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeat(ifccParser::GeatContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Great(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNot(ifccParser::NotContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::Not(astExpr, line, column);
    }
};

