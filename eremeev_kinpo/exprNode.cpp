#include "ExprNode.h"

void ExprNode::swapOperands() {
    //��������� ��������� �� ������ ������� � tmp
    ExprNode* tmp = this->firstOperand;
    //��������� � ���� ��� ������� �������� ��������� �� ������ �������
    this->firstOperand = this->secondOperand;
    //��������� � ���� ��� ������� �������� tmp
    this->secondOperand = tmp;
}

void ExprNode::addUnaryOperatorBefore(ExprNodeType op) {
    // ������� ��������� �� ����� ���� newNode
    ExprNode* newNode = this->copyNode(); // �������� ������� ����

    // �������� newNode � ������ ������� �������� ����
    firstOperand = newNode;

    // �������� �������� ������� �������� �������� ����
    secondOperand = nullptr; // ��� = NULL; (�� nullptr ����� ��� C++)

    // �������� ��� �������� �� operator
    type = op;
    value = ""; // ������� value, ���� ���� ������ ��������
}

ExprNode* ExprNode::copyNode() const {
    ExprNode* newNode = new ExprNode(); // ������� ����� ���� � ����

    newNode->type = type; // ����������� ��� ��������

    // ���� ������� ���� - �������
    if (type == ExprNodeType::Operand) {
        newNode->value = value; // ����������� �������� �������� 
    }
    //����� ���� ������� ���� ����� ������ �������
    else if (firstOperand) {
        //��������� � ������ ������� newNode �������� ������� �������� �������� ����
        newNode->firstOperand = firstOperand;
        //���� ������� ���� ����� ������ �������
        if (secondOperand) {
            //��������� � ������ ������� newNode �������� ������� �������� ������������
            newNode->secondOperand = secondOperand;
        }
    }

    return newNode; // ���������� ��������� �� ������������� ����
}

std::string ExprNode::getRpmOfTree() const {
    std::string result = ""; // ������ ��� �������� �������� �������� ������

    // ���� ������� ���� - �������
    if (type == ExprNodeType::Operand) {
        // ���������� �������� ���� value
        result += value; 
    }
    // ����� ���� ������� ���� ����� ������ �������
    else if (firstOperand) {
            // ���������� �������� �������� ������ ������� ��������
            result += firstOperand->getRpmOfTree() + " ";
        // ���� ������� ���� ����� ������ �������
        if (secondOperand) {
            // ���������� �������� �������� ������ ������� ��������
            result += secondOperand->getRpmOfTree() + " ";
        }
        // ��������� � ������ �������������� ������ ��������� �� ������� stringToSymbol
        result += stringToSymbol.at(type);
    }
    // ���������� ������ � �������� �������� �������
    return result; 
}

// ������������� ����������� ������ ������
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