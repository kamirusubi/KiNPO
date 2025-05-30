#pragma once

#include <string>
#include <map>
#include <set>

enum class ExprNodeType { Plus, Minus, Division, Multiplication, DivRemainder, UnaryMinus, Not, GreaterEqual, LessEqual, Greater, Less, Operand };

class ExprNode {
private:
    /// @brief ��� ���� ���������
    ExprNodeType type;
    /// @brief �������� ����, ���� ���� - �������
    std::string value = "";
    /// @brief ��������� �� ������ �������
    ExprNode* firstOperand = nullptr; 
    /// @brief ��������� �� ������ �������
    ExprNode* secondOperand = nullptr; 

public:
    /// @brief ����������� ������� ��� ��������� ��������� ������ ��������� �� ��� �������
    static const std::map<std::string, ExprNodeType> symbolToString;
    /// @brief ����������� ������� ��� ��������� ������� ��������� �� ��� ��������� ������
    static const std::map<ExprNodeType, std::string> stringToSymbol;
    /// @brief ����������� ������� ��� ��������� ���������� ���������
    static const std::map<ExprNodeType, int> operandCount;
    /// @brief ����������� ������� � ���������
    static const std::set<std::string> operatorsSymbols;

    /*!
    * ����������� �� ���������
    */
    ExprNode(){}

    /*!
    * ����������� ��� ���� - ��������
    * \param[in] _value - �������� ����
    */
    ExprNode(std::string _value) :
        type(ExprNodeType::Operand), value(_value){}

    /*!
    * ����������� ��� ���� ������� ��������
    * \param[in] _type - ��� ����
    * \param[in] _firstOperand - ��������� �� �������
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand) :
        type(_type), firstOperand(_firstOperand) {}

    /*!
    * ����������� ��� ���� �������� ��������
    * \param[in] _type - ��� ����
    * \param[in] _firstOperand - ��������� �� ������ �������
    * \param[in] _secondOperand - ��������� �� ������ �������
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand, ExprNode* _secondOperand) :
        type(_type), firstOperand(_firstOperand), secondOperand(_secondOperand) {}



    /*!
    * ������ ������� �������� ���� ������ ������� ���������
    */
    void swapOperands();

    /*!
    * ��������� ������� �������� ����� �������
    * \param[in] operator - ��������, ������� ����� ���������
    */
    void addUnaryOperatorBefore(ExprNodeType _operator);

    /*!
    * �������� ������� ����
    * \return � ��������� �� ����� ����
    */
    ExprNode* copyNode() const;

    /*!
    * ������� ������ � �������� ��������
    * \return � ������ � �������� �������� �������
    */
    std::string getRpnOfTree() const;

    /*!
    * ���������� ��� ����
    * \return � �������� ���� type
    */
    ExprNodeType getType() const;

    /*!
    * �������� ��� ����
    * \param[in] newType - ����� ��� ���� type
    */
    void setType(ExprNodeType newType);

    /*!
    * ���������� �������� ����
    * \return � �������� ���� value
    */
    std::string getValue() const;

    /*!
    * �������� �������� ����
    * \param[in] newValue - ������ � ����� ���������� ���� value
    */
    void setValue(const std::string& newValue);

    /*!
    * ���������� ������ �� ������ ������� ����
    * \return � ������ �� ������ ������� ����
    */
    ExprNode* getFirstOperand() const;

    /*!
    * �������� �������� ������� �������� ����
    * \param[in] newFirstOperand - ������ �� ����� ������ �������
    */
    void setFirstOperand(ExprNode* newFirstOperand);

    /*!
    * ���������� ������ �� ������ ������� ����
    * \return � ������ �� ������ ������� ����
    */
    ExprNode* getSecondOperand() const;

    /*!
    * �������� �������� ������� �������� ����
    * \param[in] newSecondOperand - ������ �� ����� ������ �������
    */
    void setSecondOperand(ExprNode* newSecondOperand);

};