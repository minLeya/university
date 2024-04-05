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
	/*return (3.0 * h / 8.0 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)
		+ 2 * (getFunctionValue(constants::a + 3.0 * h) + getFunctionValue(constants::a + 6.0 * h) + getFunctionValue(constants::a + 9.0 * h))
		+ 3 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 4.0 * h) 
			+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 7.0 * h) 
			+ getFunctionValue(constants::a + 8.0 * h) + getFunctionValue(constants::a + 10.0 * h)
			+ getFunctionValue(constants::a + 11.0 * h))));*/
}


double NewtonCotes4(int n)
{
	double h{ (constants::b - constants::a) / n };
	return (4.0 * h / 90.0 * (7 * (getFunctionValue(constants::a) + getFunctionValue(constants::b))
		+ 32 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 3.0 * h) 
			+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 7.0 * h)
			+ getFunctionValue(constants::a + 9.0 * h) + getFunctionValue(constants::a + 11.0 * h))
		+ 12 * (getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 6.0 * h) + getFunctionValue(constants::a + 10.0 * h)) 
		+ 14 * (getFunctionValue(constants::a + 4.0 * h) + getFunctionValue(constants::a + 8.0 * h))));
}

double NewtonCotes5(int n)
{
	double h{ (constants::b - constants::a) / n };
	return (5.0 * h / 288.0 * (19 * (getFunctionValue(constants::a) + getFunctionValue(constants::b))
		+ 75 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 4.0 * h) 
			+ getFunctionValue(constants::a + 6.0 * h) + getFunctionValue(constants::a + 9.0 * h))
		+ 50 * (getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 3.0 * h)
			+ getFunctionValue(constants::a + 7.0 * h) + getFunctionValue(constants::a + 8.0 * h))
		+ 38 * getFunctionValue(constants::a + 5.0 * h)));
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

	int n_3{ 12 };
	double NewtonCotes3Solution{ NewtonCotes3(n_3) };
	double NewtonCotes3Difference{ std::abs(exactSolution - NewtonCotes3Solution) };
	double h_3{ (constants::b - constants::a) / n_3 };

	int n_4{ 12 };
	double NewtonCotes4Solution{ NewtonCotes4(n_4) };
	double NewtonCotes4Difference{ std::abs(exactSolution - NewtonCotes4Solution) };
	double h_4{ (constants::b - constants::a) / n_4 };

	int n_5{ 10 };
	double NewtonCotes5Solution{ NewtonCotes5(n_5) };
	double NewtonCotes5Difference{ std::abs(exactSolution - NewtonCotes5Solution) };
	double h_5{ (constants::b - constants::a) / n_5 };


	std::cout << "n = 10:\n";
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


	std::cout << "n = 12:\n";
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


	std::cout << "n = 10:\n";
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
