#pragma once
#include "../eremeev_kinpo/exprNode.h"
#include "../eremeev_kinpo/error.h"
#include <sstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <iterator>  

bool compareErrorSets(const std::set<Error>& expected, const std::set<Error>& actual, std::set<Error>& missing, std::set<Error>& extra);
