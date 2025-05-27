#pragma once

#include <string>
#include <map>
#include <set>

enum class ExprNodeType { Plus, Minus, Division, Multiplication, DivRemainder, UnaryMinus, Not, GreaterEqual, LessEqual, Greater, Less, Operand };

class ExprNode {
private:
    ExprNodeType type; //��� ���� ���������
    std::string value = ""; // �������� ����, ���� ���� - �������
    ExprNode* firstOperand = nullptr; // ������ �������
    ExprNode* secondOperand = nullptr; // ������ �������

public:
    //����������� ������� ��� ��������� ��������� ������ ��������� �� ��� �������
    static const std::map<std::string, ExprNodeType> symbolToString;
    //����������� ������� ��� ��������� ������� ��������� �� ��� ��������� ������
    static const std::map<ExprNodeType, std::string> stringToSymbol;
    //����������� ������� ��� ��������� ���������� ���������
    static const std::map<ExprNodeType, int> operandCount;
    //����������� ������� � ���������
    static const std::set<std::string> operatorsSymbols;

    /*!
    * \����������� �� ���������
    */
    ExprNode(){}

    /*!
    * \����������� ��� ���� - ��������
    * \param[in] _value - �������� ����
    */
    ExprNode(std::string _value) :
        type(ExprNodeType::Operand), value(_value){}

    /*!
    * \����������� ��� ���� ������� ��������
    * \param[in] _type - ��� ����
    * \param[in] _firstOperand - ��������� �� �������
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand) :
        type(_type), firstOperand(_firstOperand) {}

    /*!
    * \����������� ��� ���� �������� ��������
    * \param[in] _type - ��� ����
    * \param[in] _firstOperand - ��������� �� ������ �������
    * \param[in] _secondOperand - ��������� �� ������ �������
    */
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand, ExprNode* _secondOperand) :
        type(_type), firstOperand(_firstOperand), secondOperand(_secondOperand) {}



    /*!
    * \������ ������� �������� ���� ������ ������� ���������
    * \this � ����, �������� �������� ���������� �������
    */
    void swapOperands();

    /*!
    * \��������� ������� �������� ����� �������
    * \param[in] operator - ��������, ������� ����� ���������
    */
    void addUnaryOperatorBefore(ExprNodeType _operator);

    /*!
    * \�������� ������� ����
    * \this � ����, ������� ����� ����������
    * \return � ��������� �� ����� ����
    */
    ExprNode* copyNode() const;

    /*!
    * \������� ������ � �������� ��������
    * \return � ������ � �������� �������� �������
    */
    std::string getRpnOfTree() const;

    /*!
    * \���������� ��� ����
    * \return � �������� ���� type
    */
    ExprNodeType getType() const;

    /*!
    * \�������� ��� ����
    * \param[in] newType - ����� ��� ���� type
    */
    void setType(ExprNodeType newType);

    /*!
    * \���������� �������� ����
    * \return � �������� ���� value
    */
    std::string getValue() const;

    /*!
    * \�������� �������� ����
    * \param[in] newValue - ������ � ����� ���������� ���� value
    */
    void setValue(const std::string& newValue);

    /*!
    * \���������� ������ �� ������ ������� ����
    * \return � ������ �� ������ ������� ����
    */
    ExprNode* getFirstOperand() const;

    /*!
    * \�������� �������� ������� �������� ����
    * \param[in] newFirstOperand - ������ �� ����� ������ �������
    */
    void setFirstOperand(ExprNode* newFirstOperand);

    /*!
    * \���������� ������ �� ������ ������� ����
    * \return � ������ �� ������ ������� ����
    */
    ExprNode* getSecondOperand() const;

    /*!
    * \�������� �������� ������� �������� ����
    * \param[in] newSecondOperand - ������ �� ����� ������ �������
    */
    void setSecondOperand(ExprNode* newSecondOperand);

};