#include "pch.h"
#include "compareErrors.h"

std::set<Error> compareErrorSets(const std::set<Error>& expected, const std::set<Error>& actual) {
    std::set<Error> differences;

    // ������ ������, ������� ���� � expected, �� ��� � actual
    std::set<Error> missingFromActual;
    std::set_difference(expected.begin(), expected.end(),
        actual.begin(), actual.end(),
        std::inserter(missingFromActual, missingFromActual.end()));

    // ������ ������, ������� ���� � actual, �� ��� � expected
    std::set<Error> extraInActual;
    std::set_difference(actual.begin(), actual.end(),
        expected.begin(), expected.end(),
        std::inserter(extraInActual, extraInActual.end()));

    // ������� ��� �������� � ���� set
    differences.insert(missingFromActual.begin(), missingFromActual.end());
    differences.insert(extraInActual.begin(), extraInActual.end());

    return differences;
}
