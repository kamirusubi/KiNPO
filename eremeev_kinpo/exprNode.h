#pragma once

#include <string>
#include <map>
#include <set>

enum class ExprNodeType { Plus, Minus, Division, Multiplication, DivRemainder, UnaryMinus, Not, GreaterEqual, LessEqual, Greater, Less, Operand };

class ExprNode {
public:
    ExprNodeType type; //тип узла выражения
    std::string value = ""; // значение узла, если узел - операнд
    ExprNode* firstOperand = nullptr; // первый операнд
    ExprNode* secondOperand = nullptr; // второй операнд


    //статический словарь для получения словесной записи оператора по его символу
    static const std::map<std::string, ExprNodeType> symbolToString;
    //статический словарь для получения символа оператора по его словесной записи
    static const std::map<ExprNodeType, std::string> stringToSymbol;
    //статический словарь для получения количества операндов
    static const std::map<ExprNodeType, int> operandCount;
    //статический словарь с символами
    static const std::set<std::string> operatorsSymbols;

    //Конструктор по умолчанию
    ExprNode(){}

    //Конструктор для узла операнда
    ExprNode(std::string _value) :
        type(ExprNodeType::Operand), value(_value){}

    //Конструктор для узла унарной операции
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand) :
        type(_type), firstOperand(_firstOperand) {}

    //Конструктор для узла бинарной операции
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand, ExprNode* _secondOperand) :
        type(_type), firstOperand(_firstOperand), secondOperand(_secondOperand) {}

    /*!
    * \Меняет местами операнды узла дерева разбора выражения
    * \this – узел, операнды которого поменяются местами
    */
    void swapOperands();

    /*!
    * \Добавляет унарную операцию перед текущей
    * \param[in] operator - операция, которая будет добавлена
    */
    void addUnaryOperatorBefore(ExprNodeType op);

    /*!
    * \Копирует текущий узел
    * \this – узел, который будет скопирован
    * \return – указатель на копию узла
    */
    ExprNode* copyNode() const;

    /*!
    * \Создает строку с обратной польской
    * \return – строка с обратной польской записью
    */
    std::string getRpnOfTree() const;


};