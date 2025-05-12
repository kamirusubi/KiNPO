#include "pch.h"
//#include "CppUnitTest.h"
//#include "../eremeev_kinpo/header.h"
//#include "compareTrees.h"
//
//using namespace Microsoft::VisualStudio::CppUnitTestFramework;
//
//namespace TestFunctions
//{
//	TEST_CLASS(TestSwapOperands)
//	{
//	public:
//		TEST_METHOD(Test1_OperandsAreNotNodes) { // ќперанды €вл€ютс€ значени€ми
//
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x <", errors);
//			tree->swapOperands();
//
//			ExprNode* expTree = stringToExprTree("x 5 <", errors);
//
//			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//		TEST_METHOD(Test2_OperandsAreNodes) { // ќперанды содержат узлы
//
//			std::set<Error>* errors = new std::set<Error>();
//			ExprNode* tree = stringToExprTree("5 x + 7 <", errors);
//			tree->swapOperands();
//
//			ExprNode* expTree = stringToExprTree("7 5 x + <", errors);
//
//			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpnOfTree() + "; Actual: " + tree->getRpnOfTree();
//			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());
//
//			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
//		}
//	};
//}
