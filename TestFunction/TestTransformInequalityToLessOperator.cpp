#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/error.cpp"
#include "../eremeev_kinpo/exprNode.cpp"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestTransformInequalityToLessOperator)
	{
	public:
		TEST_METHOD(Test1_CurrentIsLess) { // Текущая операция – «меньше»

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x <", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 1 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
		TEST_METHOD(Test2_CurrentIsLessEqual) { // Текущая операция – «меньше или равно»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("x 5 < !", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 2 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
		TEST_METHOD(Test3_CurrentIsGreater) { // Текущая операция – «больше»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + x + 7 >", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("7 5 x + x + <", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 3 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
		TEST_METHOD(Test4_CurrentIsGreaterEqual) { // Текущая операция – «больше или равно»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x >=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 4 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
	};
}
