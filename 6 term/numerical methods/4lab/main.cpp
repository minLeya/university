#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>

namespace constants {
    inline constexpr double gamma{ -1.7 };
    inline constexpr double m{ 2.3 };
    inline constexpr double alpha{ -1.2 };
    inline constexpr double beta{ 1.4 };
    inline constexpr double M{ 0.8 };
    inline constexpr double N{ -1.3 };

    inline constexpr int l{ 1 };
    inline constexpr int n{ 10 };
    inline constexpr double h{ l / static_cast<double>(n) };
}

void printHeader()
{
    std::cout << "|" << std::setw(15) << "t"
        << "|" << std::setw(14) << "x = 0.0"
        << "|" << std::setw(14) << "x = 0.1"
        << "|" << std::setw(14) << "x = 0.2"
        << "|" << std::setw(14) << "x = 0.3"
        << "|" << std::setw(14) << "x = 0.4"
        << "|" << std::setw(14) << "x = 0.5"
        << "|" << std::setw(14) << "x = 0.6"
        << "|" << std::setw(14) << "x = 0.7"
        << "|" << std::setw(14) << "x = 0.8"
        << "|" << std::setw(14) << "x = 0.9"
        << "|" << std::setw(14) << "x = 1.0"
        << "|" << "\n";
    std::cout << std::string(181, '_') << std::endl;

}

void printResult(double k, const std::vector<std::vector<double>>& result,
    const std::vector<double>& virtualResult)
{
    printHeader();

    std::cout << "|" << std::setw(15) << "Вирт. слой" << "|";
    std::cout << std::setw(14) << "  " << "|";
    for (int i{ 1 }; i < constants::n; ++i)
    {
        std::cout << std::setw(14) << virtualResult[i] << "|";
    }
     std::cout << std::setw(14) << "  " << "|";
    std::cout << '\n';


    for (int j{ 0 }; j <= constants::n; ++j)
    {
        std::cout << "|" << std::setw(15) << k * j <<"|";
        for (int i{ 0 }; i <= constants::n; ++i)
        {
            std::cout << std::setw(14) << result[i][j] << "|";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

double fxValue(double x)
{
    return (constants::gamma * std::exp(constants::m * x) + std::cos(constants::gamma * x));
}

double FxValue(double x)
{
    return (constants::alpha * std::exp(x) + constants::beta * std::cos(constants::gamma * x));
}

double phiTValue(double t)
{
    return (constants::alpha * t + std::sin(constants::beta * t));
}

double psiTValue(double t)
{
    return (std::exp(constants::N * t) + constants::M * std::sin(constants::m * t) + constants::N);
}

void calculateAndPrintResult()
{
    std::vector<std::vector<double>> u(constants::n + 1, std::vector<double>(constants::n + 1));
    std::vector<double> virtualU(constants::n + 1);

    // начальное условие при t = 0
    double x0{ 0.0 };
    for (int i{ 0 }; i <= constants::n; ++i)
    {
        u[i][0] = fxValue(x0 + i * constants::h);
    }

    // граничные условия при x = 0 и x = n
    double k{ constants::h };
    for (int j{ 1 }; j <= constants::n; ++j)
    {
        u[0][j] = phiTValue(k * j);
        u[constants::n][j] = psiTValue(k * j);
    }

    // заполнение виртуального слоя
    for (int i{ 1 }; i < constants::n; ++i)
    {
        virtualU[i] = u[i][0] - k * FxValue(x0 + i * constants::h);
    }

    // заполнение второго слоя с использованием первого слоя и виртуального слоя
    for (int i{ 1 }; i < constants::n; ++i)
    {
        u[i][1] = u[i + 1][0] + u[i - 1][0] - virtualU[i];
    }

    // заполнение u(i, j)
    for (int j{ 1 }; j < constants::n; ++j) 
    {
        for (int i{ 1 }; i < constants::n; ++i)
        {
            u[i][j + 1] = u[i + 1][j] + u[i - 1][j] - u[i][j - 1];
        }
    }

    printResult(k, u, virtualU);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    calculateAndPrintResult();

    return 0;
}
