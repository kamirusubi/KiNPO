#pragma once
#include <string>

enum ErrorType { inFileNotExist, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    ErrorType type; //тип ошибки
    std::string errorInputFilePath; //поле для хранения пути, откуда не удалось прочитать файл
    std::string strWithError; // строка, содержащая ошибку
    int position; // позиция ошибки

    //Конструктор для входных параметров с типом ошибки и ее описанием
    Error(ErrorType _type, std::string _strWithError, int _position) :
        type(_type), strWithError(_strWithError), position(_position) {}

    bool operator<(const Error& other) const;
    bool operator==(const Error& other) const;
    /*!
    * \Возвращает описание ошибки
    * \this – ошибка
    * \return – строка с описанием ошибки
    */
    std::string generateErrorMessage() const;
};