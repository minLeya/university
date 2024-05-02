#include <iostream>
#include "math.h"
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

void printResult(double k, const std::vector<std::vector<double>>& result)
{
    printHeader();
    for (int j{ 0 }; j <= constants::n; ++j)
    {
        std::cout << "|" << std::setw(15) << k * j; // шаг по оси t
        for (int i{ 0 }; i <= constants::n; ++i)
        {
        std::cout << "|" << std::setw(14) << result[i][j];
        }
        std::cout << "|";
        std::cout << '\n';
    }
    std::cout << '\n';
}

// функция f(x)
double fxValue(double x)
{
    return (constants::gamma * std::exp(constants::m * x) + std::cos(constants::gamma * x));
}

// фи(t)
double phiTValue(double t)
{
    return (constants::alpha * t + std::sin(constants::beta * t));
}

// пси(t)
double psiTValue(double t)
{
    return (std::exp(constants::N * t) + constants::M * std::sin(constants::m * t + constants::N));
}

// явная схема
void runExplicitScheme()
{
    // шаг по оси t : k = h^2 / 6
    double k{ std::pow(constants::h, 2) / 6 };

    // создание двумерного массива для хранения значений функции u(x, t)
    std::vector<std::vector<double>> u(constants::n + 1, std::vector<double>(constants::n + 1));

    // начальное условие при t = 0
    double x0 = 0.0;
    for (int i{ 0 }; i <= constants::n; ++i)
    {
        u[i][0] = fxValue(x0 + i * constants::h);
    }

    // граничное условие при x = 0 и x = n 
    for (int j{ 1 }; j <= constants::n; ++j)
    {
        u[0][j] = phiTValue(k * j); 
        u[constants::n][j] = psiTValue(k * j);
    }

    // вычисление значений функции u(x, t)  методом явной схемы
    for (int j{ 0 }; j < constants::n; ++j)//
    {
        for (int i{ 1 }; i < constants::n; ++i)
        {
            u[i][j + 1] = 1.0 / 6.0 * (u[i - 1][j] + 4 * u[i][j] + u[i + 1][j]);
        }
    }

    std::cout << "Явная схема\n" << "Шаг по t: " << k << '\n';
    printResult(k, u);
}

// неявная схема
void runImplicitScheme(int s)
{
    // Вычисление шага по оси t: k = h^2 / s
    double k{ std::pow(constants::h, 2) / s };

    // Создание двумерных массивов для хранения значений функции u(x, t), коэффициентов a и b
    std::vector<std::vector<double>> u(constants::n + 1, std::vector<double>(constants::n + 1));
    std::vector<std::vector<double>> a(constants::n + 1, std::vector<double>(constants::n + 1));
    std::vector<std::vector<double>> b(constants::n + 1, std::vector<double>(constants::n + 1));

    // начальное условие при t = 0
    double x0 = 0.0;
    for (int i{ 0 }; i <= constants::n; ++i)
    {
        u[i][0] = fxValue(x0 + i * constants::h);
    }

    // граничные условия при x = 0 и x = n 
    for (int j{ 1 }; j <= constants::n; ++j)
    {
        u[0][j] = phiTValue(k * j);
        u[constants::n][j] = psiTValue(k * j);
    }

    // Прямой ход
    // Вычисление вспомогательных коэффициентов при прямом ходе на всех слоях при x=x1
    for (int j{ 0 }; j < constants::n; ++j)
    {
        a[1][j + 1] = 1.0 / (2.0 + s);
        b[1][j + 1] = phiTValue(k * (j + 1) ) + s * u[1][j];
    }

    // Вычисление оставшихся вспомогательных коэффициентов при обратном ходе на всех слоях при x=x2,x3,...,x(n-1).
    for (int j{ 0 }; j < constants::n; ++j)//
    {
        for (int i{ 2 }; i < constants::n; ++i)
        {
            a[i][j + 1] = 1.0 / (2.0 + s - a[i - 1][j + 1]);
            b[i][j + 1] = a[i - 1][j + 1] * b[i - 1][j + 1] + s * u[i][j];
        }

        // Вычисление значений uij при обратном ходе на данном слое
        for (int i{ constants::n - 1 }; i > 0; --i)
        {
            u[i][j + 1] = a[i][j + 1] * (b[i][j + 1] + u[i + 1][j + 1]);
        }
    }

    std::cout << "Неявная схема\nS = " << s << '\n' << "Шаг по t: " << k << '\n';
    printResult(k, u);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    for (int i{ 0 }; i < 3; ++i)
    {
        runExplicitScheme();
        std::cout << "S = ";
        int s{};
        std::cin >> s;
        runImplicitScheme(s);
    }

    return 0;
}
