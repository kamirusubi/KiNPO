#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestGetRpnOfExprTree)
	{
	public:
		TEST_METHOD(Test1_RootHasNoChildren) { // Корневой узел не имеет дочерних
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 >", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "x 5 >";
			Assert::AreEqual(expString, str, L"Test 1 Failed: Root with no children failed.");
		}

		TEST_METHOD(Test2_RootHasChildren) { // Корневой узел имеет дочерние
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 + 7 <=", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "x 5 + 7 <=";
			Assert::AreEqual(expString, str, L"Test 2 Failed: Root with children failed.");
		}

		TEST_METHOD(Test3_RootIsValue) { // Корневой узел - значение 
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "5";
			Assert::AreEqual(expString, str, L"Test 3 Failed: Root is value failed.");
		}

		TEST_METHOD(Test4_TreeContainsUnaryOperations) { // Дерево содержит унарные операции
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x ~ 5 >=", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "x ~ 5 >=";
			Assert::AreEqual(expString, str, L"Test 4 Failed: Tree with unary operations failed.");
		}

		TEST_METHOD(Test5_CheckMinusMultiplicationDivision) {// Проверка операторов «-», «*», «/»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x - 7 x * /", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "5 x - 7 x * /";
			Assert::AreEqual(expString, str, L"Test 5 Failed: -, *, / operators check failed.");
		}

		TEST_METHOD(Test6_CheckRemainderNotLess) { // Проверка операторов «%», «!», «<»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x % 7 ! <", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "5 x % 7 ! <";
			Assert::AreEqual(expString, str, L"Test 6 Failed: %, !, < operators check failed.");
		}

		TEST_METHOD(Test7_StringContainsUnderscoreVariables) { // Строка содержит переменные на «_»
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("_123 1 +", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "_123 1 +";
			Assert::AreEqual(expString, str, L"Test 7 Failed: Underscore variables failed.");
		}

		TEST_METHOD(Test8_StringContainsOctalNumbers) { //Строка содержит восьмеричные числа
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0127 1 +", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "0127 1 +";
			Assert::AreEqual(expString, str, L"Test 8 Failed: Octal numbers failed.");
		}

		TEST_METHOD(Test9_StringContainsHexadecimalNumbers) { //Строка содержит шестнадцатеричные числа
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0x12AB 1 +", errors);
			std::string str = tree->getRpnOfTree();

			std::string expString = "0x12AB 1 +";
			Assert::AreEqual(expString, str, L"Test 9 Failed: Hexadecimal numbers failed.");
		}
	};
}
