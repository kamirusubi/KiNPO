#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestIsOperand)
	{
	public:

		TEST_METHOD(Test1_AllDigits) { // Все символы - цифры
			Assert::IsTrue(isOperand("1234"), L"Test 1 Failed: All digits should be true.");
		}

		TEST_METHOD(Test2_StartsWithZero_LessThan8) { // Строка начинается с «0» cо всеми цифрами меньше 8
			Assert::IsTrue(isOperand("01234"), L"Test 2 Failed: Starts with '0' and digits less than 8 should be true.");
		}

		TEST_METHOD(Test3_StartsWithZero_GreaterThan7) { // Строка начинается с «0» c использованием цифр больше 7
			Assert::IsFalse(isOperand("01238"), L"Test 3 Failed: Starts with '0' and contains digit greater than 7 should be false.");
		}

		TEST_METHOD(Test4_HexNumber_NoLetters) { // Строка является шестнадцатеричным числом без использования букв
			Assert::IsTrue(isOperand("0x1234"), L"Test 4 Failed: Hex number without letters should be true.");
		}

		TEST_METHOD(Test5_HexNumber_ValidLetters) {//Строка начинается с «0x» с использованием допустимых букв
			Assert::IsTrue(isOperand("0xABCD"), L"Test 5 Failed: Hex number with valid letters should be true.");
		}

		TEST_METHOD(Test6_HexNumber_InvalidLetters) { // Строка начинается с «0x» с использованием недопустимых букв
			Assert::IsFalse(isOperand("0xABCZ"), L"Test 6 Failed: Hex number with invalid letters should be false.");
		}

		TEST_METHOD(Test7_StartsWithLetter) { // Строка начинается с буквы
			Assert::IsTrue(isOperand("A1234"), L"Test 7 Failed: Starts with a letter should be true.");
		}

		TEST_METHOD(Test8_StartsWithUnderscore) { // Строка начинается на «_»
			Assert::IsTrue(isOperand("_1234"), L"Test 8 Failed: Starts with underscore should be true.");
		}

		TEST_METHOD(Test9_StartsWithDigit_ContainsLetters) { // Строка начинается с цифры, но содержит буквы
			Assert::IsFalse(isOperand("1a234"), L"Test 9 Failed: Starts with digit and contains letters should be false.");
		}

		TEST_METHOD(Test10_InvalidCharactersInVariable) { // В имени переменной содержатся недопустимые символы
			Assert::IsFalse(isOperand("_12*4/"), L"Test 10 Failed: Invalid characters in variable name should be false.");
		}

		TEST_METHOD(Test11_StartsWithInvalidCharacter) { // Строка начинается с недопустимого символа
			Assert::IsFalse(isOperand("(abc"), L"Test 11 Failed: Starts with invalid character should be false.");
		}

		TEST_METHOD(Test12_InvalidCharactersInNumber) { // В числе недопустимые символы
			Assert::IsFalse(isOperand("12:23"), L"Test 12 Failed: Invalid characters in number should be false.");
		}

	};

}
