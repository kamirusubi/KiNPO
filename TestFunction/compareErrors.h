#pragma once
#include "../eremeev_kinpo/exprNode.h"
#include "../eremeev_kinpo/error.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <iterator>  

std::set<Error> compareErrorSets(const std::set<Error>& expected, const std::set<Error>& actual);

std::wstring errorsToWstring(const std::set<Error>& errors);
