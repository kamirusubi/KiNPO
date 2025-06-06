#include "pch.h"
#include "CppUnitTest.h"
#include "../eremeev_kinpo/error.cpp"
#include "../eremeev_kinpo/exprNode.cpp"
#include "../eremeev_kinpo/header.h"
//����� �� ��������� ������� ������� � ��������� cpp �����
//��������������� ������� ��������� ��������, ����� � ���������� ����������� ���� �� ���� (* -> + x), ��� ����������� �������� ������ "�� ���� .... ��������� .... �������� ...."
//�������� ������� ��������� set ������ ����� ������� ����������� https://stackoverflow.com/questions/283977/c-stl-set-difference
//��� TestGetRpnOfExprTree ������� ����������� ������ � ���������� � ���� ���������� � ���
// ��� expErrors=nullptr �������� �������� errors==expErrors �� errors==nullptr
// ���������� �������� � expTree = nullptr
// � ������ �������� ������� getRpnOfTree, ���� N � �� M
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestFunctions
{
	bool compareExprTrees(const ExprNode* expTree, const ExprNode* tree) {
		bool flag = true;
		// ���� ��� ���� nullptr, ������� ��������� (������� ������)
		if (expTree == nullptr && tree == nullptr) {
			return true;
		}

		// ���� ���� �� ����� nullptr, � ������ ���, ������� ������
		if ((expTree == nullptr && tree != nullptr) || (expTree != nullptr && tree == nullptr)) {
			flag = false && flag;
		}

		// ��������� ����� �����
		if (expTree->type != tree->type) {
			flag = false && flag;
		}

		// ��������� �������� (������ ��� ���������)
		if (expTree->type == ExprNodeType::Operand && expTree->value != tree->value) {
			flag = false && flag;
		}

		// ����������� ��������� ���������
		if (!compareExprTrees(expTree->firstOperand, tree->firstOperand)) {
			flag = false && flag;
		}
		if (!compareExprTrees(expTree->secondOperand, tree->secondOperand)) {
			flag = false && flag;
		}

		// ���� ��� �������� ��������, ������� ���������
		return flag;
	}
	TEST_CLASS(TestStringToExprTree)
	{
	public:

		TEST_METHOD(Test1_OneOperation) // ������ �������� ���� ��������
		{
			std::string rpnString = "5 x >";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expTree(ExprNodeType::Greater, new ExprNode("5"), new ExprNode("x"));
			std::set <Error> expErrors;

			std::string errorMessage = "Test 1 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 1 Failed: the error container should be empty");
		}
		TEST_METHOD(Test2_NestedOperation) // ������ �������� ��������� ��������
		{
			std::string rpnString = "5 x + 7 >=";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expFirstOperand(ExprNodeType::Plus, new ExprNode("5"), new ExprNode("x"));
			ExprNode expTree(ExprNodeType::GreaterEqual, &expFirstOperand, new ExprNode("7"));
			std::set <Error> expErrors;

			std::string errorMessage = "Test 2 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 2 Failed: the error container should be empty");
		}
		TEST_METHOD(Test3_UnaryOperation)//������ �������� ������� ��������
		{
			std::string rpnString = "5 ~ x <=";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expFirstOperand(ExprNodeType::UnaryMinus, new ExprNode("5"));
			ExprNode expTree(ExprNodeType::LessEqual, &expFirstOperand, new ExprNode("x"));
			std::set <Error> expErrors;

			std::string errorMessage = "Test 3 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 3 Failed: the error container should be empty");
		}
		TEST_METHOD(Test4_MinusMultiplicationDivisionTest) //�������� ���������� �-�, �*�, �/�
		{
			std::string rpnString = "5 x - 7 x * /";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expFirstOperand(ExprNodeType::Minus, new ExprNode("5"), new ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Multiplication, new ExprNode("7"), new ExprNode("x"));
			ExprNode expTree(ExprNodeType::Division, &expFirstOperand, &expSecondOperand);
			std::set <Error> expErrors;

			std::string errorMessage = "Test 4 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 4 Failed: the error container should be empty");
		}
		TEST_METHOD(Test5_DivRemainderNotLessTest)// �������� ���������� �%�, �!�, �<�
		{
			std::string rpnString = "5 x % 7 ! <";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expFirstOperand(ExprNodeType::DivRemainder, new ExprNode("5"), new ExprNode("x"));
			ExprNode expSecondOperand(ExprNodeType::Not, new ExprNode("7"));
			ExprNode expTree(ExprNodeType::Less, &expFirstOperand, &expSecondOperand);
			std::set <Error> expErrors;

			std::string errorMessage = "Test 5 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 5 Failed: the error container should be empty");
		}
		TEST_METHOD(Test6__Variable) // ������ �������� ���������� �� �_�
		{
			std::string rpnString = "_123 1 +";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);


			ExprNode expTree(ExprNodeType::Plus, new ExprNode("_123"), new ExprNode("1"));
			std::set <Error> expErrors;

			std::string errorMessage = "Test 6 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 6 Failed: the error container should be empty");
		}
		TEST_METHOD(Test7_Integer_8) // ������ �������� ������������ �����
		{
			std::string rpnString = "0127 1 +";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expTree(ExprNodeType::Plus, new ExprNode("0127"), new ExprNode("1"));
			std::set <Error> expErrors;

			std::string errorMessage = "Test 7 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 7 Failed: the error container should be empty");
		}
		TEST_METHOD(Test8_Integer_16) // ������ �������� ����������������� �����
		{
			std::string rpnString = "0x12AB 1 +";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expTree(ExprNodeType::Plus, new ExprNode("0x12AB"), new ExprNode("1"));

			std::set <Error> expErrors;

			std::string errorMessage = "Test 8 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 8 Failed: the error container should be empty");
		}
		TEST_METHOD(Test9_OnlyValue) // ������ �������� ������ ��������
		{
			std::string rpnString = "5";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode expTree("5");
			std::set <Error> expErrors;

			std::string errorMessage = "Test 9 Failed. Expected: " + expTree.getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(&expTree, tree), wideErrorMessage.c_str());
			Assert::IsTrue(expErrors == *errors, L"Test 9 Failed: the error container should be empty");
		}
		TEST_METHOD(Test10_MissingOperand) // � ������ ������������ ��������� ��� ��������
		{
			std::string rpnString = "5 x + >";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode* expTree = nullptr;
			Error expError(ErrorType::missingOperand, ">", 4);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"Test 10 Failed: the function should return nullptr");
			Assert::IsTrue(expErrors == *errors, L"Test 10 Failed: the error container should have one error about an missing operand");
		}
		TEST_METHOD(Test11_RedundantOperand) // ������ �������� ������ �������
		{
			std::string rpnString = "5 x 6 >";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode* expTree = nullptr;
			Error expError(ErrorType::redundantOperand, "5", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"Test 11 Failed: the function should return nullptr");
			Assert::IsTrue(expErrors == *errors, L"Test 11 Failed: the error container should have one error about an redundant operand");
		}
		TEST_METHOD(Test12_UnknownSymbol) // ������ �������� ����������� ������
		{
			std::string rpnString = "5 ( >";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode* expTree = nullptr;
			Error expError(ErrorType::unknownSymbol, "(", 2);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"Test 12 Failed: the function should return nullptr");
			Assert::IsTrue(expErrors == *errors, L"Test 12 Failed: the error container should have one error about an unknown symbol");

		}
		TEST_METHOD(Test13_UnknownSymbolCombination) // ������ �������� ���������� ����������� ��������
		{
			std::string rpnString = "_12*4/";
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree(rpnString, errors);

			ExprNode* expTree = nullptr;
			Error expError(ErrorType::unknownSymbol, "_12*4/", 1);
			std::set <Error> expErrors;
			expErrors.insert(expError);

			Assert::IsTrue(compareExprTrees(expTree, tree), L"Test 13 Failed: the function should return nullptr");
			Assert::IsTrue(expErrors == *errors, L"Test 13 Failed: the error container should have one error about an unknown symbol");
		}
	};

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

	TEST_CLASS(TestCheckTestRootOperation)
	{
	public:

		TEST_METHOD(Test1_RootIsPlus) { // �������� �������� - �+�
			Assert::IsFalse(checkRootOperator(ExprNodeType::Plus), L"Test 1 Failed: Root operation '+' should be false.");
		}

		TEST_METHOD(Test2_RootIsMinus) {// �������� �������� - �-�
			Assert::IsFalse(checkRootOperator(ExprNodeType::Minus), L"Test 2 Failed: Root operation '-' should be false.");
		}

		TEST_METHOD(Test3_RootIsDivision) { // �������� �������� - �/�
			Assert::IsFalse(checkRootOperator(ExprNodeType::Division), L"Test 3 Failed: Root operation '/' should be false.");
		}

		TEST_METHOD(Test4_RootIsMultiplication) { // �������� �������� - �*�
			Assert::IsFalse(checkRootOperator(ExprNodeType::Multiplication), L"Test 4 Failed: Root operation '*' should be false.");
		}

		TEST_METHOD(Test5_RootIsDivRemainder) { // �������� �������� - �%�
			Assert::IsFalse(checkRootOperator(ExprNodeType::DivRemainder), L"Test 5 Failed: Root operation '%' should be false.");
		}

		TEST_METHOD(Test6_RootIsUnaryMinus) { // �������� �������� - �~�
			Assert::IsFalse(checkRootOperator(ExprNodeType::UnaryMinus), L"Test 6 Failed: Root operation '~' should be false.");
		}

		TEST_METHOD(Test7_RootIsNot) { // �������� �������� - �!�
			Assert::IsFalse(checkRootOperator(ExprNodeType::Not), L"Test 7 Failed: Root operation '!' should be false.");
		}

		TEST_METHOD(Test8_RootIsGreaterEqual) { // �������� �������� - �>=�
			Assert::IsTrue(checkRootOperator(ExprNodeType::GreaterEqual), L"Test 8 Failed: Root operation '>=' should be true.");
		}

		TEST_METHOD(Test9_RootIsLessEqual) { // �������� �������� - �<=�
			Assert::IsTrue(checkRootOperator(ExprNodeType::LessEqual), L"Test 9 Failed: Root operation '<=' should be true.");
		}

		TEST_METHOD(Test10_RootIsGreater) { // �������� �������� - �>�
			Assert::IsTrue(checkRootOperator(ExprNodeType::Greater), L"Test 10 Failed: Root operation '>' should be true.");
		}

		TEST_METHOD(Test11_RootIsLess) { // �������� �������� - �<�
			Assert::IsTrue(checkRootOperator(ExprNodeType::Less), L"Test 11 Failed: Root operation '<' should be true.");
		}

		TEST_METHOD(Test12_RootIsOperand) { // �������� �������� - �������
			Assert::IsFalse(checkRootOperator(ExprNodeType::Operand), L"Test 12 Failed: Root operation is Operand should be false.");
		}

	};

	TEST_CLASS(TestTransformInequalityToLessOperator)
	{
	public:
		TEST_METHOD(Test1_CurrentIsLess) { // ������� �������� � �������

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x <", errors);

			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
		TEST_METHOD(Test2_CurrentIsLessEqual) { // ������� �������� � ������� ��� �����
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("x 5 < !", errors);

			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
		TEST_METHOD(Test3_CurrentIsGreater) { // ������� �������� � �������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + x + 7 >", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("7 5 x + x + <", errors);

			std::string errorMessage = "Test 3 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
		TEST_METHOD(Test4_CurrentIsGreaterEqual) { // ������� �������� � ������� ��� �����
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x >=", errors);
			transformInequalityToLessOperator(tree);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);

			std::string errorMessage = "Test 4 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
	};

	TEST_CLASS(TestSwapOperands)
	{
	public:
		TEST_METHOD(Test1_OperandsAreNotNodes) { // �������� �������� ����������

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->swapOperands();

			ExprNode* expTree = stringToExprTree("x 5 <", errors);

			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
		TEST_METHOD(Test2_OperandsAreNodes) { // �������� �������� ����

			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x + 7 <", errors);
			tree->swapOperands();

			ExprNode* expTree = stringToExprTree("7 5 x + <", errors);

			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
	};

	TEST_CLASS(TestAddUnaryOperatorBefore)
	{
	public:
		TEST_METHOD(Test1_CurrentIsValue) { // ������� ���� - ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 !", errors);

			std::string errorMessage = "Test 1 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}

		TEST_METHOD(Test2_CurrentIsOperation) { // ������� ���� - ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x < !", errors);

			std::string errorMessage = "Test 2 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}

		TEST_METHOD(Test3_CurrentIsIntermediate) { // ������� ���� - �������������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x <", errors);
			tree->secondOperand->addUnaryOperatorBefore(ExprNodeType::Not);

			ExprNode* expTree = stringToExprTree("5 x ! <", errors);

			std::string errorMessage = "Test 3 Failed. Expected: " + expTree->getRpmOfTree() + "; Actual: " + tree->getRpmOfTree();
			std::wstring wideErrorMessage(errorMessage.begin(), errorMessage.end());

			Assert::IsTrue(compareExprTrees(expTree, tree), wideErrorMessage.c_str());
		}
	};
	TEST_CLASS(TestGetRpnOfExprTree)
	{
	public:
		TEST_METHOD(Test1_RootHasNoChildren) { // �������� ���� �� ����� ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 >", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x 5 >";
			Assert::AreEqual(expString, str, L"Test 1 Failed: Root with no children failed.");
		}

		TEST_METHOD(Test2_RootHasChildren) { // �������� ���� ����� ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x 5 + 7 <=", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x 5 + 7 <=";
			Assert::AreEqual(expString, str, L"Test 2 Failed: Root with children failed.");
		}

		TEST_METHOD(Test3_RootIsValue) { // �������� ���� - �������� 
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5";
			Assert::AreEqual(expString, str, L"Test 3 Failed: Root is value failed.");
		}

		TEST_METHOD(Test4_TreeContainsUnaryOperations) { // ������ �������� ������� ��������
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("x ~ 5 >=", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "x ~ 5 >=";
			Assert::AreEqual(expString, str, L"Test 4 Failed: Tree with unary operations failed.");
		}

		TEST_METHOD(Test5_CheckMinusMultiplicationDivision) {// �������� ���������� �-�, �*�, �/�
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x - 7 x * /", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5 x - 7 x * /";
			Assert::AreEqual(expString, str, L"Test 5 Failed: -, *, / operators check failed.");
		}

		TEST_METHOD(Test6_CheckRemainderNotLess) { // �������� ���������� �%�, �!�, �<�
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("5 x % 7 ! <", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "5 x % 7 ! <";
			Assert::AreEqual(expString, str, L"Test 6 Failed: %, !, < operators check failed.");
		}

		TEST_METHOD(Test7_StringContainsUnderscoreVariables) { // ������ �������� ���������� �� �_�
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("_123 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "_123 1 +";
			Assert::AreEqual(expString, str, L"Test 7 Failed: Underscore variables failed.");
		}

		TEST_METHOD(Test8_StringContainsOctalNumbers) { //������ �������� ������������ �����
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0127 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "0127 1 +";
			Assert::AreEqual(expString, str, L"Test 8 Failed: Octal numbers failed.");
		}

		TEST_METHOD(Test9_StringContainsHexadecimalNumbers) { //������ �������� ����������������� �����
			std::set<Error>* errors = new std::set<Error>();
			ExprNode* tree = stringToExprTree("0x12AB 1 +", errors);
			std::string str = tree->getRpmOfTree();

			std::string expString = "0x12AB 1 +";
			Assert::AreEqual(expString, str, L"Test 9 Failed: Hexadecimal numbers failed.");
		}
	};
}
