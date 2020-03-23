
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
    std::cout << "Axiom  FinAxiom" << std::endl;
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProg(ifccParser::ProgContext *ctx) override {
    std::cout << "Prog" << std::endl;
    AST::Bloc* astBloc = visit(ctx->bloc());
    AST::Expr::Expr* astExpr = visit(ctx->expr());
//    auto truc = new AST::Prog(astBloc, astExpr);
    std::cout << "FinProg" << std::endl;
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
    std::cout << "DefExpr" << std::endl;
    AST::Expr::Expr* astExpr = visit(ctx->expr());
//    auto truc = new AST::Def(ctx->NAME()->getText(), astExpr);
    std::cout << "FinDefExpr" << std::endl;
    return new AST::Def(ctx->NAME()->getText(), astExpr);
  }

  virtual antlrcpp::Any visitAdd(ifccParser::AddContext *ctx) override {
    std::cout << "Add" << std::endl;
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
//    auto truc = new AST::Expr::Add(astLeftExpr, astRightExpr);
    std::cout << "FinAdd" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Add(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitSub(ifccParser::SubContext *ctx) override {
    std::cout << "Sub" << std::endl;
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
    std::cout << "Ozymandias" << std::endl;
//    auto truc = new AST::Expr::Sub(astLeftExpr, astRightExpr);
    std::cout << "FinSub" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Sub(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitMinus(ifccParser::MinusContext *ctx) override {
    std::cout << "Minus" << std::endl;
    AST::Expr::Expr* astExpr = visit(ctx->expr());
//    auto truc = new AST::Expr::Minus(astExpr);
    std::cout << "FinMinus" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Minus(astExpr);
  }

  virtual antlrcpp::Any visitMult(ifccParser::MultContext *ctx) override {
    std::cout << "Mult" << std::endl;
    AST::Expr::Expr* astLeftExpr = visit(ctx->expr()[0]);
    AST::Expr::Expr* astRightExpr = visit(ctx->expr()[1]);
//    auto truc = new AST::Expr::Mult(astLeftExpr, astRightExpr);
    std::cout << "FinMult" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Mult(astLeftExpr, astRightExpr);
  }

  virtual antlrcpp::Any visitPar(ifccParser::ParContext *ctx) override {
    std::cout << "Par  FinPar" << std::endl;
    return visit(ctx->expr());
  }

  virtual antlrcpp::Any visitConst(ifccParser::ConstContext *ctx) override {
    std::cout << "Const" << std::endl;
    std::cout << ctx->CONST()->getText() << '|' << std::endl;
//    auto truc = new AST::Expr::Const(std::stoi(ctx->CONST()->getText()));
    std::cout << "FinConst" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Const(std::stoi(ctx->CONST()->getText()));
  }

  virtual antlrcpp::Any visitName(ifccParser::NameContext *ctx) override {
    std::cout << "Name" << std::endl;
//    auto truc = new AST::Expr::Name(ctx->NAME()->getText());
    std::cout << "FinName" << std::endl;
    return (AST::Expr::Expr*)new AST::Expr::Name(ctx->NAME()->getText());
  }
};

