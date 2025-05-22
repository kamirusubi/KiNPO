#include "error.h"

std::string Error::generateErrorMessage() const {
    std::string message = "";
    switch (type) {
    case ErrorType::inFileNotExist:
        message = "Input file does not exist on path " + errorInputFilePath;
        break;
    case ErrorType::outFileCreateFail:
        message = "Failed to create output file on path " + errorOutputFilePath;
        break;
    case ErrorType::emptyFile:
        message = "File is empty: ";
        break;
    case ErrorType::moreThenOneLineInFile:
        message = "File contains extra line: " + strWithError;
        break;
    case ErrorType::invalidRootOperator:
        message = "Invalid root operator \"" + strWithError + "\"";
        break;
    case ErrorType::unknownSymbol:
        message = "Unknown symbol \"" + strWithError + "\" on position " + std::to_string(position);
        break;
    case ErrorType::missingOperand:
        message = "Missing operand \"" + strWithError + "\" on position " + std::to_string(position);
        break;
    case ErrorType::redundantOperand:
        message = "Redundant operand \"" + strWithError + "\" on position " + std::to_string(position);
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