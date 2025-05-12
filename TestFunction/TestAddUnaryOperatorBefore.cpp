#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestAddUnaryOperatorBefore)
	{
	public:
		TEST_METHOD(Test1_CurrentIsValue) { // Текущий узел - значение
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 !", errors);


			std::set<std::wstring> _errors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &_errors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!_errors.empty()) {
				wss << L"Test 1 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : _errors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}

		TEST_METHOD(Test2_CurrentIsOperation) { // Текущий узел - операция
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);

			std::set<std::wstring> _errors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &_errors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!_errors.empty()) {
				wss << L"Test 2 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : _errors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}

		TEST_METHOD(Test3_CurrentIsIntermediate) { // Текущий узел - промежуточный
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->secondOperand->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x ! <", errors);

			std::set<std::wstring> _errors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &_errors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!_errors.empty()) {
				wss << L"Test 3 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : _errors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
	};
}
