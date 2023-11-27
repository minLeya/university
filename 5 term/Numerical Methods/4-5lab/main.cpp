#include <iostream>
#include <string>
#include <math.h>
#include <cmath>
#include <vector>
#include <iomanip>
#include <array>

namespace constants
{
    inline constexpr double leftEndOfRange{ 3.125 };
    inline constexpr double rightEndOfRange{ 3.135 };
}

double getFunctionValue(double x)
{
	return (3 * exp(cos(x) + 4) + x);
}

double getQ(double x)
{
	return ((x - 3.125) / 0.002);
}

double getT(double x)
{
	return ((x - 3.135) / 0.002);
}

double firstNewtonsInterpolationFormula(double x)
{
	double q{ getQ(x) };
	return (63.38990595932 + 0.000120726165 * q
		+ 0.00024107793 * q * (q - 1) / 2
		- 0.000000013106 * q * (q - 1) * (q - 2) / 6
		+ 0.000000001931 * q * (q - 1) * (q - 2) * (q - 3) / 24
		- 0.000000000013 * q * (q - 1) * (q - 2) * (q - 3) * (q - 4) / 120);
}

double secondNewtonsInterpolationFormula(double x)
{
	double t{ getT(x) };
	return (63.392920248047 + 0.00108496698 * t
		+ 0.000241044392 * t * (t + 1) / 2
		- 0.000000009257 * t * (t + 1) * (t + 2) / 6
		+ 0.000000001918 * t * (t + 1) * (t + 2) * (t + 3) / 24
		- 0.000000000013 * t * (t + 1) * (t + 2) * (t + 3) * (t + 4) / 120);
}

double lagrangeInterpolationFormula(double x)
{
    return (-16507788010239.5833333 * (x - 3.127) * (x - 3.129) * (x - 3.131) * (x - 3.133) * (x - 3.135)
        + 82539097246725.260416666 * (x - 3.125) * (x - 3.129) * (x - 3.131) * (x - 3.133) * (x - 3.135)
        - 165079136691614.5833333 * (x - 3.125) * (x - 3.127) * (x - 3.131) * (x - 3.133) * (x - 3.135)
        + 165080706662757.8125 * (x - 3.125) * (x - 3.127) * (x - 3.129) * (x - 3.133) * (x - 3.135)
        - 82541452188889.3229166666 * (x - 3.125) * (x - 3.127) * (x - 3.129) * (x - 3.131) * (x - 3.135)
        + 16508572981262.2395833333 * (x - 3.125) * (x - 3.127) * (x - 3.129) * (x - 3.131) * (x - 3.133));
}

double getDerivativeValue(double x)
{
    return (1 - 3 * exp(cos(x) + 4) * sin(x));
}

double getClosestX0(double x)
{
    std::vector<double> values{ 3.125, 3.127, 3.129, 3.131, 3.133, 3.135 };
    double x0{};

    for (int i{ 0 }; i < 5; ++i)
    {
        double leftDifference{ std::abs(x - values[i]) };
        double rightDifference{ std::abs(x - values[i + 1]) };
        if (leftDifference == rightDifference)
        {
            x0 = values[i];
            break;
        }
        else if (x >= values[i] && x <= values[i + 1])
        {
            if (leftDifference < rightDifference)
                x0 = values[i];
            else
                x0 = values[i + 1];
        }
    }

    return x0;
}

double getClosestXn(double x)
{
    std::vector<double> values{ 3.125, 3.127, 3.129, 3.131, 3.133, 3.135 };
    double x0{};

    for (int i{ 0 }; i < 5; ++i)
    {
        double leftDifference{ std::abs(x - values[i]) };
        double rightDifference{ std::abs(x - values[i + 1]) };
        if (leftDifference == rightDifference)
        {
            x0 = values[i + 1];
            break;
        }
        else if (x >= values[i] && x <= values[i + 1])
        {
            if (leftDifference < rightDifference)
                x0 = values[i];
            else
                x0 = values[i + 1];
        }
    }

    return x0;
}


double derivativeFirstNewtonsInterpolation(double x)
{
    double x0{ getClosestX0(x) };
    double q{ (x - x0) / 0.002 };
    return (1.0 / 0.002 * (0.000120726165 + 0.00024107793 * (2 * q - 1) / 2
        - 0.000000013106 * (3 * q * q - 6 * q + 2) / 6 
        + 0.000000001931 * (4 * q * q * q - 18 * q * q + 22 * q - 6) / 24
        - 0.000000000013 * (5 * q * q * q * q - 40 * q * q * q + 105 * q * q - 100 * q + 24) / 120));
}

double derivativeSecondNewtonsInterpolation(double x)
{
    double xn{ getClosestXn(x) };
    double t{ (x - xn) / 0.002 };
    return (1.0 / 0.002 * (0.00108496698 + 0.000241044392 * (2 * t + 1) / 2 
        - 0.000000009257 * (3 * pow(t, 2) + 6 * t + 2) / 6 
        + 0.000000001918 * (4 * pow(t, 3) + 18 * pow(t, 2) + 22 * t + 6) / 24
        - 0.000000000013 * (5 * pow(t, 4) + 40 * pow(t, 3) + 105 * pow(t, 2) + 100 * t + 24) / 120));
}

void printHeaderForInterpolation()
{
    std::cout << std::string(188, '_') << std::endl;
    std::cout << "|" << std::setw(17) << "x"
       "|" << std::setw(19) << "y(x)"
       "|" << std::setw(19) << "PI(x) "
       "|" << std::setw(19) << "|y(x) - PI(x)| "
       "|" << std::setw(19) << "q"
       "|" << std::setw(19) << "PII(x)   "
       "|" << std::setw(19) << "|y(x)-PII(x)|  "
       "|" << std::setw(19) << "t"
       "|" << std::setw(19) << "L(x)"
       "|" << std::setw(19) << "|y(x)-L(x)|  "
       "|" << std::setw(18) << std::endl;
    std::cout << std::string(188, '_') << '\n';
}

void printHeaderForNumericalDifferentiation()
{
    std::cout << std::string(192, '_') << std::endl;
    std::cout << "|" << std::setw(17) << "x"
        "|" << std::setw(19) << "y'(x)"
        "|" << std::setw(19) << "(PI(x))' "
        "|" << std::setw(19) << " x0 "
        "|" << std::setw(19) << "q  "
        "|" << std::setw(19) << "|y(x) - (PI(x))'|"
        "|" << std::setw(19) << "(PII(x))' "
        "|" << std::setw(19) << "xn"
        "|" << std::setw(19) << "t"
        "|" << std::setw(21) << " |(y(x))' - (PII(x))'|"
        "|" << std::setw(18) << std::endl;
    std::cout << std::string(192, '_') << '\n';
}

int main()
{
    setlocale(LC_ALL, "russian");
    std::array<double, 3> inputValues{};
    for (int i{ 0 }; i < 3; ++i)
    {
        std::cout << "x" << i << " = ";
        std::cin >> inputValues[i];
        if (inputValues[i] > constants::rightEndOfRange ||
            inputValues[i] < constants::leftEndOfRange)
        {
            std::cout << "Значения должны принадлежать отрезку [3.125; 3.135]\n";
            std::cout << "x" << i << " = ";
            std::cin >> inputValues[i];
        }
    }

    printHeaderForInterpolation();
    std::cout << std::setprecision(13) << std::fixed;
    for (int i{ 0 }; i < 3; ++i)
    {
        double functionValue{ getFunctionValue(inputValues[i]) };

        double firstInterpolationFormulaValue{ firstNewtonsInterpolationFormula(inputValues[i]) };
        double firstDifference{ std::abs(functionValue - firstInterpolationFormulaValue) };
        double q{ getQ(inputValues[i]) };
      
        double secondInterpolationFormulaValue{ secondNewtonsInterpolationFormula(inputValues[i]) };
        double secondDifference{ std::abs(functionValue - secondInterpolationFormulaValue) };
        double t{ getT(inputValues[i]) };

        double lagrangeInterpolationFormulaValue{ lagrangeInterpolationFormula(inputValues[i]) };
        double thirdDifference{ std::abs(functionValue - lagrangeInterpolationFormulaValue) };
        std::cout << "|" << std::setw(16) << inputValues[i] <<
            "|" << std::setw(18) << functionValue <<
            "|" << std::setw(18) << firstInterpolationFormulaValue <<
            "|" << std::setw(18) << firstDifference <<
            "|" << std::setw(18) << q <<
            "|" << std::setw(18) << secondInterpolationFormulaValue <<
            "|" << std::setw(18) << secondDifference <<
            "|" << std::setw(18) << t <<
            "|" << std::setw(18) << lagrangeInterpolationFormulaValue <<
            "|" << std::setw(18) << thirdDifference <<
            "|" << std::setw(18) << std::endl;
        std::cout << std::string(188, '_') << '\n';

    }

    std::cout << '\n';

    printHeaderForNumericalDifferentiation();
    std::cout << std::setprecision(13) << std::fixed;

    for (int i{ 0 }; i < 3; ++i)
    {
        double derivativeValue{ getDerivativeValue(inputValues[i]) };

        double x0{ getClosestX0(inputValues[i]) };
        double q{ (inputValues[i] - x0) / 0.002 };
        double derivativeFirstInterpolationFormula{ derivativeFirstNewtonsInterpolation(inputValues[i]) };
        double firstDerivativeDifference{ std::abs(derivativeValue - derivativeFirstInterpolationFormula) };

        double xn{ getClosestXn(inputValues[i]) };
        double t{ (inputValues[i] - xn) / 0.002 };
        double derivativeSecondInterpolationFormula{ derivativeSecondNewtonsInterpolation(inputValues[i]) };
        double secondDerivativeDifference{ std::abs(derivativeValue - derivativeSecondInterpolationFormula) };

    
        std::cout << "|" << std::setw(16) << inputValues[i] <<
             "|" << std::setw(18) << derivativeValue <<
             "|" << std::setw(18) << derivativeFirstInterpolationFormula <<
             "|" << std::setw(18) << x0 <<
             "|" << std::setw(18) << q <<
             "|" << std::setw(18) << firstDerivativeDifference <<
             "|" << std::setw(18) << derivativeSecondInterpolationFormula <<
             "|" << std::setw(18) << xn <<
             "|" << std::setw(18) << t <<
             "|" << std::setw(22) << secondDerivativeDifference <<
             "|" << std::setw(18) << std::endl;
        std::cout << std::string(192, '_') << '\n';
    }
    
    return 0;
}
