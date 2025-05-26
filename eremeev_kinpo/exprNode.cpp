#include "ExprNode.h"

void ExprNode::swapOperands() {
    //—охранить указатель на первый операнд в tmp
    ExprNode* tmp = this->firstOperand;
    //ѕоместить в поле дл€ первого операнда указатель на второй операнд
    this->firstOperand = this->secondOperand;
    //ѕоместить в поле дл€ второго операнда tmp
    this->secondOperand = tmp;
}

void ExprNode::addUnaryOperatorBefore(ExprNodeType op) {
    // —оздаем указатель на новый узел newNode
    ExprNode* newNode = this->copyNode(); //  опируем текущий узел

    // ѕомещаем newNode в первый операнд текущего узла
    firstOperand = newNode;

    // ќбнул€ем значение второго операнда текущего узла
    secondOperand = nullptr; // »ли = NULL; (но nullptr лучше дл€ C++)

    // »змен€ем тип операции на operator
    type = op;
    value = ""; // ќчищаем value, если узел теперь оператор
}

ExprNode* ExprNode::copyNode() const {
    ExprNode* newNode = new ExprNode(); // —оздаем новый узел в куче

    newNode->type = type; // ѕрисваиваем тип операции

    // ≈сли текущий узел - операнд
    if (type == ExprNodeType::Operand) {
        newNode->value = value; // ѕрисваиваем значение операнда 
    }
    //»наче если текущий узел имеет первый операнд
    else if (firstOperand) {
        //ѕрисвоить в первый операнд newNode значение первого операнда текущего узла
        newNode->firstOperand = firstOperand;
        //≈сли текущий узел имеет второй операнд
        if (secondOperand) {
            //ѕрисвоить в второй операнд newNode значение второго операнда текущегоузла
            newNode->secondOperand = secondOperand;
        }
    }

    return newNode; // ¬озвращаем указатель на скопированный узел
}

std::string ExprNode::getRpnOfTree() const {
    std::string result = ""; // —трока дл€ хранени€ обратной польской записи

    // ≈сли текущий узел - операнд
    if (type == ExprNodeType::Operand) {
        // «аписываем значение пол€ value
        result += value; 
    }
    // »наче если текущий узел имеет первый операнд
    else if (firstOperand) {
            // «аписываем обратную польскую запись первого операнда
            result += firstOperand->getRpnOfTree() + " ";
        // ≈сли текущий узел имеет второй операнд
        if (secondOperand) {
            // «аписываем обратную польскую запись второго операнда
            result += secondOperand->getRpnOfTree() + " ";
        }
        // ƒобавл€ем к строке математическую запись оператора из словар€ stringToSymbol
        result += stringToSymbol.at(type);
    }
    // ¬озвращаем строку с обратной польской записью
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



// »нициализаци€ статических членов класса
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