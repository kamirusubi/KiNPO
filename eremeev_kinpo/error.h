#pragma once
#include <string>

enum ErrorType { inFileNotExist, outFileCreateFail, emptyFile, moreThenOneLineInFile, invalidRootOperator, unknownSymbol, missingOperand, redundantOperand };

class Error {
public:
    ErrorType type; //тип ошибки
    std::string errorInputFilePath; //поле дл€ хранени€ пути, откуда не удалось прочитать файл
    std::string errorOutputFilePath; //поле дл€ хранени€ пути, куда не удалось записать файл
    std::string strWithError; // строка, содержаща€ ошибку

    /*!
    * \¬озвращает описание ошибки
    * \this Ц ошибка
    * \return Ц строка с описанием ошибки
    */
    std::string generateErrorMessage() const;
};