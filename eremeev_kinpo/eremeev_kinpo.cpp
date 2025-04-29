#include <iostream>
#include "exprNode.h"
#include "error.h"

ExprNode* stringToExprTree(std::string rpnString, std::set <Error>* errors) {
    ExprNode ex;
    return &ex;
}


bool isOperand(std::string str) {
    return true;
}


bool checkRootOperator(ExprNodeType op) {
    return true;
}


void transformInequalityToLessOperator(ExprNode* node) {

}

int main()
{
    ExprNode ex("5");
    ex.addUnaryOperatorBefore(ExprNodeType::Not);
    std::cout << ex.getRpmOfTree();

    return 0;
}
