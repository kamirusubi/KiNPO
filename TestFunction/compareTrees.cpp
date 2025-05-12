#include "pch.h"
#include "compareTrees.h"
#include <sstream>
#include <locale>
#include <codecvt>

// Функция для преобразования std::string в std::wstring
std::wstring s2ws(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}

bool compareExprTrees(const ExprNode* expected, const ExprNode* actual, const std::wstring& path, std::set<std::wstring>* errors) {
    bool flag = true;
    std::wstring error = L"On path \"" + path + L"\" expected: "; // Преобразование path к std::wstring

    if (expected == nullptr && actual == nullptr) {
        return true;
    }

    if (expected == nullptr && actual != nullptr) {
        error += L"nullptr; actual " + s2ws(actual->getRpnOfTree());
        errors->insert(error);
        return false;
    }

    if (expected != nullptr && actual == nullptr) {
        error += s2ws(expected->getRpnOfTree()) + L"; actual: nullptr"; // Преобразование здесь
        errors->insert(error);
        return false;
    }

    if (expected->type != actual->type) {
        error += s2ws(ExprNode::stringToSymbol.at(expected->type)) + L"; actual: " + s2ws(ExprNode::stringToSymbol.at(actual->type)); // Преобразование здесь
        errors->insert(error);
        return false;
    }

    if (expected->type == ExprNodeType::Operand && expected->value != actual->value) {
        error += s2ws(expected->value) + L"; actual: " + s2ws(actual->value); // Преобразование здесь
        errors->insert(error);
        return false;
    }

    if (expected->firstOperand != nullptr || actual->firstOperand != nullptr) {
        flag = compareExprTrees(expected->firstOperand, actual->firstOperand, path + s2ws(ExprNode::stringToSymbol.at(expected->type)) + L" -> ", errors) && flag;
    }

    if (expected->secondOperand != nullptr || actual->secondOperand != nullptr) {
        flag = compareExprTrees(expected->secondOperand, actual->secondOperand, path + s2ws(ExprNode::stringToSymbol.at(expected->type)) + L" -> ", errors) && flag;
    }

    return flag;
}