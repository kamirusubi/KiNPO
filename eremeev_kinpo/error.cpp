#include "error.h"
#include <string>

std::string Error::generateErrorMessage() const {
    std::string message = "";
    switch (type) {
    case ErrorType::inFileNotExist:
        message = "Input file does not exist: ";
        break;
    case ErrorType::outFileCreateFail:
        message = "Failed to create output file: ";
        break;
    case ErrorType::emptyFile:
        message = "File is empty: ";
        break;
    case ErrorType::moreThenOneLineInFile:
        message = "File contains more than one line: ";
        break;
    case ErrorType::invalidRootOperator:
        message = "Invalid root operator: ";
        break;
    case ErrorType::unknownSymbol:
        message = "Unknown symbol: ";
        break;
    case ErrorType::missingOperand:
        message = "Missing operand: ";
        break;
    case ErrorType::redundantOperand:
        message = "Redundant operand: ";
        break;
    default:
        message = "Unknown error: ";
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