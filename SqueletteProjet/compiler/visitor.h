
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
    return (AST::Prog*)visit(ctx->prog());
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    AST::Bloc* astBloc = visit(ctx->bloc());
    AST::Expr::Expr* astExpr = visit(ctx->expr());
    return new AST::Prog(astBloc, astExpr);
  }

  virtual antlrcpp::Any visitBloc(ifccParser::BlocContext *ctx) override {
    AST::Bloc* astBloc = new AST::Bloc();
    for(auto& it : ctx->def()){
      astBloc->pushDef(visit(it));
    }
    return astBloc;
  }

  virtual antlrcpp::Any visitDefexpr(ifccParser::DefexprContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
    return new AST::Def(ctx->NAME()->getText(), astExpr);
  }

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
    return (AST::Expr::Expr*)new AST::Expr::Add(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitSub(ifccParser::SubContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
    return (AST::Expr::Expr*)new AST::Expr::Sub(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitMinus(ifccParser::MinusContext *ctx) override {
    AST::Expr::Expr* astExpr = visit(ctx->expr());
    return (AST::Expr::Expr*)new AST::Expr::Minus(astExpr);
  }

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override {
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
    return (AST::Expr::Expr*)new AST::Expr::Mult(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
    return (AST::Expr::Expr*)new AST::Expr::Const(std::stoi(ctx->CONST()->getText()));
  }

  virtual antlrcpp::Any visitName(ifccParser::NameContext *ctx) override {
    return (AST::Expr::Expr*)new AST::Expr::Name(ctx->NAME()->getText());
  }
};

