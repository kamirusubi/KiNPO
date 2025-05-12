#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestCheckTestRootOperation)
	{
	public:

		TEST_METHOD(Test1_RootIsPlus) { // Корневая операция - «+»
			Assert::IsFalse(checkRootOperator(ExprNodeType::Plus), L"Test 1 Failed: Root operation '+' should be false.");
		}

		TEST_METHOD(Test2_RootIsMinus) {// Корневая операция - «-»
			Assert::IsFalse(checkRootOperator(ExprNodeType::Minus), L"Test 2 Failed: Root operation '-' should be false.");
		}

		TEST_METHOD(Test3_RootIsDivision) { // Корневая операция - «/»
			Assert::IsFalse(checkRootOperator(ExprNodeType::Division), L"Test 3 Failed: Root operation '/' should be false.");
		}

		TEST_METHOD(Test4_RootIsMultiplication) { // Корневая операция - «*»
			Assert::IsFalse(checkRootOperator(ExprNodeType::Multiplication), L"Test 4 Failed: Root operation '*' should be false.");
		}

		TEST_METHOD(Test5_RootIsDivRemainder) { // Корневая операция - «%»
			Assert::IsFalse(checkRootOperator(ExprNodeType::DivRemainder), L"Test 5 Failed: Root operation '%' should be false.");
		}

		TEST_METHOD(Test6_RootIsUnaryMinus) { // Корневая операция - «~»
			Assert::IsFalse(checkRootOperator(ExprNodeType::UnaryMinus), L"Test 6 Failed: Root operation '~' should be false.");
		}

		TEST_METHOD(Test7_RootIsNot) { // Корневая операция - «!»
			Assert::IsFalse(checkRootOperator(ExprNodeType::Not), L"Test 7 Failed: Root operation '!' should be false.");
		}

		TEST_METHOD(Test8_RootIsGreaterEqual) { // Корневая операция - «>=»
			Assert::IsTrue(checkRootOperator(ExprNodeType::GreaterEqual), L"Test 8 Failed: Root operation '>=' should be true.");
		}

		TEST_METHOD(Test9_RootIsLessEqual) { // Корневая операция - «<=»
			Assert::IsTrue(checkRootOperator(ExprNodeType::LessEqual), L"Test 9 Failed: Root operation '<=' should be true.");
		}

		TEST_METHOD(Test10_RootIsGreater) { // Корневая операция - «>»
			Assert::IsTrue(checkRootOperator(ExprNodeType::Greater), L"Test 10 Failed: Root operation '>' should be true.");
		}

		TEST_METHOD(Test11_RootIsLess) { // Корневая операция - «<»
			Assert::IsTrue(checkRootOperator(ExprNodeType::Less), L"Test 11 Failed: Root operation '<' should be true.");
		}

		TEST_METHOD(Test12_RootIsOperand) { // Корневая операция - операнд
			Assert::IsFalse(checkRootOperator(ExprNodeType::Operand), L"Test 12 Failed: Root operation is Operand should be false.");
		}

	};

}
