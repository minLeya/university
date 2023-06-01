#include "ExpressionParser.h"

#include <cmath>
#include <iostream>
#include <stack>

//отрицание - унарная операция
//умножение - бинарная операция

bool isDelimiter(char character)
{
    return character == ' ';
}

bool isOperator(char operatorCharacter)
{
    return operatorCharacter == '_' || operatorCharacter == '*';
}

bool isUnary(char operatorCharacter)
{
    return operatorCharacter == '_';
}

int getPriority(char operatorCharacter)
{
    if (operatorCharacter == '_') // унарная
        return 2;
    else if (operatorCharacter == '*') //бинарная
        return 1;

    return 0;
}

void processOperation(std::stack<int>& operands, char operatorCharacter, int numberOfValues)
{
    if (operatorCharacter == '_') //унарная x_
    {
        int auxiliaryOperand{ operands.top() };
        operands.pop();
        int operand{ operands.top() };
        operands.pop();
        operands.push(static_cast<int>(operand + auxiliaryOperand) % numberOfValues);
    }
    else //бинарная x*y
    {
        int rightOperand{ operands.top() };
        operands.pop();
        int leftOperand{ operands.top() };
        operands.pop();
        operands.push((rightOperand * leftOperand) % numberOfValues);
    }
}

void convertDenialToBinary(std::string& functionString)
{
    for (std::size_t i{ 0 }; i < functionString.size(); ++i)
    {
        if (functionString[i] == '_')
        {
            functionString.insert(i + 1, 1, '1');
            ++i;
        }
    }
}

std::string convertToPostfix(std::string& functionString)
{
    std::stack<char> operators{};
    std::string result{};
    result.reserve(functionString.size());

    for (std::size_t i{ 0 }; i < functionString.size(); ++i)
    {
        char currentCharacter{ functionString[i] };

        if (isDelimiter(currentCharacter))
            continue;

        if (std::isalnum(currentCharacter))
            result += currentCharacter;
        else if (currentCharacter == '(')
            operators.push(currentCharacter);
        else if (currentCharacter == ')')
        {
            while (operators.top() != '(')
            {
                result += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if (isOperator(currentCharacter))
        {
            while (!operators.empty() && getPriority(currentCharacter) <= getPriority(operators.top()))
            { //пока приоритет данного оператора <= приоритета оператора в топе 
                result += operators.top(); //добавляем операторы стека
                operators.pop();
            }
            operators.push(currentCharacter);
        }
    }
    while (!operators.empty()) //добавляем оставшиеся операторы
    {
        result += operators.top();
        operators.pop();
    }
   
    return result;
}

int evaluateFunction(const std::string& functionString, int currentX, int currentY, int numberOfValues)
{
    std::stack<int> operands{};

    for (std::size_t i{ 0 }; i < functionString.size(); ++i)
    {
        char currentCharacter{ functionString[i] };
        if (isOperator(currentCharacter))
            processOperation(operands, currentCharacter, numberOfValues);
        else if (std::isdigit(currentCharacter))
        {
            int number{ 0 }; //для чисел
            while (i < functionString.size() && std::isdigit(functionString[i]))
                number = number * 10 + functionString[i++] - '0';
            --i;
            operands.push(number);
        }
        else if (currentCharacter == 'x')
            operands.push(currentX);
        else if (currentCharacter == 'y')
            operands.push(currentY);
    }

    return operands.top();
}