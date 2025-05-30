#pragma once
#include <string>

enum ErrorType { inFileNotExist, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    /// @brief Тип ошибки
    ErrorType type;
    /// @brief Поле для хранения пути, откуда не удалось прочитать файл
    std::string errorInputFilePath; 
    /// @brief Строка, содержащая ошибку
    std::string strWithError; 
    /// @brief Позиция ошибки
    int position; 

    /*!
    * Конструктор для входных параметров с типом ошибки и ее описанием
    * \param[in] _type - тип ошибки
    * \param[in] _strWithError - строка, содержащая ошибку
    * \param[in] _position - позиция ошибки
    */
    Error(ErrorType _type, std::string _strWithError, int _position) :
        type(_type), strWithError(_strWithError), position(_position) {}

    bool operator<(const Error& other) const;
    bool operator==(const Error& other) const;

    /*!
    * Возвращает описание ошибки
    * \return – строка с описанием ошибки
    */
    std::string generateErrorMessage() const;
};