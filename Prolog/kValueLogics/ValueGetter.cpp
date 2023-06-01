#include "ValueGetter.h"
#include "ExpressionParser.h"

std::vector<int> getFunctionValues(const std::string& function, int numberOfValues,
    int numberOfVariables)
{
    std::vector<int> values{};
    if (numberOfVariables == 1)
        getSingleVariableFunctionValues(function, values, numberOfValues);
    else if (numberOfVariables == 2)
        getMultipleVariableFunctionValues(function, values, numberOfValues);

    return values;
}

void getSingleVariableFunctionValues(const std::string& function, std::vector<int>& values, int numberOfValues)
{
    for (int currentX{ 0 }; currentX < numberOfValues; ++currentX)
        values.push_back(evaluateFunction(function, currentX, 0, numberOfValues));
}

void getMultipleVariableFunctionValues(const std::string& function, std::vector<int>& values, int numberOfValues)
{
    for (int currentX{ 0 }; currentX < numberOfValues; ++currentX)
        for (int currentY{ 0 }; currentY < numberOfValues; ++currentY)
            values.push_back(evaluateFunction(function, currentX, currentY, numberOfValues));
}