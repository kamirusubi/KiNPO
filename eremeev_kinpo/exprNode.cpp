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

std::string ExprNode::getRpnOfTree() const {
    std::string result = ""; // ������ ��� �������� �������� �������� ������

    // ���� ������� ���� - �������
    if (type == ExprNodeType::Operand) {
        // ���������� �������� ���� value
        result += value; 
    }
    // ����� ���� ������� ���� ����� ������ �������
    else if (firstOperand) {
            // ���������� �������� �������� ������ ������� ��������
            result += firstOperand->getRpnOfTree() + " ";
        // ���� ������� ���� ����� ������ �������
        if (secondOperand) {
            // ���������� �������� �������� ������ ������� ��������
            result += secondOperand->getRpnOfTree() + " ";
        }
        // ��������� � ������ �������������� ������ ��������� �� ������� stringToSymbol
        result += stringToSymbol.at(type);
    }
    // ���������� ������ � �������� �������� �������
    return result; 
}



ExprNodeType ExprNode::getType() const {
    return this->type;
}


void ExprNode::setType(ExprNodeType newType) {
    this->type = newType;
}

std::string ExprNode::getValue() const {
    return this->value;
}


void ExprNode::setValue(const std::string& newValue) {
    this->value = newValue;
}


ExprNode* ExprNode::getFirstOperand() const {
    return this->firstOperand;
}


void ExprNode::setFirstOperand(ExprNode* newFirstOperand) {
    this->firstOperand = newFirstOperand;
}


ExprNode* ExprNode::getSecondOperand() const {
    return this->secondOperand;
}


void ExprNode::setSecondOperand(ExprNode* newSecondOperand) {
    this->secondOperand = newSecondOperand;
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