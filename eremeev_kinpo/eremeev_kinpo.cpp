#include <iostream>
#include "header.h"

ExprNode* stringToExprTree(std::string rpnString, std::set <Error>* errors) {
    std::stack<ExprNode*> stack; // Стэк с содержимым класса ExprNode
    std::stringstream stream(rpnString); // Поток с выражением в обратной польской записи
    std::string token;
    int position = 0;
    std::map <ExprNode*, int> tokenIndex;/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (stream >> token && errors->empty()) { // Пока в переменную token получается извлечь часть потока и нет ошибок
        position += 1;
        ExprNode* newNode = new ExprNode(); // Создать узел newNode

        // Если token – операнд
        if (isOperand(token)) {
            newNode->value = token; // Присвоить полю value newNode значение token
            newNode->type = ExprNodeType::Operand; // Присвоить полю type newNode значение Operand
        }
        // Если token – символ из словаря symbolToString
        else if (ExprNode::symbolToString.count(token)) {
            newNode->type = ExprNode::symbolToString.at(token); // Присвоить значению type newNode словесную запись оператора из словаря symbolToString

            int operandCountNeeded = ExprNode::operandCount.at(newNode->type); // Узнать необходимое количество операндов

            // Если в стеке нет нужного количества операндов
            if (stack.size() < operandCountNeeded) {
                errors->insert(Error(ErrorType::missingOperand, token, position)); // Добавить ошибку о недостатке операндов
            }
            // Если нет ошибок
            if (errors->empty()) {
                // Если оператор бинарный
                if (operandCountNeeded == 2) {
                    newNode->secondOperand = stack.top(); // Присвоить второму операнду newNode значение верхнего узла из стека
                    stack.pop(); // Удалить из стека верхний узел
                }
                newNode->firstOperand = stack.top(); // Присвоить первому операнду newNode значение верхнего узла из стека
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

    //НЕПОНЯТНО КАК СЧИТАТЬ ПОЗИЦИЮ ДЛЯ ЛИШНИХ ОПЕРАНДОВ И ОПЕРАТОРОВ 
    // std::map <ExprNode*, int> tokenIndex;
    if (stack.size() > 1) { // Если в стэке больше одного элемента
        //сохранить верхушку стека
        ExprNode* tree = stack.top();
        stack.pop();

        //для всех неиспользованных операндов
        while (stack.size() > 0)
        {
            ExprNode* tmp = stack.top();
            stack.pop();
            errors->insert(Error(ErrorType::redundantOperand, "", 0));
        }
    }


    // Если нет ошибок
    if (errors->empty() && !stack.empty()) {
        ExprNode* root = stack.top(); // Вернуть верхушку стэка
        stack.pop();
        return root;
    }
    else {
        // Обработка ошибок: очистка стека и освобождение памяти
        while (!stack.empty()) {
            delete stack.top();
            stack.pop();
        }
        return nullptr;
    }
}
bool isOperand(std::string str) {
    bool isOperandFlag = true;

    if (str.empty()) {
        isOperandFlag = false; // Пустая строка не может быть операндом
    }

    //Если длина str больше 1 и первый символ str - «0» 
    if (str.length() > 1 && str[0] == '0' && isOperandFlag) {
        //Если второй символ str - «X» или «x»
        if (str[1] == 'X' || str[1] == 'x') {
            // Шестнадцатеричное число
            for (int i = 2; i < str.length(); ++i) {
                if (!isxdigit(str[i])) {
                    return false; // Недопустимый символ в шестнадцатеричном числе
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
            return false;  // После '0' должен идти 'x', 'X' или цифра
        }
    }
    // Если первый символ - цифра
    else if (isdigit(str[0]) && isOperandFlag) {
        // Проверяем, что остальные символы тоже цифры
        for (int i = 1; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                return false; // Есть нецифровой символ
            }
        }
    }
    // Если начинается с буквы или "_"
    else if (isalpha(str[0]) || str[0] == '_') {
        for (size_t i = 1; i < str.length(); ++i) {
            if (!isalnum(str[i]) && str[i] != '_') {
                return false; // Недопустимый символ
            }
        }
    }
    else {
        return false; // Недопустимый первый символ
    }
    return isOperandFlag;
}




bool checkRootOperator(ExprNodeType op) {
    // Контейнер допустимых корневых операторов
    std::set<ExprNodeType> validRootOperators = {
        ExprNodeType::Less,
        ExprNodeType::Greater,
        ExprNodeType::GreaterEqual,
        ExprNodeType::LessEqual
    };
    //Вернуть допустимость корневого оператора
    return validRootOperators.count(op) > 0;
}


void transformInequalityToLessOperator(ExprNode* node) {
    // Если корневая операция отличается от “Less”
    if (node->type != ExprNodeType::Less) {
        ExprNodeType originalOperator = node->type; // Запомнить корневую операцию

        node->type = ExprNodeType::Less; // Заменить корневую операцию на “Less”

        switch (originalOperator) {
        case ExprNodeType::Greater:
            // Поменять операнды местами
            std::swap(node->firstOperand, node->secondOperand);
            break;
        case ExprNodeType::GreaterEqual:
            // Добавить новую операцию “Not” перед корневой
            node->addUnaryOperatorBefore(ExprNodeType::Not);
            break;
        case ExprNodeType::LessEqual:
            // Поменять операнды местами
            std::swap(node->firstOperand, node->secondOperand);
            // Добавить операцию “Not” перед корневой
            node->addUnaryOperatorBefore(ExprNodeType::Not);
            break;
        default:
            // Не требуется никаких изменений для других операторов
            break;
        }
    }
}

int main()
{
    //ExprNode ex("5");
    //ex.addUnaryOperatorBefore(ExprNodeType::Not);
    //std::cout << ex.getRpmOfTree();


    std::string rpnString = "5 x >";
    std::set<Error>* errors = new std::set<Error>();
    ExprNode* tree = stringToExprTree(rpnString, errors);
    tree->swapOperands();
    rpnString = tree->getRpnOfTree();
    std::cout << rpnString;

    return 0;
}
