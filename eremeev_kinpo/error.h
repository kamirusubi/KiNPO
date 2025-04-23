#pragma once
#include <string>

enum ErrorType { inFileNotExist, outFileCreateFail, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    ErrorType type; //��� ������
    std::string errorInputFilePath; //���� ��� �������� ����, ������ �� ������� ��������� ����
    std::string errorOutputFilePath; //���� ��� �������� ����, ���� �� ������� �������� ����
    std::string strWithError; // ������, ���������� ������

    /*!
    * \���������� �������� ������
    * \this � ������
    * \return � ������ � ��������� ������
    */
    std::string generateErrorMessage() const;
};