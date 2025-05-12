#include "pch.h"
#include "compareTrees.h"
	bool compareExprTrees(const ExprNode* expTree, const ExprNode* tree) {
		bool flag = true;
		// ≈сли оба узла nullptr, деревь€ одинаковы (базовый случай)
		if (expTree == nullptr && tree == nullptr) {
			return true;
		}

		// ≈сли один из узлов nullptr, а другой нет, деревь€ разные
		if ((expTree == nullptr && tree != nullptr) || (expTree != nullptr && tree == nullptr)) {
			flag = false && flag;
		}

		// —равнение типов узлов
		if (expTree->type != tree->type) {
			flag = false && flag;
		}

		// —равнение значений (только дл€ операндов)
		if (expTree->type == ExprNodeType::Operand && expTree->value != tree->value) {
			flag = false && flag;
		}

		// –екурсивное сравнение операндов
		if (!compareExprTrees(expTree->firstOperand, tree->firstOperand)) {
			flag = false && flag;
		}
		if (!compareExprTrees(expTree->secondOperand, tree->secondOperand)) {
			flag = false && flag;
		}

		// ≈сли все проверки пройдены, деревь€ одинаковы
		return flag;
	}

	