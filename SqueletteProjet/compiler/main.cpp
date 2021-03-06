#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ifccLexer.h"
#include "antlr4-generated/ifccParser.h"
#include "antlr4-generated/ifccBaseVisitor.h"
#include "visitor.h"
#include "IR/IR.h"

using namespace antlr4;
using namespace std;

int main(int argn, const char **argv) {
    stringstream in;
    if (argn == 2) {
        ifstream lecture(argv[1]);
        in << lecture.rdbuf();
    }

    std::string filename = (argv[1]);
    std::string filename_stripped = filename.substr(0, filename.find(".", 0));
    ANTLRInputStream input(in.str());
    ifccLexer lexer(&input);
    CommonTokenStream tokens(&lexer);

    tokens.fill();
//  for (auto token : tokens.getTokens()) {
//    std::cout << token->toString() << std::endl;
//  }

    ifccParser parser(&tokens);
    tree::ParseTree *tree = parser.axiom();

    int nbError = parser.getNumberOfSyntaxErrors();

    if (nbError < 1) {
        Visitor visitor;
        AST::Prog *ast = visitor.visit(tree);
        stringstream resultAssembly;

        //ast->display();

        std::vector<CFG *> cfgs = ast->generateIR();

        bool error = ast->getError();
        if (!error) {
            for (auto &it : cfgs) {
                it->gen_asm(resultAssembly);
            }

            ofstream output;
            output.open(filename_stripped + ".s");
            output << resultAssembly.str();
            output.close();
        } else {
            cout << ast->getErrorMsg();
            return 1;
        }
    } else {
        return 1;
    }

    return 0;
}
