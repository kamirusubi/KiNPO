#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestSwapOperands)
	{
	public:
		TEST_METHOD(Test1_OperandsAreNotNodes) { // ќперанды €вл€ютс€ значени€ми

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->swapOperands();

			ExprNode* expTree = stringToExprTree("x 5 <", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// —обираем все ошибки в одну строку дл€ Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 1 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
		TEST_METHOD(Test2_OperandsAreNodes) { // ќперанды содержат узлы

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + 7 <", errors);
			tree->swapOperands();

			ExprNode* expTree = stringToExprTree("7 5 x + <", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// —обираем все ошибки в одну строку дл€ Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 2 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
	};
}
