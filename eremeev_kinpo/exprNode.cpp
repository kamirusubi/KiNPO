#include "ExprNode.h"

void ExprNode::swapOperands() {
    int a = 1;
}

void ExprNode::addUnaryOperatorBefore(ExprNodeType op) {
    int a = 1;

}

ExprNode* ExprNode::copyNode() const {
    ExprNode ex;
    return &ex;
}

std::string ExprNode::getRpmOfTree() const {
    return "";
}

// Инициализация статических членов класса
const std::map<std::string, ExprNodeType> ExprNode::symbolToString = {
    {"+", ExprNodeType::Plus},
    {"-", ExprNodeType::Minus},
    {"/", ExprNodeType::Division},
    {"*", ExprNodeType::Multiplication},
    {"%", ExprNodeType::DivRemainder},
    {"~", ExprNodeType::UnaryMinus},
    {"!", ExprNodeType::Not},
    {">=", ExprNodeType::GreaterEqual},
    {"<=", ExprNodeType::LessEqual},
    {">", ExprNodeType::Greater},
    {"<", ExprNodeType::Less}
};

const std::map<ExprNodeType, std::string> ExprNode::stringToSymbol = {
    {ExprNodeType::Plus, "+"},
    {ExprNodeType::Minus, "-"},
    {ExprNodeType::Division, "/"},
    {ExprNodeType::Multiplication, "*"},
    {ExprNodeType::DivRemainder, "%"},
    {ExprNodeType::UnaryMinus, "~"},
    {ExprNodeType::Not, "!"},
    {ExprNodeType::GreaterEqual, ">="},
    {ExprNodeType::LessEqual, "<="},
    {ExprNodeType::Greater, ">"},
    {ExprNodeType::Less, "<"}
};

const std::map<ExprNodeType, int> ExprNode::operandCount = {
    {ExprNodeType::Plus, 2},
    {ExprNodeType::Minus, 2},
    {ExprNodeType::Division, 2},
    {ExprNodeType::Multiplication, 2},
    {ExprNodeType::DivRemainder, 2},
    {ExprNodeType::UnaryMinus, 1},
    {ExprNodeType::Not, 1},
    {ExprNodeType::GreaterEqual, 2},
    {ExprNodeType::LessEqual, 2},
    {ExprNodeType::Greater, 2},
    {ExprNodeType::Less, 2}
};

const std::set<std::string> ExprNode::operatorsSymbols = {
    "+", "-", "/", "*", "%", "~", "!", ">=", "<=", ">", "<"
};