#include <iostream>
#include <cmath>
#include <iomanip>
#include "constants.h"
#include <string>

double getFirstFunctionValue(double x, double y)
{
	return (2 * x + y - 7);
}

double getSecondFunctionValue(double x, double y)
{
	return (x * y - 6);
}

double alpha(double x, double y)
{
	return (-x / (2 * x - y));
}

double beta(double x, double y)
{
	return (1 / (2 * x - y));
}

double gamma(double x, double y)
{
	return (y / (2 * x - y));
}

double sigma(double x, double y)
{
	return (-2 / (2 * x - y));
}

double getNextXForIterativeMethod(double lastX, double lastY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastX + alpha(lastX, lastY) * firstFunctionValue + beta(lastX, lastY) * secondFunctionValue);
}

double getNextYForIterativeMethod(double lastX, double lastY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastY + gamma(lastX, lastY) * firstFunctionValue + sigma(lastX, lastY) * secondFunctionValue);
}

double getNextXForNewtonsMethod(double lastX, double lastY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastX - (lastX / (2 * lastX - lastY) * firstFunctionValue - 1 / (2 * lastX - lastY) * secondFunctionValue));
}

double getNextYForNewtonsMethod(double lastX, double lastY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastY - (-lastY / (2 * lastX - lastY) * firstFunctionValue + 2 / (2 * lastX - lastY) * secondFunctionValue));
}

double getNextXForModifiedNewtonsMethod(double lastX, double lastY, double firstX, double firstY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastX - (firstX / (2 * firstX - firstY) * firstFunctionValue - 1 / (2 * firstX - firstY) * secondFunctionValue));
}

double getNextYForModifiedNewtonsMethod(double lastX, double lastY, double firstX, double firstY)
{
	double firstFunctionValue{ getFirstFunctionValue(lastX, lastY) };
	double secondFunctionValue{ getSecondFunctionValue(lastX, lastY) };
	return (lastY - (-firstY / (2 * firstX - firstY) * firstFunctionValue + 2 / (2 * firstX - firstY) * secondFunctionValue));
}

void printHeader(const double epsilon, std::string method)
{
	std::cout << method << '\n';
	std::cout << "Точность " << epsilon << '\n';
	std::cout << std::string(140, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(10) << "x_k  "
		"|" << std::setw(11) << "x_k+1  "
		"|" << std::setw(15) << " |x_(k+1) - x_k| "
		"|" << std::setw(10) << "y_k  "
		"|" << std::setw(11) << "y_k+1   "
		"|" << std::setw(15) << "  |y_(k+1) - y_k|  "
		"|" << std::setw(15) << "  |f1(x_(k+1), y_(k+1))|  "
		"|" << std::setw(15) << "  |f2(x_(k+1), y_(k+1))|  "
		"|" << std::setw(14) << std::endl;
	std::cout << std::string(140, '_') << '\n';
}

void runIterativeMethod(const double epsilon, const double delta, double lastX, double lastY)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	
	while (keepGoing)
	{
		if (lastY != 2 * lastX)
		{
			double nextX{ getNextXForIterativeMethod(lastX, lastY) };
			double nextY{ getNextYForIterativeMethod(lastX, lastY) };
			double xDifference{ std::abs(nextX - lastX) };
			double yDifference{ std::abs(nextY - lastY) };
			double firstFunctionValue{ std::abs(getFirstFunctionValue(nextX, nextY)) };
			double secondFunctionValue{ std::abs(getSecondFunctionValue(nextX, nextY)) };

			std::cout << "|" << std::setw(5) << currentIteration <<
				"|" << std::setw(9) << lastX <<
				"|" << std::setw(10) << nextX <<
				"|" << std::setw(17) << xDifference <<
				"|" << std::setw(9) << lastY <<
				"|" << std::setw(10) << nextY <<
				"|" << std::setw(19) << yDifference <<
				"|" << std::setw(26) << firstFunctionValue <<
				"|" << std::setw(26) << secondFunctionValue <<
				"|" << std::setw(14) << std::endl;
			std::cout << std::string(140, '_') << '\n';

			lastX = nextX;
			lastY = nextY;
			++currentIteration;

			if (xDifference <= epsilon && yDifference <= epsilon &&
				firstFunctionValue <= delta && secondFunctionValue <= delta)
			{
				keepGoing = false;
				std::cout << "Корни:\n";
				std::cout << "x = " << lastX << '\n';
				std::cout << "y = " << lastY << '\n';
			}
		}
		else
		{
			keepGoing = false;
			std::cout << "Итерационный процесс окончен, так как в знаменателе 0.\n";
		}	
	}
}

void runNewtonsMethod(const double epsilon, const double delta, double lastX, double lastY)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	while (keepGoing)
	{
		if (lastY != 2 * lastX)
		{
			double nextX{ getNextXForNewtonsMethod(lastX, lastY) };
			double nextY{ getNextYForNewtonsMethod(lastX, lastY) };
			double xDifference{ std::abs(nextX - lastX) };
			double yDifference{ std::abs(nextY - lastY) };
			double firstFunctionValue{ std::abs(getFirstFunctionValue(nextX, nextY)) };
			double secondFunctionValue{ std::abs(getSecondFunctionValue(nextX, nextY)) };

			std::cout << "|" << std::setw(5) << currentIteration <<
				"|" << std::setw(9) << lastX <<
				"|" << std::setw(10) << nextX <<
				"|" << std::setw(17) << xDifference <<
				"|" << std::setw(9) << lastY <<
				"|" << std::setw(10) << nextY <<
				"|" << std::setw(19) << yDifference <<
				"|" << std::setw(26) << firstFunctionValue <<
				"|" << std::setw(26) << secondFunctionValue <<
				"|" << std::setw(14) << std::endl;
			std::cout << std::string(140, '_') << '\n';

			lastX = nextX;
			lastY = nextY;
			++currentIteration;

			if (xDifference <= epsilon && yDifference <= epsilon &&
				firstFunctionValue <= delta && secondFunctionValue <= delta)
			{
				keepGoing = false;
				std::cout << "Корни:\n";
				std::cout << "x = " << lastX << '\n';
				std::cout << "y = " << lastY << '\n';
			}
		}
		else
		{
			std::cout << "Итерационный процесс метода Ньютона окончен, так как матрица Якоби вырожденная.\n";

			keepGoing = false;
		}
	}
}

void runModifiedNewtonsMethod(const double epsilon, const double delta, double lastX, double lastY, double firstX, double firstY)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	bool convergence{ true };
	while(keepGoing)
	{
		if (firstY != 2 * firstX)
		{
			double nextX{ getNextXForModifiedNewtonsMethod(lastX, lastY, firstX, firstY) };
			double nextY{ getNextYForModifiedNewtonsMethod(lastX, lastY, firstX, firstY) };
			double xDifference{ std::abs(nextX - lastX) };
			double yDifference{ std::abs(nextY - lastY) };
			double firstFunctionValue{ std::abs(getFirstFunctionValue(nextX, nextY)) };
			double secondFunctionValue{ std::abs(getSecondFunctionValue(nextX, nextY)) };

			std::cout << "|" << std::setw(5) << currentIteration <<
				"|" << std::setw(9) << lastX <<
				"|" << std::setw(10) << nextX <<
				"|" << std::setw(17) << xDifference <<
				"|" << std::setw(9) << lastY <<
				"|" << std::setw(10) << nextY <<
				"|" << std::setw(19) << yDifference <<
				"|" << std::setw(26) << firstFunctionValue <<
				"|" << std::setw(26) << secondFunctionValue <<
				"|" << std::setw(14) << std::endl;
			std::cout << std::string(140, '_') << '\n';

			lastX = nextX;
			lastY = nextY;
			++currentIteration;

			if (xDifference <= epsilon && yDifference <= epsilon &&
				firstFunctionValue <= delta && secondFunctionValue <= delta)
			{
				keepGoing = false;
				std::cout << "Корни:\n";
				std::cout << "x = " << lastX << '\n';
				std::cout << "y = " << lastY << '\n';
			}

			if (lastX == +INFINITY || lastY == +INFINITY || lastX == -INFINITY && lastY == -INFINITY )
			{
				convergence = true;
				keepGoing = false;
			}
		}
		else
		{
			std::cout << "Итерационный процесс модифицированного метода Ньютона окончен, так как матрица Якоби вырожденная.\n";
			keepGoing = false;
		}

	} 
	if (convergence)
	{
		std::cout  << "Модифицированный метод Ньютона расходится, т.к. обратная матрица Якоби не является непрерывной и мало меняющейся " <<
			"в области (окрестности), в которой ищем решение.\n";
	}
}

void iterative(double x, double y)
{
	printHeader(constants::firstEpsilon, "Метод простых итераций");
	runIterativeMethod(constants::firstEpsilon, constants::firstDelta, x, y);
	std::cout << '\n';
	printHeader(constants::secondEpsilon, "Метод простых итераций");
	runIterativeMethod(constants::secondEpsilon, constants::secondDelta, x, y);
	std::wcout << '\n';
}

void newtons(double x, double y)
{
	printHeader(constants::firstEpsilon, "Метод Ньютона");
	runNewtonsMethod(constants::firstEpsilon, constants::firstDelta, x, y);
	std::cout << '\n';
	printHeader(constants::secondEpsilon, "Метод Ньютона");
	runNewtonsMethod(constants::secondEpsilon, constants::secondDelta, x, y);
	std::cout << '\n';
}

void modifiedNewtons(double x, double y, double firstX, double firstY)
{
	printHeader(constants::firstEpsilon, "Модифицированный метод Ньютона");
	runModifiedNewtonsMethod(constants::firstEpsilon, constants::firstDelta, x, y, firstX, firstY);
	std::cout << '\n';
	printHeader(constants::secondEpsilon, "Модифицированный метод Ньютона");
	runModifiedNewtonsMethod(constants::secondEpsilon, constants::secondDelta, x, y, firstX, firstY);
}

int main()
{
	setlocale(LC_ALL, "russian");
	std::cout << "13 вариант.\n";
	std::cout << "|2x + y - 7 = 0,\n|xy - 6 = 0.\n";

	double firstX{};
	std::cout << "Введите х_0: ";
	std::cin >> firstX;

	double firstY{};
	std::cout << "Введите у_0: ";
	std::cin >> firstY;

	std::cout << '\n';

	iterative(firstX, firstY);
	newtons(firstX, firstY);
	modifiedNewtons(firstX, firstY, firstX, firstY);

	return 0;
}