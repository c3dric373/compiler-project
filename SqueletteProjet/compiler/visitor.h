
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
    return new AST::Prog(astInitBloc, astBloc);
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
        AST::Instr::Instr* astInstr = visit(it);
        if(astInstr != nullptr){
            astBloc->pushInstr(astInstr);
    }
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

    virtual antlrcpp::Any visitDeclinttab(ifccParser::DeclinttabContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
      AST::Expr::Expr* astExpr = visit(ctx->expr());
      if(!astExpr->isConst()){
          std::string errorMessage =
                  "line" + std::to_string(line) + ':' + std::to_string(column)
                  + " array size must be a constant";
          std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
      }
        return (AST::Instr::Instr*)(new AST::Instr::DeclIntTab(ctx->NAME()->getText(), astExpr, line, column));
    }

    virtual antlrcpp::Any visitDeclchartab(ifccParser::DeclchartabContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclCharTab(ctx->NAME()->getText(), astExpr, line, column));
    }

  virtual antlrcpp::Any visitAffexpr(ifccParser::AffexprContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column));
  }

    virtual antlrcpp::Any visitAfftab(ifccParser::AfftabContext *ctx) override {
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column));
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
      //optimization : unreachable code
      if(astExpr->isConst() && astExpr->getValue() == 0){
          return (AST::Instr::Instr*)nullptr;
      }
      //optimisation : always reached code
      if(astExpr->isConst() && astExpr->getValue() > 0){
          return (AST::Instr::Instr*)new AST::Instr::Bloci(astBloc);
      }

      return (AST::Instr::Instr*)new AST::Instr::If(astExpr, astBloc);
  }

    virtual antlrcpp::Any visitIfelsebloc(ifccParser::IfelseblocContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astIfBloc = visit(ctx->bloc()[0]);
        AST::Bloc* astElseBloc = visit(ctx->bloc()[1]);
        //optimization : unreachable code
        if(astExpr->isConst() && astExpr->getValue() == 0){
            return (AST::Instr::Instr*)new AST::Instr::Bloci(astElseBloc);
        }
        if(astExpr->isConst() && astExpr->getValue() > 0){
            return (AST::Instr::Instr*)new AST::Instr::Bloci(astIfBloc);
        }

        return (AST::Instr::Instr*)(new AST::Instr::IfElse(astExpr, astIfBloc, astElseBloc));
    }

    virtual antlrcpp::Any visitWhilebloc(ifccParser::WhileblocContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        AST::Bloc* astBloc = visit(ctx->bloc());
        //optimization : unreachable code
        if(astExpr->isConst() && astExpr->getValue() == 0){
            return (AST::Instr::Instr*)nullptr;
        }
        //optimization : detection of an endless loop
        if(astExpr->isConst() && astExpr->getValue() > 0 && !astBloc->containsReturn()){
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " warning : endless loop";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
        }

        return (AST::Instr::Instr*)(new AST::Instr::While(astExpr, astBloc));
    }

    virtual antlrcpp::Any visitCallproc(ifccParser::CallprocContext *ctx) override {
        std::vector<std::string> args = std::vector<std::string>();
        for(unsigned i = 1; i < ctx->NAME().size(); ++i){
            args.push_back(ctx->NAME()[i]->getText());
        }
        return (AST::Instr::Instr*)new AST::Instr::CallProc(ctx->NAME()[0]->getText(), args);
    }

    virtual antlrcpp::Any visitPutchar(ifccParser::PutcharContext *ctx) override {
        return (AST::Instr::Instr*)new AST::Instr::Putchar(ctx->NAME()->getText());
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
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
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
        //optimization : unreachable code
        if(astExpr->isConst() && astExpr->getValue() == 0){
            return (AST::Instr::Instr*)nullptr;
        }
        //optimization : detection of an endless loop
        if(astExpr->isConst() && astExpr->getValue() > 0 && !astBloc->containsReturn()){
            std::string errorMessage =
                    "line" + std::to_string(line) + ':' + std::to_string(column)
                    + " warning : endless loop";
            std::cout << "\033[;31m" + errorMessage + "\033[0m" << std::endl;
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

    virtual antlrcpp::Any visitFordeclinttab(ifccParser::FordeclinttabContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclIntTab(ctx->NAME()->getText(), astExpr, line, column));
    }

    virtual antlrcpp::Any visitFordeclchartab(ifccParser::FordeclchartabContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::DeclCharTab(ctx->NAME()->getText(), astExpr, line, column));
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

    virtual antlrcpp::Any visitForafftab(ifccParser::ForafftabContext *ctx) override {
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column));
    }

    virtual antlrcpp::Any visitLoopaff(ifccParser::LoopaffContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column);
    }

    virtual antlrcpp::Any visitLoopafftab(ifccParser::LoopafftabContext *ctx) override {
        AST::Expr::Expr* astIndex = visit(ctx->expr()[0]);
        AST::Expr::Expr* astExpr = visit(ctx->expr()[1]);
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Instr::Instr*)(new AST::Instr::AffctTab(ctx->NAME()->getText(), astIndex, astExpr, line, column));
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
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
    //optimisation : constant propagation
    if(astRightExpr->isConst() && astLeftExpr->isConst()){
        return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() + astRightExpr->getValue());
    }
    //optimisation : neutrality of 0
    if(astLeftExpr->isConst() && astLeftExpr->getValue() == 0){
        return astRightExpr;
    }
    if(astRightExpr->isConst() && astRightExpr->getValue() == 0){
        return astLeftExpr;
    }

    return (AST::Expr::Expr*)new AST::Expr::Add(astLeftExpr, astRightExpr, line, column);
    }

  virtual antlrcpp::Any visitSub(ifccParser::SubContext *ctx) override {
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
      AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
      AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      //optimisation : constant propagation
      if(astRightExpr->isConst() && astLeftExpr->isConst()){
          return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() - astRightExpr->getValue());
      }
      //optimisation : neutrality of 0
      if(astLeftExpr->isConst() && astLeftExpr->getValue() == 0){
          return (AST::Expr::Expr*)new AST::Expr::Minus(astRightExpr, line, column);
      }
      if(astRightExpr->isConst() && astRightExpr->getValue() == 0){
          return astLeftExpr;
      }

    return (AST::Expr::Expr*)new AST::Expr::Sub(astLeftExpr, astRightExpr, line, column);
  }

  virtual antlrcpp::Any visitMinus(ifccParser::MinusContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
      //optimisation : constant propagation
      if(astExpr->isConst()){
          return (AST::Expr::Expr*)new AST::Expr::Const(- astExpr->getValue());
      }

    return (AST::Expr::Expr*)new AST::Expr::Minus(astExpr, line, column);
  }

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override {
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
      AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
      AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
      //optimisation : constant propagation
      if(astRightExpr->isConst() && astLeftExpr->isConst()){
          return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() * astRightExpr->getValue());
      }
      //optimisation : neutrality of 1
      if(astLeftExpr->isConst() && astLeftExpr->getValue() == 1){
          return astRightExpr;
      }
      if(astRightExpr->isConst() && astRightExpr->getValue() == 1){
          return astLeftExpr;
      }
      //optimisation : absorbance de 0
      if((astLeftExpr->isConst() && astLeftExpr->getValue() == 0) ||
              (astRightExpr->isConst() && astRightExpr->getValue() == 1)){
          return (AST::Expr::Expr*)new AST::Expr::Const(0);
      }

      return (AST::Expr::Expr*)new AST::Expr::Mult(astLeftExpr, astRightExpr, line, column);
  }

    virtual antlrcpp::Any visitAnd(ifccParser::AndContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() & astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::And(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitOr(ifccParser::OrContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() | astRightExpr->getValue());
        }
        //optimisation : neutrality of 0
        if(astLeftExpr->isConst() && astLeftExpr->getValue() == 0){
            return astRightExpr;
        }
        if(astRightExpr->isConst() && astRightExpr->getValue() == 0){
            return astLeftExpr;
        }

        return (AST::Expr::Expr*)new AST::Expr::Or(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitXor(ifccParser::XorContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() ^ astRightExpr->getValue());
        }

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

    virtual antlrcpp::Any visitTabaccess(ifccParser::TabaccessContext *ctx) override {
      AST::Expr::Expr* astIndex = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::TabAccess(ctx->NAME()->getText(), astIndex, line, column);
    }

    virtual antlrcpp::Any visitCallfun(ifccParser::CallfunContext *ctx) override {
        std::vector<std::string> args = std::vector<std::string>();
        for(unsigned i = 1; i < ctx->NAME().size(); ++i){
            args.push_back(ctx->NAME()[i]->getText());
        }
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::CallFun(ctx->NAME()[0]->getText(), args, line, column);
    }

    virtual antlrcpp::Any visitGetchar(ifccParser::GetcharContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        return (AST::Expr::Expr*)new AST::Expr::GetChar(line, column);
    }

  //COMPARAISONS ET BOOLEENS

    virtual antlrcpp::Any visitEq(ifccParser::EqContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() == astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Eq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNeq(ifccParser::NeqContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() != astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Neq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLeq(ifccParser::LeqContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() <= astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Leq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitLow(ifccParser::LowContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() < astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Low(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeq(ifccParser::GeqContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() >= astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Geq(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitGeat(ifccParser::GeatContext *ctx) override {
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
        AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
        //optimisation : constant propagation
        if(astRightExpr->isConst() && astLeftExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(astLeftExpr->getValue() > astRightExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Great(astLeftExpr, astRightExpr, line, column);
    }

    virtual antlrcpp::Any visitNot(ifccParser::NotContext *ctx) override {
        AST::Expr::Expr* astExpr = visit(ctx->expr());
        unsigned line = ctx->getStart()->getLine();
        unsigned column = ctx->getStart()->getCharPositionInLine();
        //optimisation : constant propagation
        if(astExpr->isConst()){
            return (AST::Expr::Expr*)new AST::Expr::Const(! astExpr->getValue());
        }

        return (AST::Expr::Expr*)new AST::Expr::Not(astExpr, line, column);
    }
};

