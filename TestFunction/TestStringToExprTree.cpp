#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/header.h"
#include "compareTrees.h"
#include "compareErrors.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	TEST_CLASS(TestStringToExprTree)
	{
	public:

		TEST_METHOD(Test1_OneOperation) // Строка содержит одну операцию
		{
			std::string rpnString = "5 x >";
			std::set<Error>& errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expTree(ExprNodeType::Greater, new ExprNode("5"), new ExprNode("x"));
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 1 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());


			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 1 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());

		}
		TEST_METHOD(Test2_NestedOperation) // Строка содержит вложенные операции
		{
			std::string rpnString = "5 x + 7 >=";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expFirstOperand(ExprNodeType::Plus, new ExprNode("5"), new ExprNode("x"));
			ExprNode expTree(ExprNodeType::GreaterEqual, &expFirstOperand, new ExprNode("7"));
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 2 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 2 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test3_UnaryOperation)//Строка содержит унарные операции
		{
			std::string rpnString = "5 ~ x <=";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expFirstOperand(ExprNodeType::UnaryMinus, new ExprNode("5"));
			ExprNode expTree(ExprNodeType::LessEqual, &expFirstOperand, new ExprNode("x"));
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 3 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());


			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 3 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test4_MinusMultiplicationDivisionTest) //Проверка операторов «-», «*», «/»
		{
			std::string rpnString = "5 x - 7 x * /";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expFirstOperand(ExprNodeType::Minus, new ExprNode("5"), new ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Multiplication, new ExprNode("7"), new ExprNode("x"));
			ExprNode expTree(ExprNodeType::Division, &expFirstOperand, &expSecondOperand);
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 4 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 4 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test5_DivRemainderNotLessTest)// Проверка операторов «%», «!», «<»
		{
			std::string rpnString = "5 x % 7 ! <";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expFirstOperand(ExprNodeType::DivRemainder, new ExprNode("5"), new ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Not, new ExprNode("7"));
			ExprNode expTree(ExprNodeType::Less, &expFirstOperand, &expSecondOperand);
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 5 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 5 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test6__Variable) // Строка содержит переменные на «_»
		{
			std::string rpnString = "_123 1 +";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);


			ExprNode expTree(ExprNodeType::Plus, new ExprNode("_123"), new ExprNode("1"));
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 6 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 6 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test7_Integer_8) // Строка содержит восьмеричные числа
		{
			std::string rpnString = "0127 1 +";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expTree(ExprNodeType::Plus, new ExprNode("0127"), new ExprNode("1"));
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 7 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 7 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test8_Integer_16) // Строка содержит шестнадцатеричные числа
		{
			std::string rpnString = "0x12AB 1 +";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expTree(ExprNodeType::Plus, new ExprNode("0x12AB"), new ExprNode("1"));

			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 8 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 8 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test9_OnlyValue) // Строка содержит только значение
		{
			std::string rpnString = "5";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			ExprNode expTree("5");
			std::set <Error> expErrors;

			std::set<std::wstring> compareTreesErrors;
			bool areEqualTrees = compareExprTrees(tree, &expTree, L"", &compareTreesErrors);
			// Собираем все ошибки в одну строку для Assert
			std::wstringstream wss;
			if (!compareTreesErrors.empty()) {
				wss << L"Test 9 Failed: trees are not equal. Errors:\n";
				for (std::wstring error : compareTreesErrors) {
					wss << error;
				}
			}
			Assert::IsTrue(areEqualTrees, wss.str().c_str());

			
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 9 Failed: the error container should be empty. Extra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test10_MissingOperand) // В строке недостаточно операндов для операции
		{
			std::string rpnString = "5 x + >";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			Error expError(ErrorType::missingOperand, ">", 4);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(tree == nullptr, L"Test 10 Failed: the function should return nullptr");


			std::wstringstream wss;
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 10 Failed. \nMissing errors:\n";
				for (Error error : missingErrors) {
					wss << error.generateErrorMessage().c_str();
				}
				wss << L";\nExtra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
			
		}
		TEST_METHOD(Test11_RedundantOperand) // Строка содержит лишний операнд
		{
			std::string rpnString = "5 x 6 >";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			Error expError(ErrorType::redundantOperand, "5", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(tree == nullptr, L"Test 11 Failed: the function should return nullptr");

			std::wstringstream wss;
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 11 Failed. \nMissing errors:\n";
				for (Error error : missingErrors) {
					wss << error.generateErrorMessage().c_str();
				}
				wss << L";\nExtra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());

		}
		TEST_METHOD(Test12_UnknownSymbol) // Строка содержит неизвестный символ
		{
			std::string rpnString = "5 ( >";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			Error expError(ErrorType::unknownSymbol, "(", 2);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(tree == nullptr, L"Test 12 Failed: the function should return nullptr");

			std::wstringstream wss;
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 12 Failed. \nMissing errors:\n";
				for (Error error : missingErrors) {
					wss << error.generateErrorMessage().c_str();
				}
				wss << L";\nExtra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
		TEST_METHOD(Test13_UnknownSymbolCombination) // Строка содержит комбинацию неизвестных символов
		{
			std::string rpnString = "_12*4/";
			std::set<Error> errors = std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, &errors);

			Error expError(ErrorType::unknownSymbol, "_12*4/", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(tree == nullptr, L"Test 13 Failed: the function should return nullptr");

			std::wstringstream wss;
			std::set<Error> missingErrors;
			std::set<Error> extraErrors;
			bool equalErrors = compareErrorSets(expErrors, errors, missingErrors, extraErrors);
			wss.clear();
			if (!equalErrors) {
				wss << L"Test 13 Failed. \nMissing errors:\n";
				for (Error error : missingErrors) {
					wss << error.generateErrorMessage().c_str();
				}
				wss << L";\nExtra errors:\n";
				for (Error error : extraErrors) {
					wss << error.generateErrorMessage().c_str();
				}
			}
			Assert::IsTrue(equalErrors, wss.str().c_str());
		}
	};
}
