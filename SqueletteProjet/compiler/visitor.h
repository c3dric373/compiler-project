
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
    AST::Bloc* astBloc = visit(ctx->bloc());
    AST::Expr::Expr* astExpr = visit(ctx->expr());
    return new AST::Prog(astBloc, astExpr);
  }

  virtual antlrcpp::Any visitBlocinstr(ifccParser::BlocinstrContext *ctx) override {
    AST::Bloc* astBloc = new AST::Bloc();
    for(auto& it : ctx->instr()){
      astBloc->pushInstr(visit(it));
    }
    return astBloc;
  }

  //INSTRUCTIONS

  virtual antlrcpp::Any visitInstrdecl(ifccParser::InstrdeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstrdef(ifccParser::InstrdefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstraffct(ifccParser::InstraffctContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInstrif(ifccParser::InstrifContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclint(ifccParser::DeclintContext *ctx) override {
    auto names = std::vector<std::string>();
    for(auto& it : ctx->NAME()){
      names.push_back(it->getText());
    }
    unsigned line = ctx->getStart()->getLine();
    unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::Decl(names, line, column));
  }

  virtual antlrcpp::Any visitAffexpr(ifccParser::AffexprContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::Affct(ctx->NAME()->getText(), astExpr, line, column));
  }

  virtual antlrcpp::Any visitDefexpr(ifccParser::DefexprContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Instr::Instr*)(new AST::Instr::Def(ctx->NAME()->getText(), astExpr, line, column));
  }

  virtual antlrcpp::Any visitIfbloc(ifccParser::IfblocContext *ctx) override {
      AST::Expr::Expr* astExpr = visit(ctx->expr());
      AST::Bloc* astBloc = visit(ctx->bloc());
      return (AST::Instr::Instr*)(new AST::Instr::If(astExpr, astBloc));
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

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
      unsigned line = ctx->getStart()->getLine();
      unsigned column = ctx->getStart()->getCharPositionInLine();
    return (AST::Expr::Expr*)new AST::Expr::Const(std::stoi(ctx->CONST()->getText()), line, column);
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

