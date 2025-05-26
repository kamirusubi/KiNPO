#include "error.h"

std::string Error::generateErrorMessage() const {
    std::string message = "";
    switch (type) {
    case ErrorType::inFileNotExist:
        message = "�� ���� \"" + errorInputFilePath + "\" �� ������� �������� ������ � ����� � �������� �������. ��������, ���� �� ����������.";
        break;
    case ErrorType::emptyFile:
        message = "������� ���� ����.";
        break;
    case ErrorType::moreThenOneLineInFile:
        message = "���� �� �������� ������� �������� ������ ������: " + strWithError;
        break;
    case ErrorType::invalidRootOperator:
        message = "������������ �������� �������� \"" + strWithError + "\". ��������� ��������� �� ���� �����������.";
        break;
    case ErrorType::unknownSymbol:
        message = "��������� �������� \"" + strWithError + "\" �� ������� " + std::to_string(position) + " �� �������� ��������� ��� ���������.";
        break;
    case ErrorType::missingOperand:
        message = "�������������� ������ �� ������� " + std::to_string(position) + ": ������������ ��������� �������� \"" + strWithError + "\"";
        break;
    case ErrorType::redundantOperand:
        message = "�������������� ������ �� ������� " + std::to_string(position) + ": ������ ������� \"" + strWithError + "\"";
        break;
    default:
        message = "";
    }
    return message;
}

bool Error::operator<(const Error& other) const {
    if (type != other.type) {
        return type < other.type;
    }
    if (strWithError != other.strWithError) {
        return strWithError < other.strWithError;
    }
    if (position != other.position) {
        return position < other.position;
    }
    if (!errorInputFilePath.empty() && !other.errorInputFilePath.empty()) {
        if (errorInputFilePath != other.errorInputFilePath)
        {
            return errorInputFilePath < other.errorInputFilePath;
        }
    }
    else if (!errorInputFilePath.empty() && other.errorInputFilePath.empty())
    {
        return false;
    }
    else if (errorInputFilePath.empty() && !other.errorInputFilePath.empty())
    {
        return true;
    }

    if (!errorOutputFilePath.empty() && !other.errorOutputFilePath.empty())
    {
        if (errorOutputFilePath != other.errorOutputFilePath)
        {
            return errorOutputFilePath < other.errorOutputFilePath;
        }
    }
    else if (!errorOutputFilePath.empty() && other.errorOutputFilePath.empty())
    {
        return false;
    }
    else if (errorOutputFilePath.empty() && !other.errorOutputFilePath.empty())
    {
        return true;
    }

    return false;
}

bool Error::operator==(const Error& other) const {
    return type == other.type &&
        errorInputFilePath == other.errorInputFilePath &&
        errorOutputFilePath == other.errorOutputFilePath &&
        strWithError == other.strWithError &&
        position == other.position;

}