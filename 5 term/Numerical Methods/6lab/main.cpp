#include <iostream>
#include <string>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <vector>

namespace constants {
	double constexpr a{ 1.0 };
	double constexpr b{ 2.0 };
}

double getFunctionValue(double x)
{
	return (pow(x, 3) * exp(-x));
}

double getIntegralValue(double x)
{
	return ((-pow(x, 3) - 3 * pow(x, 2) - 6 * x - 6) / exp(x));
}

double trapezoidFormula4()
{
	double n{ 4 };
	double h{ (constants::b - constants::a) / n };
	return (h * ((getFunctionValue(constants::a) + getFunctionValue(constants::b)) / 2
		+ getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 2.0 * h)
		+ getFunctionValue(constants::a + 3.0 * h)));
}

double trapezoidFormula8()
{
	double n{ 8 };
	double h{ (constants::b - constants::a) / n };
	return (h * ((getFunctionValue(constants::a) + getFunctionValue(constants::b)) / 2
		+ getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 2.0 * h)
		+ getFunctionValue(constants::a + 3.0 * h) + getFunctionValue(constants::a + 4.0 * h)
		+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 6.0 * h)
		+ getFunctionValue(constants::a + 7.0 * h)));
}

double simpsonQuadrature4()
{
	double n{ 4 };
	double h{ (constants::b - constants::a) / n };
	return (h / 3.0 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)
		+ 4 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 3.0 * h))
		+ 2 * getFunctionValue(constants::a + 2.0 * h)));
}

double simpsonQuadrature8()
{
	double n{ 8 };
	double h{ (constants::b - constants::a) / n };
	return (h / 3.0 * (getFunctionValue(constants::a) + getFunctionValue(constants::b)
		+ 4 * (getFunctionValue(constants::a + h) + getFunctionValue(constants::a + 3.0 * h)
			+ getFunctionValue(constants::a + 5.0 * h) + getFunctionValue(constants::a + 7.0 * h))
		+ 2 * (getFunctionValue(constants::a + 2.0 * h) + getFunctionValue(constants::a + 4.0 * h) + getFunctionValue(constants::a + 6.0 * h))));
}

double gaussianQuadrature4()
{
	std::vector<double> t{ -0.86113631, -0.33998104, 0.33998104, 0.86113631 };
	std::vector<double> A{ 0.34785484, 0.65214516, 0.65214516, 0.34785484 };
	double gaussianSum{ 0 };
	double x{ 0 };
	for (int i{ 0 }; i < 4; ++i)
	{
		x = ((constants::b + constants::a) / 2 + ((constants::b - constants::a) / 2) * t[i]);
		gaussianSum += (constants::b - constants::a) / 2.0 * A[i] * getFunctionValue(x);
	}
	return gaussianSum;
}

double gaussianQuadrature8()
{
	std::vector<double> t{ -0.96028986, -0.79666648, -0.52553242, -0.18343464, 0.18343464, 0.52553242, 0.79666648, 0.96028986 };
	std::vector<double> A{ 0.10122854, 0.22238104, 0.31370664, 0.36268378, 0.36268378, 0.31370664, 0.22238104, 0.10122854 };
	double gaussianSum{ 0 };
	double x{ 0 };
	for (int i{ 0 }; i < 8; ++i)
	{
		x = ((constants::b + constants::a) / 2 + ((constants::b - constants::a) / 2) * t[i]);
		gaussianSum += (constants::b - constants::a) / 2.0 * A[i] * getFunctionValue(x);
	}
	return gaussianSum;
}

int main()
{
	setlocale(LC_ALL, "russian");
	std::cout << std::setprecision(13) << std::fixed;
	double exactSolution{ getIntegralValue(constants::b) - getIntegralValue(constants::a) };

	double trapezoidFormulaSolution4{ trapezoidFormula4() };
	double trapezoidFormulaSolution8{ trapezoidFormula8() };

	double trapezoidDifference4{ std::abs(exactSolution - trapezoidFormulaSolution4) };
	double trapezoidDifference8{ std::abs(exactSolution - trapezoidFormulaSolution8) };

	double simpsonQuadratureSolution4{ simpsonQuadrature4() };
	double simpsonQuadratureSolution8{ simpsonQuadrature8() };

	double simpsonDifference4{ std::abs(exactSolution - simpsonQuadratureSolution4) };
	double simpsonDifference8{ std::abs(exactSolution - simpsonQuadratureSolution8) };
	
	double gaussianQuadratureSolution4{ gaussianQuadrature4() };
	double gaussianQuadratureSolution8{ gaussianQuadrature8() };

	double gaussianDifference4{ std::abs(exactSolution - gaussianQuadratureSolution4) };
	double gaussianDifference8{ std::abs(exactSolution - gaussianQuadratureSolution8) };


	std::cout << std::string(147, '_') << std::endl;
	std::cout << "|" << std::setw(5) << "n"
		"|" << std::setw(19) << "J"
		"|" << std::setw(19) << "J_тр "
		"|" << std::setw(19) << "|J - J_тр|  "
		"|" << std::setw(19) << "J_кв.ф.Симпсона"
		"|" << std::setw(22) << " |J - J_кв.ф.Симпсона| "
		"|" << std::setw(19) << "J_кв.ф.Гаусса"
		"|" << std::setw(22) << " |J - J_кв.ф.Гаусса| "
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(147, '_') << '\n';

	std::cout << "|" << std::setw(4) << 4 <<
		"|" << std::setw(18) << exactSolution <<
		"|" << std::setw(18) << trapezoidFormulaSolution4 <<
		"|" << std::setw(18) << trapezoidDifference4 <<
		"|" << std::setw(18) << simpsonQuadratureSolution4 <<
		"|" << std::setw(23) << simpsonDifference4 <<
		"|" << std::setw(18) << gaussianQuadratureSolution4 <<
		"|" << std::setw(21) << gaussianDifference4 <<
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(147, '_') << '\n';

	std::cout << "|" << std::setw(4) << 8 <<
		"|" << std::setw(18) << exactSolution <<
		"|" << std::setw(18) << trapezoidFormulaSolution8 <<
		"|" << std::setw(18) << trapezoidDifference8 <<
		"|" << std::setw(18) << simpsonQuadratureSolution8 <<
		"|" << std::setw(23) << simpsonDifference8 <<
		"|" << std::setw(18) << gaussianQuadratureSolution8 <<
		"|" << std::setw(21) << gaussianDifference8 <<
		"|" << std::setw(18) << std::endl;
	std::cout << std::string(147, '_') << '\n';

	return 0;
}