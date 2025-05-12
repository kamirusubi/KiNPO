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
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 !", errors);

			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}

		TEST_METHOD(Test2_CurrentIsOperation) { // ������� ���� - ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);

			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}

		TEST_METHOD(Test3_CurrentIsIntermediate) { // ������� ���� - �������������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->secondOperand->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x ! <", errors);

			std::string errorMessage = "Test 3 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
	};
}
