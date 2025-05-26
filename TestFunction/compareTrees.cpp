#include "pch.h"
#include "compareTrees.h"
#include <sstream>
#include <locale>
#include <codecvt>

// ������� ��� �������������� std::string � std::wstring
std::wstring s2ws(const std::string& s) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}


// ���������� ������ � ������� "�� ���� ...->...->.... ���������:... ��������: ..."
bool compareExprTrees(const ExprNode* expected, const ExprNode* actual, const std::wstring& path, std::set<std::wstring>* errors) {
    bool flag = true;
    std::wstring error = L"On path \"" + path + L"\" expected: ";

    if (expected == nullptr && actual == nullptr) {
        return true;
    }

    if (expected == nullptr && actual != nullptr) {
        error += L"nullptr; actual " + s2ws(actual->getRpnOfTree());
        errors->insert(error);
        return false;
    }

    if (expected != nullptr && actual == nullptr) {
        error += s2ws(expected->getRpnOfTree()) + L"; actual: nullptr"; // �������������� �����
        errors->insert(error);
        return false;
    }

    if (expected->getType() != actual->getType()) {
        error += s2ws(ExprNode::stringToSymbol.at(expected->getType())) + L"; actual: " + s2ws(ExprNode::stringToSymbol.at(actual->getType())); // �������������� �����
        errors->insert(error);
        return false;
    }

    if (expected->getType() == ExprNodeType::Operand && expected->getValue() != actual->getValue()) {
        error += s2ws(expected->getValue()) + L"; actual: " + s2ws(actual->getValue()); // �������������� �����
        errors->insert(error);
        return false;
    }

    if (expected->getFirstOperand() != nullptr || actual->getFirstOperand() != nullptr) {
        flag = compareExprTrees(expected->getFirstOperand(), actual->getFirstOperand(), path + s2ws(ExprNode::stringToSymbol.at(expected->getType())) + L" -> ", errors) && flag;
    }

    if (expected->getSecondOperand() != nullptr || actual->getSecondOperand() != nullptr) {
        flag = compareExprTrees(expected->getSecondOperand(), actual->getSecondOperand(), path + s2ws(ExprNode::stringToSymbol.at(expected->getType())) + L" -> ", errors) && flag;
    }

    return flag;
}