#include <iostream>
#include "header.h"


std::string* readFileToString(const std::string filePath, std::set <Error>* errors) {
    //Открыть файл
    std::ifstream inputFile(filePath);

    //Если не удалось открыть файл
    if (!inputFile.is_open()) {
        // Добавить ошибку о неудаче открыть файл
        Error error(ErrorType::inFileNotExist, "", 0);
        error.errorInputFilePath = filePath;
        errors->insert(error);
    }

    //Иначе
    else {
        std::string line;
        std::vector<std::string> non_empty_lines;

        //Считать непустые строки файла
        while (std::getline(inputFile, line)) {
            if (!line.empty()) {
                non_empty_lines.push_back(line);
            }
        }

        //Закрыть файл
        inputFile.close(); 

        // Если в файле все строки пустые
        if (non_empty_lines.empty()) {
            // Добавить ошибку о пустом входном файле
            Error error(ErrorType::emptyFile, "", 0);
            errors->insert(error);
        }

        // Если в файле больше одной непустой строки
        if (non_empty_lines.size() > 1) {
            // Для каждой лишней непустой строки
            for (size_t i = 1; i < non_empty_lines.size(); ++i) { 
                // Добавить ошибку о том, что в файле содержит лишнюю строку
                Error error(ErrorType::moreThenOneLineInFile, non_empty_lines[i], 0);
                errors->insert(error);
            }
        }

        // Если нет ошибок (только одна непустая строка)
        if (errors->empty()) {
            // Считать содержимое первой непустой строки
            std::string* content = new std::string(non_empty_lines[0]);
            return content;
        }
    }
    
    //Вернуть указатель на пустую строку
    return nullptr;
}


ExprNode* stringToExprTree(std::string rpnString, std::set <Error>* errors) {
    std::stack<ExprNode*> stack; // Стэк с содержимым класса ExprNode
    std::stringstream stream(rpnString); // Поток с выражением в обратной польской записи
    std::string token;
    int position = 0;
    std::map <ExprNode*, int> tokenIndex;// словарь для позиций токенов в исходной строке

    while (stream >> token && errors->empty()) { // Пока в переменную token получается извлечь часть потока и нет ошибок
        position += 1;
        ExprNode* newNode = new ExprNode(); // Создать узел newNode
        
        tokenIndex[newNode] = position;

        // Если token – операнд
        if (isOperand(token)) {
            newNode->setValue(token); // Присвоить полю value newNode значение token
            newNode->setType(ExprNodeType::Operand); // Присвоить полю type newNode значение Operand
        }
        // Если token – символ из словаря symbolToString
        else if (ExprNode::symbolToString.count(token)) {
            newNode->setType(ExprNode::symbolToString.at(token)); // Присвоить значению type newNode словесную запись оператора из словаря symbolToString

            int operandCountNeeded = ExprNode::operandCount.at(newNode->getType()); // Узнать необходимое количество операндов

            // Если в стеке нет нужного количества операндов
            if (stack.size() < operandCountNeeded) {
                errors->insert(Error(ErrorType::missingOperand, token, position)); // Добавить ошибку о недостатке операндов
            }
            // Если нет ошибок
            if (errors->empty()) {
                // Если оператор бинарный
                if (operandCountNeeded == 2) {
                    newNode->setSecondOperand(stack.top()); // Присвоить второму операнду newNode значение верхнего узла из стека
                    stack.pop(); // Удалить из стека верхний узел
                }
                newNode->setFirstOperand(stack.top()); // Присвоить первому операнду newNode значение верхнего узла из стека
                stack.pop(); // Удалить из стека верхний узел
            }
        }
        else {
            errors->insert(Error(ErrorType::unknownSymbol, token, position)); // Добавить ошибку о недопустимом символе
        }
        // Если нет ошибок
        if (errors->empty()) {
            stack.push(newNode); // Поместить newNode в стэк
        }
    }

    if (stack.size() > 1 && errors->empty()) { // Если в стэке больше одного элемента и нет ошибок
        //сохранить верхушку стека
        ExprNode* tree = stack.top();
        stack.pop();

        //для всех неиспользованных операндов
        while (stack.size() > 0)
        {
            ExprNode* redundantOperand = stack.top();
            stack.pop();

            errors->insert(Error(ErrorType::redundantOperand, redundantOperand->getRpnOfTree(), tokenIndex[redundantOperand]));
        }
    }

    // Если нет ошибок
    if (errors->empty() && !stack.empty()) {
        ExprNode* root = stack.top(); // Вернуть верхушку стэка
        stack.pop();
        return root;
    }
    else {
        // Освободить память, выделенную под стэк
        while (!stack.empty()) {
            delete stack.top();
            stack.pop();
        }
        return nullptr;
    }
}


bool isOperand(std::string str) {

    //Если длина str больше 1 и первый символ str - «0» 
    if (str.length() > 1 && str[0] == '0') {
        //Если второй символ str - «X» или «x»
        if (str[1] == 'X' || str[1] == 'x') {
            // Для каждого символа числа
            for (int i = 2; i < str.length(); ++i) {
                // Если символ недопустим в шестнадцатеричном числе
                if (!isxdigit(str[i])) { 
                    return false; // Вернуть false
                }
            }
        }
        // Иначе если второй символ str – число
        else if (isdigit(str[1])) {
            // Восьмеричное число
            for (int i = 1; i < str.length(); ++i) {
                if (!isdigit(str[i]) || str[i] >= '8') {
                    return false; // Недопустимый символ в восьмеричном числе
                }
            }
        }
        else {
            return false;
        }
    }
    // Если первый символ - цифра
    else if (isdigit(str[0])) {
        // Проверить, что остальные символы тоже цифры
        for (int i = 1; i < str.length(); ++i) {
            // Если есть нецифровой символ
            if (!isdigit(str[i])) {
                return false; 
            }
        }
    }
    // Если начинается с буквы или "_"
    else if (isalpha(str[0]) || str[0] == '_') {
        //Для остальных символов
        for (size_t i = 1; i < str.length(); ++i) {
            //Если симвлол - не цифра и не буква
            if (!isalnum(str[i]) && str[i] != '_') {
                return false; // Недопустимый символ
            }
        }
    }
    else {
        //Иначе первый символ недопустим для операнда
        return false; 
    }
    return true;
}


bool checkRootOperator(ExprNodeType _operator) {
    // Контейнер допустимых корневых операторов
    std::set<ExprNodeType> validRootOperators = {
        ExprNodeType::Less,
        ExprNodeType::Greater,
        ExprNodeType::GreaterEqual,
        ExprNodeType::LessEqual
    };
    //Вернуть допустимость корневого оператора
    return validRootOperators.count(_operator) > 0;
}


void transformInequalityToLessOperator(ExprNode* node) {
    // Если корневая операция отличается от “Less”
    if (node->getType() != ExprNodeType::Less) {
        ExprNodeType originalOperator = node->getType(); // Запомнить корневую операцию

        node->setType(ExprNodeType::Less); // Заменить корневую операцию на “Less”

        switch (originalOperator) {
        case ExprNodeType::Greater:
            // Поменять операнды местами
            node->swapOperands();
            break;
        case ExprNodeType::GreaterEqual:
            // Добавить новую операцию “Not” перед корневой
            node->addUnaryOperatorBefore(ExprNodeType::Not);
            break;
        case ExprNodeType::LessEqual:
            // Поменять операнды местами
            node->swapOperands();
            // Добавить операцию “Not” перед корневой
            node->addUnaryOperatorBefore(ExprNodeType::Not);
            break;
        default:
            break;
        }
    }
}


int main(int argc, char* argv[]) {
    //Если получено меньше трех параметров завершаем программу
    if (argc < 3) {
        std::cerr << "Usage: program <input_file> <output_file>" << std::endl;
        return 0; 
    }

    //Считать из параметров командной строки путь к входному файлу
    std::string inputFilePath = argv[1];

    //Считать из параметров командной строки путь для выходных файлов
    std::string outputFilePath = argv[2];

    std::set<Error> errors;
    ExprNode* exprTree = nullptr;

    
    // Получить обратную польскую запись выражения из входного файла
    std::string* rpnString = readFileToString(inputFilePath, &errors);

    // Если удалось открыть входной файл и ошибок не было обнаружено
    if (rpnString != nullptr && errors.empty()) {

        // Получить дерево разбора выражения
        exprTree = stringToExprTree(*rpnString, &errors);

        //Если дерево разбора выражения построено без ошибок
        if (exprTree != nullptr && errors.empty()) {

            //Добавить ошибку, если корневая операция недопустима
            if (!checkRootOperator(exprTree->getType())) {

                Error error(ErrorType::invalidRootOperator, "", 0);

                //Добавить в сообщение об ошибке значение узла, если узел - операнд, иначе - тип узла
                error.strWithError = exprTree->getType() == ExprNodeType::Operand ? exprTree->getValue() : ExprNode::stringToSymbol.at(exprTree->getType());
                errors.insert(error);
            }
        }
    } 

    // Создать выходной файл
    std::ofstream outputFile;
    outputFile.open(outputFilePath);

    //Если удалось считать данные без ошибок и файл для выходных данных был создан
    if (exprTree != nullptr && outputFile.is_open() && errors.empty()) {

        //Преобразовать к операции меньше
        transformInequalityToLessOperator(exprTree);

        //Получить обратную польскую запись измененного дерева
        std::string rpnResult = exprTree->getRpnOfTree();

        //Вернуть в выходной файл измененное неравенство в обратной польской записи
        outputFile << rpnResult << std::endl;
    }

    // Очистить память, выделенную под дерево и строку с rpn
    if (rpnString != nullptr) {
        delete rpnString;
    }
    if (exprTree != nullptr) {
        delete exprTree;
    }

    //Если выходной файл был создан и есть ошибки
    if (outputFile.is_open() && !errors.empty()) {
        //Для каждой ошибки
        for (const Error& error : errors) {
            //Записать в выходной файл информацию об ошибке (generateErrorMessage)
            outputFile << error.generateErrorMessage() << std::endl;
        }
    }
    // Если выходной файл не удалось создать
    else if (!outputFile.is_open()) {
        //Вывести в консоль ошибку о неудаче создания выходного файла
        std::cerr << "По пути \"" << outputFilePath << "\" не удалось создать файл для выходных данных. Возможно указанного расположения не существует или нет прав на запись." << std::endl;
        return 0;
    }

    outputFile.close();
    return 0; 
}