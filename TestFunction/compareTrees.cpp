#include "pch.h"
#include "compareTrees.h"
	bool compareExprTrees(const ExprNode* expTree, const ExprNode* tree) {
		bool flag = true;
		// ���� ��� ���� nullptr, ������� ��������� (������� ������)
		if (expTree == nullptr && tree == nullptr) {
			return true;
		}

		// ���� ���� �� ����� nullptr, � ������ ���, ������� ������
		if ((expTree == nullptr && tree != nullptr) || (expTree != nullptr && tree == nullptr)) {
			flag = false && flag;
		}

		// ��������� ����� �����
		if (expTree->type != tree->type) {
			flag = false && flag;
		}

		// ��������� �������� (������ ��� ���������)
		if (expTree->type == ExprNodeType::Operand && expTree->value != tree->value) {
			flag = false && flag;
		}

		// ����������� ��������� ���������
		if (!compareExprTrees(expTree->firstOperand, tree->firstOperand)) {
			flag = false && flag;
		}
		if (!compareExprTrees(expTree->secondOperand, tree->secondOperand)) {
			flag = false && flag;
		}

		// ���� ��� �������� ��������, ������� ���������
		return flag;
	}

	