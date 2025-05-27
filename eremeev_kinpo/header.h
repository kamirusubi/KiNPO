#pragma once
#include "exprNode.h"
#include "error.h"
#include <string>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
#include <fstream>


/*!
* \Создает дерево разбора выражения строки в обратной польской записи
* \param[in] rpnString – строка в обратной польской записи
* \param[out] errors – указатель контейнер с ошибками
* \return – указатель на дерево разбора выражения
*/
ExprNode* stringToExprTree(std::string rpnString, std::set <Error>* errors);

/*!
* \Проверяет, является ли строка операндом
* \param[in] str – строка, которая будет проверена
* \return - true, если строка операндом; false, если строка не является операндом
*/
bool isOperand(std::string str);

/*!
* \Проверяет, является ли корневая операция допустимой
* \param[in] operator – тип операции
* \param[out] errors – указатель на контейнер с ошибками
* \return - true, если операция допустима; false, если строка операция не допустима
*/
bool checkRootOperator(ExprNodeType _operator);

/*!
* \Преобразует узел дерева разбора выражения к операции «меньше»
* \param[in/out] obj – указатель на узел, который должен быть преобразован
*/
void transformInequalityToLessOperator(ExprNode* node);

/*!
* \Возвращает строку, содержащую содердимое файла
* \param[in] filename – путь до файла, откуда будут прочитаны данные
* \param[out] errors – указатель на контейнер с ошибками
* \return - строка с содержимым файла
*/
std::string* readFileToString(const std::string filePath, std::set <Error>* errors);