#include "pch.h"
#include "compareErrors.h"

std::set<Error> compareErrorSets(const std::set<Error>& expected, const std::set<Error>& actual) {
    std::set<Error> differences;

    // Найдем ошибки, которые есть в expected, но нет в actual
    std::set<Error> missingFromActual;
    std::set_difference(expected.begin(), expected.end(),
        actual.begin(), actual.end(),
        std::inserter(missingFromActual, missingFromActual.end()));

    // Найдем ошибки, которые есть в actual, но нет в expected
    std::set<Error> extraInActual;
    std::set_difference(actual.begin(), actual.end(),
        expected.begin(), expected.end(),
        std::inserter(extraInActual, extraInActual.end()));

    // Добавим все различия в один set
    differences.insert(missingFromActual.begin(), missingFromActual.end());
    differences.insert(extraInActual.begin(), extraInActual.end());

    return differences;
}
