#include <iostream>
#include <cmath>
#include <math.h>
#include <iomanip>

namespace constants
{
	const double nu{ pow(2, 0) * log(2) + 7 };
	const double mu{ pow(2, 2) * log(2) + 7 };
	const double alpha{ 1.0 - constants::nu / constants::mu };
	const double epsilon{ 1.e-5 };
}

double getFunctionValue(double x)
{
	return (pow(2, x) + 7 * x - 10);
}

double getNextIterativeMethod(double lastX)
{
	double function{ getFunctionValue(lastX) };
	return (lastX - (1 / constants::mu) * function);
}

void runIterativeMethod(const double epsilon, const double alpha, double lastX)
{
	int currentIteration{ 1 };
	bool keepGoing{ true };
	double xDifference{ };
	while (keepGoing)
	{
		double nextX{ getNextIterativeMethod(lastX) };
		xDifference = std::abs(nextX - lastX);

		lastX = nextX;

		if (alpha / (1 - alpha) * xDifference <= epsilon)
			keepGoing = false;

		++currentIteration;
	}
	std::cout << "Найденный приближённый корень x = " << lastX
		<< " получен на итерации i = " << currentIteration
		<< ", |x_n - x_n-1 | = " << std::setprecision(10) << std::fixed << xDifference<< '\n';
}

int main()
{
	setlocale(LC_ALL, "Russian");
	double firstX{ 2.0 };
	double secondX{ getNextIterativeMethod(firstX) };
	std::cout << "x_1 = " << firstX << '\n';
	double p{ std::abs(secondX - firstX) };
	double numerator{ log(constants::epsilon * (1 - constants::alpha) / p) };
	double Napr{ floor(numerator / log(constants::alpha)) + 1};
	std::cout << "p(x_0, x_1) = " << p;
	std::cout << "\nNapr = " << Napr << '\n';
	runIterativeMethod(constants::epsilon, constants::alpha, firstX);
	return 0;
}
