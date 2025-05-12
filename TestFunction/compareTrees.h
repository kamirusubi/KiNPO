#pragma once
#include "../eremeev_kinpo/exprNode.h"
#include "../eremeev_kinpo/error.h"
bool compareExprTrees(const ExprNode* expected, const ExprNode* actual, const std::wstring& path, std::set<std::wstring>* errors);
