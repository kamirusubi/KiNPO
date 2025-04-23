#include <iostream>
#include "exprNode.h"
#include "error.h"

int main()
{
    ExprNode ex;
    ex.type = ExprNodeType::Plus;

    return 0;
}



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
