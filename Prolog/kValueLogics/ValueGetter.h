#ifndef VALUE_GETTER_H
#define VALUE_GETTER_H

#include <string>
#include <vector>

std::vector<int> getFunctionValues(const std::string& function, int numberOfValues,
    int numberOfVariables);
void getSingleVariableFunctionValues(const std::string& function, std::vector<int>& values,
    int numberOfValues);
void getMultipleVariableFunctionValues(const std::string& function, std::vector<int>& values,
    int numberOfValues);

#endif