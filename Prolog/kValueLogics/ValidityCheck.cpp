#include "ValidityCheck.h"

#include <cctype>
#include <iostream>

bool functionIsValid(const std::string& function, int numberOfValues, int numberOfVariables)
{
    return (bracketsAreValid(function) && numbersAreValid(function, numberOfValues) &&
        symbolsAreValid(function, numberOfVariables));
}

bool bracketsAreValid(const std::string& function)
{
    int balance{ 0 };
    for (const auto& symbol : function)
    {
        if (symbol == '(')
            ++balance;
        else if (symbol == ')')
            --balance;

        if (balance < 0)
        {
            std::cout << "the function has invalid brackets\n";
            return false;
        }
    }

    if (balance != 0)
        std::cout << "the function has invalid brackets\n";

    return (balance == 0);
}

bool numbersAreValid(const std::string& function, int numberOfValues)
{
    int number{ 0 };
    for (std::size_t i{ 0 }; i < function.size(); ++i)
    {
        while (std::isdigit(function[i]) && i < function.size())
            number = number * 10 + function[i++] - '0';

        if (number > numberOfValues - 1 || number < 0)
        {
            std::cout << "numbers in the function must be between 0 and " << numberOfValues - 1
                << " inclusive\n";
            return false;
        }
    }

    std::cout << "\nnumbers are valid\n";

    return true;
}

bool symbolsAreValid(const std::string& function, int numberOfVariables)
{
    std::string availableSymbols{ " ()^>1234567890x" };
    if (numberOfVariables == 2)
        availableSymbols += 'y';

    for (const auto& symbol : function)
    {
        if (availableSymbols.find(symbol) == std::string::npos)
        {
            std::cout << "unknown symbol: " << symbol << '\n';
            return false;
        }
    }

    return true;
}