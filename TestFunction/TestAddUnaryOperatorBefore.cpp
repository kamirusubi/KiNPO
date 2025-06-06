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
		TEST_METHOD(Test1_CurrentIsValue) { // ������� ���� - ��������
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree("5", &errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 !", &errors);


			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// �������� ��� ������ � ���� ������ ��� Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 1 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}

		TEST_METHOD(Test2_CurrentIsOperation) { // ������� ���� - ��������
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", &errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x < !", &errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// �������� ��� ������ � ���� ������ ��� Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 2 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}

		TEST_METHOD(Test3_CurrentIsIntermediate) { // ������� ���� - �������������
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", &errors);
			tree->getSecondOperand()->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x ! <", &errors);

			std::set<std::wstring> compareTreesErrors;
			bool areEqual = compareExprTrees(tree, expTree, L"", &compareTreesErrors);
			// �������� ��� ������ � ���� ������ ��� Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 3 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqual, wss.str().c_str());
		}
	};
}
