#include "error.h"

std::string Error::generateErrorMessage() const {
    std::string message = "";
    switch (type) {
    case ErrorType::inFileNotExist:
        message = "По пути \"" + errorInputFilePath + "\" не удалось получить доступ к файлу с входными данными. Возможно, файл не существует.";
        break;
    case ErrorType::emptyFile:
        message = "Входной файл пуст.";
        break;
    case ErrorType::moreThenOneLineInFile:
        message = "Файл со входными данными содержит лишнюю строку: " + strWithError;
        break;
    case ErrorType::invalidRootOperator:
        message = "Недопустимая корневая операция \"" + strWithError + "\". Программа принимает на вход неравенство.";
        break;
    case ErrorType::unknownSymbol:
        message = "Сочетание символов \"" + strWithError + "\" на позиции " + std::to_string(position) + " не является операцией или операндом.";
        break;
    case ErrorType::missingOperand:
        message = "Синтаксическая ошибка на позиции " + std::to_string(position) + ": недостаточно операндов операции \"" + strWithError + "\"";
        break;
    case ErrorType::redundantOperand:
        message = "Синтаксическая ошибка на позиции " + std::to_string(position) + ": лишний операнд \"" + strWithError + "\"";
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