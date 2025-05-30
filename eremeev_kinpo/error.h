#pragma once
#include <string>

enum ErrorType { inFileNotExist, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    /// @brief ��� ������
    ErrorType type;
    /// @brief ���� ��� �������� ����, ������ �� ������� ��������� ����
    std::string errorInputFilePath; 
    /// @brief ������, ���������� ������
    std::string strWithError; 
    /// @brief ������� ������
    int position; 

    /*!
    * ����������� ��� ������� ���������� � ����� ������ � �� ���������
    * \param[in] _type - ��� ������
    * \param[in] _strWithError - ������, ���������� ������
    * \param[in] _position - ������� ������
    */
    Error(ErrorType _type, std::string _strWithError, int _position) :
        type(_type), strWithError(_strWithError), position(_position) {}

    bool operator<(const Error& other) const;
    bool operator==(const Error& other) const;

    /*!
    * ���������� �������� ������
    * \return � ������ � ��������� ������
    */
    std::string generateErrorMessage() const;
};