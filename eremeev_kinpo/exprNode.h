#pragma once

#include <string>
#include <map>
#include <set>

enum class ExprNodeType { Plus, Minus, Division, Multiplication, DivRemainder, UnaryMinus, Not, GreaterEqual, LessEqual, Greater, Less, Operand };

class ExprNode {
private:
    /// @brief “ип узла выражени€
    ExprNodeType type;
    /// @brief «начение узла, если узел - операнд
    std::string value = "";
    /// @brief ”казатель на первый операнд
    ExprNode* firstOperand = nullptr; 
    /// @brief ”казатель на второй операнд
    ExprNode* secondOperand = nullptr; 

public:
    /// @brief —татический словарь дл€ получени€ словесной записи оператора по его символу
    static const std::map<std::string, ExprNodeType> symbolToString;
    /// @brief —татический словарь дл€ получени€ символа оператора по его словесной записи
    static const std::map<ExprNodeType, std::string> stringToSymbol;
    /// @brief —татический словарь дл€ получени€ количества операндов
    static const std::map<ExprNodeType, int> operandCount;
    /// @brief —татический словарь с символами
    static const std::set<std::string> operatorsSymbols;

    /*!
    *  онструктор по умолчанию
    */
    ExprNode(){}

    /*!
    *  онструктор дл€ узла - операнда
    * \param[in] _value - значение узла
    */
    ExprNode(std::string _value) :
        type(ExprNodeType::Operand), value(_value){}

    /*!
    *  онструктор дл€ узла унарной операции
    * \param[in] _type - тип узла
    * \param[in] _firstOperand - указатель на операнд
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand) :
        type(_type), firstOperand(_firstOperand) {}

    /*!
    *  онструктор дл€ узла бинарной операции
    * \param[in] _type - тип узла
    * \param[in] _firstOperand - указатель на первый операнд
    * \param[in] _secondOperand - указатель на второй операнд
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand, ExprNode* _secondOperand) :
        type(_type), firstOperand(_firstOperand), secondOperand(_secondOperand) {}



    /*!
    * ћен€ет местами операнды узла дерева разбора выражени€
    */
    void swapOperands();

    /*!
    * ƒобавл€ет унарную операцию перед текущей
    * \param[in] operator - операци€, котора€ будет добавлена
    */
    void addUnaryOperatorBefore(ExprNodeType _operator);

    /*!
    *  опирует текущий узел
    * \return Ц указатель на копию узла
    */
    ExprNode* copyNode() const;

    /*!
    * —оздает строку с обратной польской
    * \return Ц строка с обратной польской записью
    */
    std::string getRpnOfTree() const;

    /*!
    * ¬озвращает тип узла
    * \return Ц значение пол€ type
    */
    ExprNodeType getType() const;

    /*!
    * »змен€ет тип узла
    * \param[in] newType - новый тип пол€ type
    */
    void setType(ExprNodeType newType);

    /*!
    * ¬озвращает значение узла
    * \return Ц значение пол€ value
    */
    std::string getValue() const;

    /*!
    * »змен€ет значение узла
    * \param[in] newValue - строка с новым содержимым пол€ value
    */
    void setValue(const std::string& newValue);

    /*!
    * ¬озвращает ссылку на первый операнд узла
    * \return Ц ссылка на первый операнд узла
    */
    ExprNode* getFirstOperand() const;

    /*!
    * »змен€ет значение первого операнда узла
    * \param[in] newFirstOperand - ссылка на новый первый операнд
    */
    void setFirstOperand(ExprNode* newFirstOperand);

    /*!
    * ¬озвращает ссылку на второй операнд узла
    * \return Ц ссылка на второй операнд узла
    */
    ExprNode* getSecondOperand() const;

    /*!
    * »змен€ет значение второго операнда узла
    * \param[in] newSecondOperand - ссылка на новый второй операнд
    */
    void setSecondOperand(ExprNode* newSecondOperand);

};