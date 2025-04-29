#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/error.cpp"
#include "../eremeev_kinpo/exprNode.cpp"
#include "../eremeev_kinpo/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	bool compareExprTrees(const ExprNode* expTree, const ExprNode* tree) {
		// ≈сли оба узла nullptr, деревь€ одинаковы (базовый случай)
		if (expTree == nullptr && tree == nullptr) {
			return true;
		}

		// ≈сли один из узлов nullptr, а другой нет, деревь€ разные
		if ((expTree == nullptr && tree != nullptr) || (expTree != nullptr && tree == nullptr)) {
			return false;
		}

		// —равнение типов узлов
		if (expTree->type != tree->type) {
			return false;
		}

		// —равнение значений (только дл€ операндов)
		if (expTree->type == ExprNodeType::Operand && expTree->value != tree->value) {
			return false;
		}

		// –екурсивное сравнение операндов
		if (!compareExprTrees(expTree->firstOperand, tree->firstOperand)) {
			return false;
		}
		if (!compareExprTrees(expTree->secondOperand, tree->secondOperand)) {
			return false;
		}

		// ≈сли все проверки пройдены, деревь€ одинаковы
		return true;
	}
	TEST_CLASS(TestStringToExprTree)
	{
	public:

		TEST_METHOD(Test1_OneOperation)
		{
			std::string rpnString = "5 x >";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expTree(ExprNodeType::Greater, &ExprNode("5"), &ExprNode("x"));

			std::set <Error> expErrors;
			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test2_NestedOperation)
		{
			std::string rpnString = "5 x + 7 >=";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expFirstOperand(ExprNodeType::Plus, &ExprNode("5"), &ExprNode("x"));
			ExprNode expTree(ExprNodeType::GreaterEqual, &expFirstOperand, &ExprNode("7"));

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test3_UnaryOperation)
		{
			std::string rpnString = "5 ~ x <=";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expFirstOperand(ExprNodeType::UnaryMinus, &ExprNode("x"));
			ExprNode expTree(ExprNodeType::GreaterEqual, &expFirstOperand, &ExprNode("x"));

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test4_MinusMultiplicationDivisionTest)
		{
			std::string rpnString = "5 x - 7 x * /";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expFirstOperand(ExprNodeType::Minus, &ExprNode("5"), &ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Multiplication, &ExprNode("7"), &ExprNode("x"));

			ExprNode expTree(ExprNodeType::Division, &expFirstOperand, &expSecondOperand);

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test5_DivRemainderNotLessTest)
		{
			std::string rpnString = "5 x % 7 ! <";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);
						


			ExprNode expFirstOperand(ExprNodeType::DivRemainder, &ExprNode("5"), &ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Not, &ExprNode("7"));

			ExprNode expTree(ExprNodeType::Less, &expFirstOperand, &expSecondOperand);

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test6__Variable)
		{
			std::string rpnString = "_123 1 +";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expTree(ExprNodeType::Plus, &ExprNode("_123"), &ExprNode("1"));


			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test7_Integer_8)
		{
			std::string rpnString = "0127 1 +";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expTree(ExprNodeType::Plus, &ExprNode("0127"), &ExprNode("1"));


			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test8_Integer_16)
		{
			std::string rpnString = "0x12AB 1 +";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expTree(ExprNodeType::Plus, &ExprNode("0x12AB"), &ExprNode("1"));

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test9_OnlyValue)
		{
			std::string rpnString = "5";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expTree("5");

			std::set <Error> expErrors;

			Assert::IsTrue(compareExprTrees(&expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test10_MissingOperand)
		{
			std::string rpnString = "5 x + >";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);



			ExprNode* expTree = nullptr;

			Error expError(ErrorType::missingOperand, ">", 4);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test11_EdundantOperand)
		{
			std::string rpnString = "5 x 6 >";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);



			ExprNode* expTree = nullptr;

			Error expError(ErrorType::redundantOperand, "5", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test12_UnknownSymbol)
		{
			std::string rpnString = "5 ( >";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);



			ExprNode* expTree = nullptr;

			Error expError(ErrorType::unknownSymbol, "(", 2);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
		TEST_METHOD(Test13_UnknownSymbolCombination)
		{
			std::string rpnString = "_12*4/";
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);



			ExprNode* expTree = nullptr;

			Error expError(ErrorType::unknownSymbol, "_12*4/", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
			Assert::AreEqual((size_t)expErrors.size(), errors->size(), L"");
		}
	};

	TEST_CLASS(TestIsOperand)
	{
	public:

		TEST_METHOD(Test1_AllDigits) {
			Assert::IsTrue(isOperand("1234"), L"Test 1 Failed: All digits should be true.");
		}

		TEST_METHOD(Test2_StartsWithZero_LessThan8) {
			Assert::IsTrue(isOperand("01234"), L"Test 2 Failed: Starts with '0' and digits less than 8 should be true.");
		}

		TEST_METHOD(Test3_StartsWithZero_GreaterThan7) {
			Assert::IsFalse(isOperand("01238"), L"Test 3 Failed: Starts with '0' and contains digit greater than 7 should be false.");
		}

		TEST_METHOD(Test4_HexNumber_NoLetters) {
			Assert::IsTrue(isOperand("0x1234"), L"Test 4 Failed: Hex number without letters should be true.");
		}

		TEST_METHOD(Test5_HexNumber_ValidLetters) {
			Assert::IsTrue(isOperand("0xABCD"), L"Test 5 Failed: Hex number with valid letters should be true.");
		}

		TEST_METHOD(Test6_HexNumber_InvalidLetters) {
			Assert::IsFalse(isOperand("0xABCZ"), L"Test 6 Failed: Hex number with invalid letters should be false.");
		}

		TEST_METHOD(Test7_StartsWithLetter) {
			Assert::IsTrue(isOperand("A1234"), L"Test 7 Failed: Starts with a letter should be true.");
		}

		TEST_METHOD(Test8_StartsWithUnderscore) {
			Assert::IsTrue(isOperand("_1234"), L"Test 8 Failed: Starts with underscore should be true.");
		}

		TEST_METHOD(Test9_StartsWithDigit_ContainsLetters) {
			Assert::IsFalse(isOperand("1a234"), L"Test 9 Failed: Starts with digit and contains letters should be false.");
		}

		TEST_METHOD(Test10_InvalidCharactersInVariable) {
			Assert::IsFalse(isOperand("_12*4/"), L"Test 10 Failed: Invalid characters in variable name should be false.");
		}

		TEST_METHOD(Test11_StartsWithInvalidCharacter) {
			Assert::IsFalse(isOperand("(abc"), L"Test 11 Failed: Starts with invalid character should be false.");
		}

		TEST_METHOD(Test12_InvalidCharactersInNumber) {
			Assert::IsFalse(isOperand("12:23"), L"Test 12 Failed: Invalid characters in number should be false.");
		}

	};

	TEST_CLASS(TestCheckTestRootOperation)
	{
	public:

		TEST_METHOD(Test1_RootIsPlus) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Plus), L"Test 1 Failed: Root operation '+' should be false.");
		}

		TEST_METHOD(Test2_RootIsMinus) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Minus), L"Test 2 Failed: Root operation '-' should be false.");
		}

		TEST_METHOD(Test3_RootIsDivision) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Division), L"Test 3 Failed: Root operation '/' should be false.");
		}

		TEST_METHOD(Test4_RootIsMultiplication) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Multiplication), L"Test 4 Failed: Root operation '*' should be false.");
		}

		TEST_METHOD(Test5_RootIsDivRemainder) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::DivRemainder), L"Test 5 Failed: Root operation '%' should be false.");
		}

		TEST_METHOD(Test6_RootIsUnaryMinus) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::UnaryMinus), L"Test 6 Failed: Root operation '~' should be false.");
		}

		TEST_METHOD(Test7_RootIsNot) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Not), L"Test 7 Failed: Root operation '!' should be false.");
		}

		TEST_METHOD(Test8_RootIsGreaterEqual) {
			Assert::IsTrue(checkRootOperator(ExprNodeType::GreaterEqual), L"Test 8 Failed: Root operation '>=' should be true.");
		}

		TEST_METHOD(Test9_RootIsLessEqual) {
			Assert::IsTrue(checkRootOperator(ExprNodeType::LessEqual), L"Test 9 Failed: Root operation '<=' should be true.");
		}

		TEST_METHOD(Test10_RootIsGreater) {
			Assert::IsTrue(checkRootOperator(ExprNodeType::Greater), L"Test 10 Failed: Root operation '>' should be true.");
		}

		TEST_METHOD(Test11_RootIsLess) {
			Assert::IsTrue(checkRootOperator(ExprNodeType::Less), L"Test 11 Failed: Root operation '<' should be true.");
		}

		TEST_METHOD(Test12_RootIsOperand) {
			Assert::IsFalse(checkRootOperator(ExprNodeType::Operand), L"Test 12 Failed: Root operation is Operand should be false.");
		}

	};

	TEST_CLASS(TestTransformInequalityToLessOperator)
	{
	public:
		TEST_METHOD(Test1_CurrentIsLess) {

            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x <", errors);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
		TEST_METHOD(Test2_CurrentIsLessEqual) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("x 5 < !", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
		TEST_METHOD(Test3_CurrentIsGreater) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + x + 7 >", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("7 5 x + x + <", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
		TEST_METHOD(Test4_CurrentIsGreaterEqual) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x >=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
	};

	TEST_CLASS(TestSwapOperands)
	{
	public:
		TEST_METHOD(Test1_OperandsAreNotNodes) {

            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->swapOperands();

			ExprNode* expTree = stringToExprTree("x 5 <", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
		TEST_METHOD(Test2_OperandsAreNodes) {

            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + 7 <", errors);
			tree->swapOperands();

			ExprNode *expTree = stringToExprTree("7 x 5 + <", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
	};

	TEST_CLASS(TestAddUnaryOperatorBefore)
	{
	public:
		TEST_METHOD(Test1_CurrentIsValue) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 !", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}

		TEST_METHOD(Test2_CurrentIsOperation) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}

		TEST_METHOD(Test3_CurrentIsIntermediate) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->secondOperand->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x ! <", errors);
			Assert::IsTrue(compareExprTrees(expTree, tree), L"");
		}
	};
	TEST_CLASS(TestGetRpnOfExprTree)
	{
	public:
		TEST_METHOD(Test1_RootHasNoChildren) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 >", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x 5 >";
			Assert::AreEqual(expString, str, L"Test 1 Failed: Root with no children failed.");
		}

		TEST_METHOD(Test2_RootHasChildren) {

            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 + 7 <=", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x 5 + 7 <=";
			Assert::AreEqual(expString, str, L"Test 2 Failed: Root with children failed.");
		}

		TEST_METHOD(Test3_RootIsValue) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5";
			Assert::AreEqual(expString, str, L"Test 3 Failed: Root is value failed.");
		}

		TEST_METHOD(Test4_TreeContainsUnaryOperations) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x ~ 5 >=", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x ~ 5 >=";
			Assert::AreEqual(expString, str, L"Test 4 Failed: Tree with unary operations failed.");
		}

		TEST_METHOD(Test5_CheckMinusMultiplicationDivision) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x - 7 x * /", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5 x - 7 x * /";
			Assert::AreEqual(expString, str, L"Test 5 Failed: -, *, / operators check failed.");
		}

		TEST_METHOD(Test6_CheckRemainderNotLess) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x % 7 ! <", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5 x % 7 ! <";
			Assert::AreEqual(expString, str, L"Test 6 Failed: %, !, < operators check failed.");
		}

		TEST_METHOD(Test7_StringContainsUnderscoreVariables) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("_123 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "_123 1 +";
			Assert::AreEqual(expString, str, L"Test 7 Failed: Underscore variables failed.");
		}

		TEST_METHOD(Test8_StringContainsOctalNumbers) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0127 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "0127 1 +";
			Assert::AreEqual(expString, str, L"Test 8 Failed: Octal numbers failed.");
		}

		TEST_METHOD(Test9_StringContainsHexadecimalNumbers) {
            std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0x12AB 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "0x12AB 1 +";
			Assert::AreEqual(expString, str, L"Test 9 Failed: Hexadecimal numbers failed.");
		}
	};
}
