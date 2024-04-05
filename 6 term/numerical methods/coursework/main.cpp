#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

namespace constants {
	double constexpr a{ 1.0 };
	double constexpr b{ 3.0 };
}

double getFunctionValue(double x) {
	return (x * atan(x));
}

double getIntegralValue(double x)
{
	return (x * x * atan(x) / 2 - 0.5 * x + 0.5 * atan(x));
}

double trapezoidFormula(int n)
{
	double h{ (constants::b - constants::a) / n };
	double trapezoidFormulaSum{ getFunctionValue(constants::a) + getFunctionValue(constants::b) };

	for (int m{ 2 }; m <= n; m++) {
		trapezoidFormulaSum += 2 * getFunctionValue(constants::a + (m - 1) * h);	}
	return (h / 2.0 * trapezoidFormulaSum);
}

double simpsonQuadrature(int n)
{
	double h{ (constants::b - constants::a) / n };
	double simpsonQuadratureSum{ getFunctionValue(constants::a) + getFunctionValue(constants::b) };

	for (int m{ 1 }; 2 * m <= n; m++) {
		if (m != 1) {
			simpsonQuadratureSum += 2 * getFunctionValue(constants::a + (2 * m - 2) * h);
		}
		simpsonQuadratureSum += 4 * getFunctionValue(constants::a + (2 * m - 1) * h);
	}
	return (h / 3.0 * simpsonQuadratureSum);
}

double NewtonCotes3(int n)
{
	double h{ (constants::b - constants::a) / n };
	double NewtonCotes3Sum{ getFunctionValue(constants::a) + getFunctionValue(constants::b) };

	for (int m{ 1 }; 3 * m <= n; m++) {
		if (m != 1)
		{
			NewtonCotes3Sum += 2 * getFunctionValue(constants::a + (3 * m - 3) * h);
		}
		NewtonCotes3Sum += 3 * getFunctionValue(constants::a + (3 * m - 2) * h);
		NewtonCotes3Sum += 3 * getFunctionValue(constants::a + (3 * m - 1) * h);
	}
	return (3.0 * h / 8.0 * NewtonCotes3Sum);
}


double NewtonCotes4(int n)
{
	double h{ (constants::b - constants::a) / n };
	double NewtonCotes4Sum{ 7 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)) };

	for (int m{ 1 }; 4 * m <= n; m++) {
		if (m != 1)
		{
			NewtonCotes4Sum += 2 * 7 * getFunctionValue(constants::a + (4 * m - 4) * h);
		}

		NewtonCotes4Sum += 32 * getFunctionValue(constants::a + (4 * m - 3) * h);
		NewtonCotes4Sum += 12 * getFunctionValue(constants::a + (4 * m - 2) * h);
		NewtonCotes4Sum += 32 * getFunctionValue(constants::a + (4 * m - 1) * h);
	}
	return (4.0 * h / 90.0 * NewtonCotes4Sum);
}

double NewtonCotes5(int n)
{
	double h{ (constants::b - constants::a) / n };

	double NewtonCotes5Sum{ 19 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)) };

	for (int m{ 1 }; 5 * m <= n; m++) {
		if (m != 1)
		{
			NewtonCotes5Sum += 2 * 19 * getFunctionValue(constants::a + (5 * m - 5) * h);
		}

		NewtonCotes5Sum += 75 * getFunctionValue(constants::a + (5 * m - 4) * h);
		NewtonCotes5Sum += 50 * getFunctionValue(constants::a + (5 * m - 3) * h);
		NewtonCotes5Sum += 50 * getFunctionValue(constants::a + (5 * m - 2) * h);
		NewtonCotes5Sum += 75 * getFunctionValue(constants::a + (5 * m - 1) * h);
	}
	return (5.0 * h / 288.0 * NewtonCotes5Sum);
}


int main()
{
	setlocale(LC_ALL, "russian");
	std::cout << std::setprecision(15) << std::fixed;

	double exactSolution{ getIntegralValue(constants::b) - getIntegralValue(constants::a) };

	int n{ 60 };

	double trapezoidFormulaSolution{ trapezoidFormula(n) };
	double trapezoidDifference{ std::abs(exactSolution - trapezoidFormulaSolution) };

	double simpsonQuadratureSolution{ simpsonQuadrature(n) };
	double simpsonDifference{ std::abs(exactSolution - simpsonQuadratureSolution) };

	double NewtonCotes3Solution{ NewtonCotes3(n) };
	double NewtonCotes3Difference{ std::abs(exactSolution - NewtonCotes3Solution) };

	double NewtonCotes4Solution{ NewtonCotes4(n) };
	double NewtonCotes4Difference{ std::abs(exactSolution - NewtonCotes4Solution) };

	double NewtonCotes5Solution{ NewtonCotes5(n) };
	double NewtonCotes5Difference{ std::abs(exactSolution - NewtonCotes5Solution) };

	std::cout << std::string(101, '_') << std::endl;
	std::cout << "|" << std::setw(19) << "J"
		"|" << std::setw(19) << "J(тр) "
		"|" << std::setw(19) << "|J - J(тр)|  "
		"|" << std::setw(19) << "J(кв.ф.Симпсона)"
		"|" << std::setw(22) << " |J - J(кв.ф.Симпсона)| "
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(101, '_') << '\n';

	std::cout <<
		"|" << std::setw(18) << exactSolution <<
		"|" << std::setw(18) << trapezoidFormulaSolution <<
		"|" << std::setw(18) << trapezoidDifference <<
		"|" << std::setw(18) << simpsonQuadratureSolution <<
		"|" << std::setw(24) << simpsonDifference <<
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(101, '_') << "\n\n";


	std::cout << std::string(97, '_') << std::endl;
	std::cout << "|" << std::setw(19) << "J"
		"|" << std::setw(19) << "J_3 "
		"|" << std::setw(19) << "|J - J_3|  "
		"|" << std::setw(19) << "J_4"
		"|" << std::setw(20) << "|J - J_4|   "
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(97, '_') << '\n';

	std::cout <<
		"|" << std::setw(18) << exactSolution <<
		"|" << std::setw(18) << NewtonCotes3Solution <<
		"|" << std::setw(18) << NewtonCotes3Difference <<
		"|" << std::setw(18) << NewtonCotes4Solution <<
		"|" << std::setw(19) << NewtonCotes4Difference <<
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(97, '_') << "\n\n";


	std::cout << std::string(54, '_') << std::endl;
	std::cout << "|" << std::setw(18) << "J      "
		"|" << std::setw(18) << "J_5     "
		"|" << std::setw(18) << " |J - J_5|   "
		"|" << std::setw(17) << std::endl;
	std::cout << std::string(54, '_') << '\n';


	std::cout <<
		"|" << std::setw(17) << exactSolution <<
		"|" << std::setw(17) << NewtonCotes5Solution <<
		"|" << std::setw(17) << NewtonCotes5Difference <<
		"|" << std::setw(17) << std::endl;
	std::cout << std::string(54, '_') << '\n';

	return 0;
}
