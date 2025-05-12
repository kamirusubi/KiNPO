#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/error.cpp"
#include "../eremeev_kinpo/exprNode.cpp"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace TestFunctions
//{
//	TEST_CLASS(TestTransformInequalityToLessOperator)
//	{
//	public:
//		TEST_METHOD(Test1_CurrentIsLess) { // Текущая операция – «меньше»
//
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x <", errors);
//			transformInequalityToLessOperator(tree);
//
//			ExprNode* expTree = stringToExprTree("5 x <", errors);
//
//			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//		TEST_METHOD(Test2_CurrentIsLessEqual) { // Текущая операция – «меньше или равно»
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x <=", errors);
//			transformInequalityToLessOperator(tree);
//
//			ExprNode* expTree = stringToExprTree("x 5 < !", errors);
//
//			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//		TEST_METHOD(Test3_CurrentIsGreater) { // Текущая операция – «больше»
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x + x + 7 >", errors);
//			transformInequalityToLessOperator(tree);
//
//			ExprNode* expTree = stringToExprTree("7 5 x + x + <", errors);
//
//			std::string errorMessage = "Test 3 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//		TEST_METHOD(Test4_CurrentIsGreaterEqual) { // Текущая операция – «больше или равно»
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x >=", errors);
//			transformInequalityToLessOperator(tree);
//
//			ExprNode* expTree = stringToExprTree("5 x < !", errors);
//
//			std::string errorMessage = "Test 4 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//	};
//}
