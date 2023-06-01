#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "Output.h"
#include "ExpressionParser.h"
#include "Input.h"
#include "ValueGetter.h"

int main()
{
    int numberOfValues{ getNumber('k') };
    int numberOfVariables{ getNumber('n') };

    printAvailableOperations();
    std::string function{ getFunction(numberOfVariables) };
    convertDenialToBinary(function);

    std::string postfixForm{ convertToPostfix(function) }; //обратная польская нотация/запись или постфиксная форма
    std::vector<int> values{ getFunctionValues(postfixForm, numberOfValues, numberOfVariables) };
   
    printResultTable(values, numberOfValues, numberOfVariables);
    printSecondForm(values, numberOfValues, numberOfVariables);
    //void checkForSetPreservation(values, numberOfValues, numberOfVariables);

    return 0;
}