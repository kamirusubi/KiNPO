#pragma once

#include "exprNode.h"
#include "error.h"

/*!
* \������� ������ ������� ��������� ������ � �������� �������� ������
* \param[in] rpnString � ������ � �������� �������� ������
* \param[out] errors � ��������� ��������� � ��������
* \return � ��������� �� ������ ������� ���������
*/
ExprNode* stringToExprTree(std::string rpnString, std::set <Error>* errors);

/*!
* \���������, �������� �� ������ ���������
* \param[in] str � ������, ������� ����� ���������
* \return - true, ���� ������ ���������; false, ���� ������ �� �������� ���������
*/
bool isOperand(std::string str);

/*!
* \���������, �������� �� �������� �������� ����������
* \param[in] operator � ��� ��������
* \param[out] errors � ��������� �� ��������� � ��������
* \return - true, ���� �������� ���������; false, ���� ������ �������� �� ���������
*/
bool checkRootOperator(ExprNodeType op);

/*!
* \����������� ���� ������ ������� ��������� � �������� �������
* \param[in/out] obj � ��������� �� ����, ������� ������ ���� ������������
*/
void transformInequalityToLessOperator(ExprNode* node);

