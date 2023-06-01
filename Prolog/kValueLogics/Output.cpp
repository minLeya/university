#include "ExpressionParser.h"
#include "Output.h"

#include <iomanip>
#include <iostream>
#include <vector>

void printAvailableOperations()
{
    std::cout << "\navailable operations:\n";
    std::cout << "raising to the denial of post: x_\n";
    std::cout << "multiplication: x * y\n\n";
}

void printResultTable(const std::vector<int>& values, int numberOfValues, int numberOfVariables)
{
    if (numberOfVariables == 1)
        printSingleVariableResults(values, numberOfValues);
    else if (numberOfVariables == 2)
        printMultipleVariableResults(values, numberOfValues);
}

void printSingleVariableResults(const std::vector<int>& values, int numberOfValues)
{
    std::cout << std::setw(4) << 'x' << std::string(3, ' ') << '|' << std::string(4, ' ') << "f(x)\n";
    for (int currentX{ 0 }, i{ 0 }; currentX < numberOfValues; ++currentX, ++i)
    {
        std::cout << std::setw(4) << currentX << std::string(3, ' ') << '|' << std::string(3, ' ') << std::setw(4) << values[i] << '\n';
    }
}

void printMultipleVariableResults(const std::vector<int>& values, int numberOfValues)
{
    std::cout << std::setw(4) << 'x' << std::string(3, ' ') << '|' << std::setw(4) << 'y' << std::string(3, ' ') << '|' << std::string(3, ' ') << "f(x,y)\n";
    int index{ 0 };
    for (int currentX{ 0 }; currentX < numberOfValues; ++currentX)
    {
        for (int currentY{ 0 }; currentY < numberOfValues; ++currentY, ++index)
        {
            std::cout << std::setw(4) << currentX << std::string(3, ' ') << '|'
                << std::setw(4) << currentY << std::string(3, ' ') << '|' << std::setw(7)
                << values[index] << '\n';
        }
    }
}

void printSecondForm(const std::vector<int>& values, int numberOfValues, int numberOfVariables)
{
    std::cout << "the second form: ";
    if (numberOfVariables == 1)
        printSecondFormForSingleVariable(values, numberOfValues);
    else if (numberOfVariables == 2)
        printSecondFormForMultipleVariables(values, numberOfValues);
    std::cout << '\n';
}

void printSecondFormForSingleVariable(const std::vector<int>& values, int numberOfValues)
{
    for (std::size_t i{ 0 }; i < values.size(); ++i)
    {
        bool isLast{ false };
        bool first{ false };
        bool second{ false };
        if (values[i] != 0 && values[i] != 1)
        {
            std::cout << values[i] << " * j" << i << "(x)";
            first = true;
        }

        else if (values[i] == 1)
        {
            std::cout << "j" << i << "(x)";
            second = true;
           
        }

        if (first == true || second == true)
            std::cout << " + ";
    }
}

void printSecondFormForMultipleVariables(const std::vector<int>& values, int numberOfValues)
{
    int index{ 0 };
    for (int i{ 0 }; i < numberOfValues; ++i)
    {
        for (int j{ 0 }; j < numberOfValues; ++j, ++index)
        {
            bool first{ false };
            bool second{ false };
            if (values[index] != 0 && values[index] != 1)
            {
                std::cout << values[index] << " * j" << i << "(x) * j" << j << "(y)";
                first = true;
            }

            else if (values[index] == 1)
            {
                std::cout << "j" << i << "(x) * j" << j << "(y)";
                second = true;
            }
            if (first == true || second == true)
                std::cout << " + ";
        }
    }
}
