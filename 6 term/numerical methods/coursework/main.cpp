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

double trapezoidFormula()
{
	double n{ 10 };
	double h{ (constants::b - constants::a) / n };
	return (h * ((getFunctionValue(constants::a) + getFunctionValue(constants::b)) / 2
		+ getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 2.0 * h)
		+ getFunctionValue(constants::a + 3.0 * h) + getFunctionValue(constants::a + 4.0 * h)
		+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 6.0 * h)
		+ getFunctionValue(constants::a + 7.0 * h) + getFunctionValue(constants::a + 8.0 * h)
		+ getFunctionValue(constants::a + 9.0 * h)));
}

double simpsonQuadrature()
{
	double n{ 10 };
	double h{ (constants::b - constants::a) / n };
	return (h / 3.0 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)
		+ 4 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 3.0 * h)
			+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 7.0 * h) 
			+ getFunctionValue(constants::a + 9.0 * h))
		+ 2 * (getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 4.0 * h)
			+ getFunctionValue(constants::a + 6.0 * h) + getFunctionValue(constants::a + 8.0 * h))));
}

double NewtonCotes3() {
	double n{ 3 };
	double h{ (constants::b - constants::a) / n };
	return (3.0 * h / 8.0 * (getFunctionValue(constants::a) + 3 * getFunctionValue(constants::a + h)
		+ 3 * getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 3.0 * h)));
}


double NewtonCotes4()
{
	double n{ 4 };
	double h{ (constants::b - constants::a) / n };
	return (4.0 * h / 90.0 * (7 * getFunctionValue(constants::a) + 32 * getFunctionValue(constants::a + h)
		+ 12 * getFunctionValue(constants::a + 2.0 * h) + 32 * getFunctionValue(constants::a + 3.0 * h)
		+ 7 * getFunctionValue(constants::b)));
}

double NewtonCotes5()
{
	double n{ 5 };
	double h{ (constants::b - constants::a) / n };
	return (5.0 * h / 288.0 * (19 * getFunctionValue(constants::a) + 75 * getFunctionValue(constants::a + h)
		+ 50 * getFunctionValue(constants::a + 2.0 * h) + 50 * getFunctionValue(constants::a + 3.0 * h)
		+ 75 * getFunctionValue(constants::a + 4.0 * h) + 19 * getFunctionValue(constants::b)));
}

double NewtonCotes1()
{
	double n{ 1 };
	double h{ (constants::b - constants::a) / n };
	return (h / 2.0 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)));
}

double NewtonCotes2()
{
	double n{ 2 };
	double h{ (constants::b - constants::a) / n };
	return (2 * h / 6.0 * (getFunctionValue(constants::a) + 4 * getFunctionValue(constants::a + h) + getFunctionValue(constants::b)));
}

int main()
{
	setlocale(LC_ALL, "russian");
	std::cout << std::setprecision(13) << std::fixed;

	double exactSolution{ getIntegralValue(constants::b) - getIntegralValue(constants::a) };

	double trapezoidFormulaSolution{ trapezoidFormula() };
	double trapezoidDifference{ std::abs(exactSolution - trapezoidFormulaSolution) };
	
	double simpsonQuadratureSolution{ simpsonQuadrature() };
	double simpsonDifference{ std::abs(exactSolution - simpsonQuadratureSolution) };

	double NewtonCotes1Solution{ NewtonCotes1() };
	double NewtonCotes1Difference{ std::abs(exactSolution - NewtonCotes1Solution) };

	double NewtonCotes2Solution{ NewtonCotes2() };
	double NewtonCotes2Difference{ std::abs(exactSolution - NewtonCotes2Solution) };

	double NewtonCotes3Solution{ NewtonCotes3() };
	double NewtonCotes3Difference{ std::abs(exactSolution - NewtonCotes3Solution) };
	
	double NewtonCotes4Solution{ NewtonCotes4() };
	double NewtonCotes4Difference{ std::abs(exactSolution - NewtonCotes4Solution) };

	double NewtonCotes5Solution{ NewtonCotes5() };
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



	std::cout << std::string(198, '_') << std::endl;
		std::cout << "|" << std::setw(18) << "J      "
		"|" << std::setw(18) << "J_1    "
		"|" << std::setw(18) << " |J - J_1|  "
		"|" << std::setw(18) << "J_2      "
		"|" << std::setw(18) << " |J - J_2|  "
		"|" << std::setw(18) << "J_3      "
		"|" << std::setw(18) << " |J - J_3|    "
		"|" << std::setw(18) << "J_4     "
		"|" << std::setw(18) << " |J - J_4|   "
		"|" << std::setw(18) << " J_5      "
		"|" << std::setw(18) << " |J - J_5|    "
		"|" << std::setw(17) << std::endl;
	std::cout << std::string(198, '_') << '\n';

	std::cout << 
		"|" << std::setw(17) << exactSolution <<
		"|" << std::setw(17) << NewtonCotes1Solution <<
		"|" << std::setw(17) << NewtonCotes1Difference <<
		"|" << std::setw(17) << NewtonCotes2Solution <<
		"|" << std::setw(17) << NewtonCotes2Difference <<
		"|" << std::setw(17) << NewtonCotes3Solution <<
		"|" << std::setw(17) << NewtonCotes3Difference <<
		"|" << std::setw(17) << NewtonCotes4Solution <<
		"|" << std::setw(17) << NewtonCotes4Difference <<
		"|" << std::setw(17) << NewtonCotes5Solution <<
		"|" << std::setw(17) << NewtonCotes5Difference <<
		"|" << std::setw(17) << std::endl;
	std::cout << std::string(198, '_') << '\n';

	return 0;
}