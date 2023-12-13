#include <iostream>
#include <cmath>
#include <math.h>
#include <numbers>
#include <vector>
#include <iomanip>

double getFunctionValue(double x, double y)
{
	if ((x >= 0) && (y >= 0) && (12 - 2 * x - 3 * y >= 0))
	{
		return 12 - 2 * x - 3 * y;
	}
	else
		return 0;
}


double getIntegralValue(double x)
{
    return (24 * x - 4 * x * x + (2 * x * x * x) / 9);
}

std::vector<std::vector<int>> getLambdaMatrix(std::size_t n, std::size_t m)
{
    std::vector<std::vector<int>> matrix(2 * m + 1, std::vector<int>(2 * n + 1, 0));

    matrix[0][0] = 1;
    matrix[2 * m][2 * n] = 1;
    matrix[2 * m][0] = 1;
    matrix[0][2 * n] = 1;

    for (std::size_t i{ 1 }; i < 2 * m; ++i)
    {
        if (((i - 1) % 2) == 1)
        {
            matrix[i][0] = 2;
            matrix[i][2 * n] = 2;
        }
        else
        {
            matrix[i][0] = 4;
            matrix[i][2 * n] = 4;
        }
    }

    for (std::size_t i{ 1 }; i < 2 * n; ++i)
    {
        if (((i - 1) % 2) == 1)
        {
            matrix[0][i] = 2;
            matrix[2 * m][i] = 2;
        }
        else
        {
            matrix[0][i] = 4;
            matrix[2 * m][i] = 4;
        }
    }

    for (std::size_t i{ 1 }; i < 2 * m; ++i)
    {
        for (std::size_t j{ 1 }; j < 2 * n; ++j)
        {
            matrix[i][j] = matrix[0][j] * matrix[i][0];
        }
    }

    return matrix;
}


double getXi(double a, double A, std::size_t i, std::size_t n)
{
    return a + i * (A - a) / (2.0 * n);
}

double getYi(double b, double B, std::size_t j, std::size_t m)
{
    return b + j * (B - b) / (2.0 * m);
}

double simpsonFormula(std::size_t n, std::size_t m)
{
    double a{ 0 };
    double A{ 6 };
    double b{ 0 };
    double B{ 4 };

    double h{ (A - a) / (2.0 * n) };
    double k{ (B - b) / (2.0 * m) };
    std::vector<std::vector<int>> lambdaMatrix{ getLambdaMatrix(n, m) };

    double result{ 0.0 };
    for (std::size_t j{ 0 }; j <= 2 * m; ++j)
    {
        for (std::size_t i{ 0 }; i <= 2 * n; ++i)
        {
            double xi{ getXi(a, A, i, n) };
            double yi{ getYi(b, B, j, m) };
            result += h * k / 9.0 * lambdaMatrix[j][i] * getFunctionValue(xi, yi);
        }
    }

    return result;
}

void printHeader()
{
    std::cout << std::string(94, '_') << std::endl;
    std::cout << "|" << std::setw(17) << "n"
        "|" << std::setw(19) << "m"
        "|" << std::setw(19) << "Jточн      "
        "|" << std::setw(19) << "Jc     "
        "|" << std::setw(19) << "|Jточн - Jc|   "
        "|" << std::setw(18) << std::endl;
    std::cout << std::string(94, '_') << '\n';
}

int main()
{
    setlocale(LC_ALL, "russian");
    std::cout << "n = ";
    std::size_t n{};
    std::cin >> n;

    std::cout << "m = ";
    std::size_t m{};
    std::cin >> m;

    printHeader();
    double integralValue{ getIntegralValue(6) - getIntegralValue(0) };
    double simpsonValue{ simpsonFormula(n, m) };
    double simpsonDifference{ std::abs(integralValue - simpsonValue) };

    std::cout << std::setprecision(13) << std::fixed;
    std::cout << "|" << std::setw(16) << n <<
        "|" << std::setw(18) << m <<
        "|" << std::setw(18) << integralValue <<
        "|" << std::setw(18) << simpsonValue <<
        "|" << std::setw(18) << simpsonDifference <<
        "|" << std::setw(18) << std::endl;
    std::cout << std::string(94, '_') << '\n';



	return 0;
}
