#include "pch.h"
#include "compareErrors.h"

bool compareErrorSets(const std::set<Error>& expected, const std::set<Error>& actual, std::set<Error>& missing, std::set<Error>& extra) {
    // Найдем ошибки, которые есть в expected, но нет в actual
    std::set_difference(expected.begin(), expected.end(),
        actual.begin(), actual.end(),
        std::inserter(missing, missing.end()));

    // Найдем ошибки, которые есть в actual, но нет в expected
    std::set_difference(actual.begin(), actual.end(),
        expected.begin(), expected.end(),
        std::inserter(extra, extra.end())); 

    return missing.empty() && extra.empty();
}
