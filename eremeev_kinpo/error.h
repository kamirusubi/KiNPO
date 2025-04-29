#pragma once
#include <string>

enum ErrorType { inFileNotExist, outFileCreateFail, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    ErrorType type; //тип ошибки
    std::string errorInputFilePath; //поле для хранения пути, откуда не удалось прочитать файл
    std::string errorOutputFilePath; //поле для хранения пути, куда не удалось записать файл
    std::string strWithError; // строка, содержащая ошибку
    int position;

    //Конструктор для входных параметров с типом ошибки и ее описанием
    Error(ErrorType _type, std::string _strWithError, int _position) :
        type(_type), strWithError(_strWithError), position(_position) {}

    /*!
    * \Возвращает описание ошибки
    * \this – ошибка
    * \return – строка с описанием ошибки
    */
    std::string generateErrorMessage() const;
};