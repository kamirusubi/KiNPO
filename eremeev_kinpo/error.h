#pragma once
#include <string>

enum ErrorType { inFileNotExist, outFileCreateFail, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    ErrorType type; //��� ������
    std::string errorInputFilePath; //���� ��� �������� ����, ������ �� ������� ��������� ����
    std::string errorOutputFilePath; //���� ��� �������� ����, ���� �� ������� �������� ����
    std::string strWithError; // ������, ���������� ������
    int position;

    //����������� ��� ������� ���������� � ����� ������ � �� ���������
    Error(ErrorType _type, std::string _strWithError, int _position) :
        type(_type), strWithError(_strWithError), position(_position) {}

    bool operator<(const Error& other) const;

    /*!
    * \���������� �������� ������
    * \this � ������
    * \return � ������ � ��������� ������
    */
    std::string generateErrorMessage() const;
};