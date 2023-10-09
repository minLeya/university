#include <iostream>
#include <cmath>
#include <iomanip>
#include "constants.h"

double getFunctionValue(double x)
{
	return (2 * log10(x) - x / 2.0 + 1);
}

double getNextForIterativeMethod(double lastX)
{
	double functionValue{ getFunctionValue(lastX) };
	return (lastX + (-0.5 * functionValue));
}

double getNextForNewtonMethod(double lastX)
{
	double functionValue{ getFunctionValue(lastX) };
	double denominator{ (2.0 / (lastX * log(10))) - 0.5 };
	return (lastX - functionValue / denominator);
}

double getNextForModifiedNewtonNethod(double lastX)
{
	double functionValue{ getFunctionValue(lastX) };
	double denominator{ 8.0 / log(10) - 0.5 };
	return (lastX - functionValue / denominator);
}

//iterative method
void printIterativeMethodTableHeader(const double epsilon)
{
	std::cout << "Метод простых итераций\n";
	std::cout << "Точность " << epsilon << '\n';
	std::cout << std::string(76, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(15) << "x_k+1"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(20) << "   |f(x_k+1)|   "
		"|" << std::setw(14) << std::endl;
	std::cout << std::string(76, '_') << '\n';
}

void runIterativeMethodLoop(const double epsilon, const double delta, double lastX)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	while (keepGoing)
	{
		double nextX{ getNextForIterativeMethod(lastX) };
		double xDifference{ std::abs(nextX - lastX) };
		double functionValue{ std::abs(getFunctionValue(nextX)) };

		std::cout << "|" << std::setw(5) << currentIteration <<
			"|" << std::setw(11) << lastX <<
			"|" << std::setw(14) << nextX <<
			"|" << std::setw(21) << xDifference <<
			"|" << std::setw(19) << functionValue << "|\n";
		std::cout << std::string(76, '_') << '\n';

		lastX = nextX;

		if (xDifference <= epsilon && functionValue <= delta)
			keepGoing = false;

		++currentIteration;
	}
	std::cout << "Найденный приближённый корень:\n";
	std::cout << "x = " << lastX << '\n';
	std::cout << '\n';
}

//newton method 
void printNewtonMethodTableHeader(const double epsilon)
{
	std::cout << "Метод Ньютона\n";
	std::cout << "Точность " << epsilon << '\n';
	std::cout << std::string(76, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(15) << "x_k+1"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(20) << "   |f(x_k+1)|   "
		"|" << std::setw(14) << std::endl;
	std::cout << std::string(76, '_') << '\n';
}

void runNewtonMethodLoop(const double epsilon, const double delta, double lastX)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	while (keepGoing)
	{
		double nextX{ getNextForNewtonMethod(lastX) };
		double xDifference{ std::abs(nextX - lastX) };
		double functionValue{ std::abs(getFunctionValue(nextX)) };

		std::cout << "|" << std::setw(5) << currentIteration <<
			"|" << std::setw(11) << lastX <<
			"|" << std::setw(14) << nextX <<
			"|" << std::setw(21) << xDifference <<
			"|" << std::setw(19) << functionValue << "|\n";
		std::cout << std::string(76, '_') << '\n';

		lastX = nextX;

		if (xDifference <= epsilon || functionValue <= delta)
			keepGoing = false;

		++currentIteration;
	}
	std::cout << "Найденный приближённый корень:\n";
	std::cout << "x = " << lastX << '\n';
	std::cout << '\n';
}

//modified newton method
void printModifiedNewtonMethodTableHeader(const double epsilon)
{
	std::cout << "Модифицированный метод Ньютона\n";
	std::cout << "Точность " << epsilon << '\n';
	std::cout << std::string(76, '_') << std::endl;
	std::cout << "|" << std::setw(6) << "k+1"
		"|" << std::setw(12) << "x_k"
		"|" << std::setw(15) << "x_k+1"
		"|" << std::setw(20) << "   |x_(k+1) - x_k|   "
		"|" << std::setw(20) << "   |f(x_k+1)|   "
		"|" << std::setw(14) << std::endl;
	std::cout << std::string(76, '_') << '\n';
}

void runNodifiedNewtonMethodLoop(const double epsilon, const double delta, double lastX)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	while (keepGoing)
	{
		double nextX{ getNextForModifiedNewtonNethod(lastX) };
		double xDifference{ std::abs(nextX - lastX) };
		double functionValue{ std::abs(getFunctionValue(nextX)) };

		std::cout << "|" << std::setw(5) << currentIteration <<
			"|" << std::setw(11) << lastX <<
			"|" << std::setw(14) << nextX <<
			"|" << std::setw(21) << xDifference <<
			"|" << std::setw(19) << functionValue << "|\n";
		std::cout << std::string(76, '_') << '\n';

		lastX = nextX;

		if (xDifference <= epsilon || functionValue <= delta)
			keepGoing = false;

		++currentIteration;
	}
	std::cout << "Найденный приближённый корень:\n";
	std::cout << "x = " << lastX << '\n';
	std::cout << '\n';
}

int main()
{
	setlocale(LC_ALL, "Russian");
	printNewtonMethodTableHeader(constants::firstEpsilon);
	runNewtonMethodLoop(constants::firstEpsilon, constants::firstDelta, 0.25);
	std::cout << "\n";
	printModifiedNewtonMethodTableHeader(constants::firstEpsilon);
	runNodifiedNewtonMethodLoop(constants::firstEpsilon, constants::firstDelta, 0.25);
	std::cout << '\n';
	printIterativeMethodTableHeader(constants::firstEpsilon);
	runIterativeMethodLoop(constants::firstEpsilon, constants::firstDelta, 0.5);
	return 0;
}