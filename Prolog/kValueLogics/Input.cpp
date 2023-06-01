#include "Input.h"

#include <iostream>
#include <limits>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getNumber(char numberLetter)
{
    std::cout << "enter " << numberLetter << ": ";
    while (true)
    {
        int number{};
        std::cin >> number;

        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cout << "invalid input, enter " << numberLetter << " again: ";
        }
        else if (numberLetter == 'k' && number <= 0)
        {
            ignoreLine();
            std::cout << "k must be greater than 0, enter k again: ";
        }
        else if (numberLetter == 'n' && (number <= 0 || number >= 3))
        {
            ignoreLine();
            std::cout << "n must be 1 or 2, enter n again: ";
        }
        else
        {
            ignoreLine();
            return number;
        }
    }
}

std::string getFunction(int numberOfVariables)
{
    std::cout << "enter your function:\n";
    if (numberOfVariables == 1)
        std::cout << "f(x) = ";
    else if (numberOfVariables == 2)
        std::cout << "f(x,y) = ";

    std::string function{};
    std::getline(std::cin, function);
    return function;
}