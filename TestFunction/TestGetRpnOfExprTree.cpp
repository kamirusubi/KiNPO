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
		TEST_METHOD(Test1_RootHasNoChildren) { // �������� ���� �� ����� ��������
			std::string original_str = "x 5 >";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 1 Failed: Root with no children failed.");
		}

		TEST_METHOD(Test2_RootHasChildren) { // �������� ���� ����� ��������
			std::string original_str = "x 5 + 7 <=";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 2 Failed: Root with children failed.");
		}

		TEST_METHOD(Test3_RootIsValue) { // �������� ���� - �������� 
			std::string original_str = "5";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 3 Failed: Root is value failed.");
		}

		TEST_METHOD(Test4_TreeContainsUnaryOperations) { // ������ �������� ������� ��������
			std::string original_str = "x ~ 5 >=";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 4 Failed: Tree with unary operations failed.");
		}

		TEST_METHOD(Test5_CheckMinusMultiplicationDivision) {// �������� ���������� �-�, �*�, �/�
			std::string original_str = "5 x - 7 x * /";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 5 Failed: -, *, / operators check failed.");
		}

		TEST_METHOD(Test6_CheckRemainderNotLess) { // �������� ���������� �%�, �!�, �<�
			std::string original_str = "5 x % 7 ! <";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 6 Failed: %, !, < operators check failed.");
		}

		TEST_METHOD(Test7_StringContainsUnderscoreVariables) { // ������ �������� ���������� �� �_�
			std::string original_str = "_123 1 +";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 7 Failed: Underscore variables failed.");
		}

		TEST_METHOD(Test8_StringContainsOctalNumbers) { //������ �������� ������������ �����
			std::string original_str = "0127 1 +";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 8 Failed: Octal numbers failed.");
		}

		TEST_METHOD(Test9_StringContainsHexadecimalNumbers) { //������ �������� ����������������� �����
			std::string original_str = "0x12AB 1 +";

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(original_str, errors);
			std::string str = tree->getRpnOfTree();

			Assert::AreEqual(original_str, str, L"Test 9 Failed: Hexadecimal numbers failed.");
		}
	};
}
