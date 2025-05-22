#pragma once

#include <string>
#include <map>
#include <set>

enum class ExprNodeType { Plus, Minus, Division, Multiplication, DivRemainder, UnaryMinus, Not, GreaterEqual, LessEqual, Greater, Less, Operand };

class ExprNode {
public:
    ExprNodeType type; //��� ���� ���������
    std::string value = ""; // �������� ����, ���� ���� - �������
    ExprNode* firstOperand = nullptr; // ������ �������
    ExprNode* secondOperand = nullptr; // ������ �������


    //����������� ������� ��� ��������� ��������� ������ ��������� �� ��� �������
    static const std::map<std::string, ExprNodeType> symbolToString;
    //����������� ������� ��� ��������� ������� ��������� �� ��� ��������� ������
    static const std::map<ExprNodeType, std::string> stringToSymbol;
    //����������� ������� ��� ��������� ���������� ���������
    static const std::map<ExprNodeType, int> operandCount;
    //����������� ������� � ���������
    static const std::set<std::string> operatorsSymbols;

    //����������� �� ���������
    ExprNode(){}

    //����������� ��� ���� ��������
    ExprNode(std::string _value) :
        type(ExprNodeType::Operand), value(_value){}

    //����������� ��� ���� ������� ��������
    ExprNode(ExprNodeType _type, ExprNode* _firstOperand) :
        type(_type), firstOperand(_firstOperand) {}

    //����������� ��� ���� �������� ��������
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
    void addUnaryOperatorBefore(ExprNodeType op);

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


};