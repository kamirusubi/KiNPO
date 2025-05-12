#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestIsOperand)
	{
	public:

		TEST_METHOD(Test1_AllDigits) { // ��� ������� - �����
			Assert::IsTrue(isOperand("1234"), L"Test 1 Failed: All digits should be true.");
		}

		TEST_METHOD(Test2_StartsWithZero_LessThan8) { // ������ ���������� � �0� c� ����� ������� ������ 8
			Assert::IsTrue(isOperand("01234"), L"Test 2 Failed: Starts with '0' and digits less than 8 should be true.");
		}

		TEST_METHOD(Test3_StartsWithZero_GreaterThan7) { // ������ ���������� � �0� c �������������� ���� ������ 7
			Assert::IsFalse(isOperand("01238"), L"Test 3 Failed: Starts with '0' and contains digit greater than 7 should be false.");
		}

		TEST_METHOD(Test4_HexNumber_NoLetters) { // ������ �������� ����������������� ������ ��� ������������� ����
			Assert::IsTrue(isOperand("0x1234"), L"Test 4 Failed: Hex number without letters should be true.");
		}

		TEST_METHOD(Test5_HexNumber_ValidLetters) {//������ ���������� � �0x� � �������������� ���������� ����
			Assert::IsTrue(isOperand("0xABCD"), L"Test 5 Failed: Hex number with valid letters should be true.");
		}

		TEST_METHOD(Test6_HexNumber_InvalidLetters) { // ������ ���������� � �0x� � �������������� ������������ ����
			Assert::IsFalse(isOperand("0xABCZ"), L"Test 6 Failed: Hex number with invalid letters should be false.");
		}

		TEST_METHOD(Test7_StartsWithLetter) { // ������ ���������� � �����
			Assert::IsTrue(isOperand("A1234"), L"Test 7 Failed: Starts with a letter should be true.");
		}

		TEST_METHOD(Test8_StartsWithUnderscore) { // ������ ���������� �� �_�
			Assert::IsTrue(isOperand("_1234"), L"Test 8 Failed: Starts with underscore should be true.");
		}

		TEST_METHOD(Test9_StartsWithDigit_ContainsLetters) { // ������ ���������� � �����, �� �������� �����
			Assert::IsFalse(isOperand("1a234"), L"Test 9 Failed: Starts with digit and contains letters should be false.");
		}

		TEST_METHOD(Test10_InvalidCharactersInVariable) { // � ����� ���������� ���������� ������������ �������
			Assert::IsFalse(isOperand("_12*4/"), L"Test 10 Failed: Invalid characters in variable name should be false.");
		}

		TEST_METHOD(Test11_StartsWithInvalidCharacter) { // ������ ���������� � ������������� �������
			Assert::IsFalse(isOperand("(abc"), L"Test 11 Failed: Starts with invalid character should be false.");
		}

		TEST_METHOD(Test12_InvalidCharactersInNumber) { // � ����� ������������ �������
			Assert::IsFalse(isOperand("12:23"), L"Test 12 Failed: Invalid characters in number should be false.");
		}

	};

}
