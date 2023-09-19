#include <array>
#include <cmath>
#include <iostream>
#include <fstream>

namespace constants
{
    constexpr double firstEpsilon{ 0.001 };
    constexpr double secondEpsilon{ 0.00001 };
}

void printIterativeMethodTableHeader(std::ofstream& outputFile)
{
    outputFile << "k" << " ;" << "x_k" << " ;" << "y_k" << " ;" << "z_k" << " ;" <<
        "x_k+1" << " ;" << "y_k+1" << " ;" << "z_k+1" << " ;" << "|x_k+1 - x_k|" <<
        " ;" << "|y_k+1 - y_k|" << " ;" << "|z_k+1 - z_k|" << " ;" << "sum\n";
}

double getNextX(double lastY, double lastZ)
{
    return -2.0 / 12.0 + 2 * lastY / 12.0 + 5 * lastZ / 12.0;
}

double getNextY(double lastX, double lastZ)
{
    return 2 + lastX / 6.0 + lastZ / 6.0;
}

double getNextZ(double lastX, double lastY)
{
    return 17.0 / 4.0 - lastX / 2.0 + lastY / 4.0;
}

double getResidualX(double x, double y, double z)
{
    return 5.0 / 4.0 - x + y / 4.0 + z / 4.0;
}

double getResidualY(double x, double y, double z)
{
    return -25.0 / 31.0 - y + x * 4.0 / 31.0 - z * 21.0 / 31.0;
}

double getResidualZ(double x, double y, double z)
{
    return -5.0 / 3.0 - z + x * 2.0 / 3.0 - y / 6.0;
}

void runIterativeMethodLoop(const double epsilon, std::ofstream& outputFile,
    double lastX, double lastY, double lastZ)
{
    int currentIteration{ 0 };
    bool keepGoing{ true };
    while (keepGoing)
    {
        double nextX = getNextX(lastY, lastZ);
        double nextY = getNextY(lastX, lastZ);
        double nextZ = getNextZ(lastX, lastY);

        double differenceX{ std::abs(nextX - lastX) };
        double differenceY{ std::abs(nextY - lastY) };
        double differenceZ{ std::abs(nextZ - lastZ) };

        double differenceSum{ differenceX + differenceY + differenceZ };
        outputFile << currentIteration << "\t;" << lastX << "\t;" << lastY << "\t;" <<
            lastZ << "\t;" << nextX << "\t;" << nextY << "\t;" << nextZ << "\t;" <<
            differenceX << "\t;" << differenceY << "\t;" << differenceZ << "\t;" <<
            differenceSum << '\n';


        ++currentIteration;
        lastX = nextX;
        lastY = nextY;
        lastZ = nextZ;

        if (differenceSum <= epsilon)
            keepGoing = false;
    }

    outputFile << '\n';
}

void runIterativeMethod(std::ofstream& outputFile, double lastX, double lastY, double lastZ)
{
    runIterativeMethodLoop(constants::firstEpsilon, outputFile,
        lastX, lastY, lastZ);
    runIterativeMethodLoop(constants::secondEpsilon, outputFile,
        lastX, lastY, lastZ);
}

std::array<double, 3> getInitialValues()
{
    std::cout << "x0 = ";
    double firstX{};
    std::cin >> firstX;

    std::cout << "y0 = ";
    double firstY{};
    std::cin >> firstY;

    std::cout << "z0 = ";
    double firstZ{};
    std::cin >> firstZ;

    return { firstX, firstY, firstZ };
}

void printInitialInformation()
{
    std::cout << "12x - 2y - 5z = -2\n";
    std::cout << "x - 6yy + z = -12\n";
    std::cout << "2x - y + 4z = 17\n";
}

void runSeidelMethod(std::ofstream& outputFile, double lastX, double lastY, double lastZ)
{
    int currentIteration{ 0 };
    bool keepGoing{ true };
    while (keepGoing)
    {
        double nextX = getNextX(lastY, lastZ);
        double nextY = getNextY(nextX, lastZ);
        double nextZ = getNextZ(nextX, nextY);

        double differenceX{ std::abs(nextX - lastX) };
        double differenceY{ std::abs(nextY - lastY) };
        double differenceZ{ std::abs(nextZ - lastZ) };

        double differenceSum{ differenceX + differenceY + differenceZ };

        outputFile << currentIteration << "\t;" << lastX << "\t;" << lastY << "\t;" <<
            lastZ << "\t;" << nextX << "\t;" << nextY << "\t;" << nextZ << "\t;" <<
            differenceX << "\t;" << differenceY << "\t;" << differenceZ << "\t;" <<
            differenceSum << '\n';

        ++currentIteration;
        lastX = nextX;
        lastY = nextY;
        lastZ = nextZ;

        if (differenceSum <= constants::firstEpsilon)
            keepGoing = false;
    }

    outputFile << '\n';
}

void printRelaxationMethodTableHeader(std::ofstream& outputFile)
{
    outputFile << "k" << " ;" << "x_k" << "\t;" << "y_k" << " ;" << "z_k" << " ;" <<
        "R_x(k)" << " ;" << "R_y(k)" << " ;" << "R_z(k)" << " ;" << "max|R(k)|\n";
}

double getMaxResidualValue(double residualX, double residualY, double residualZ)
{
    double absoluteResidualX{ std::abs(residualX) };
    double absoluteResidualY{ std::abs(residualY) };
    double absoluteResidualZ{ std::abs(residualZ) };

    double maxResidualAbsoluteValue{ std::max(absoluteResidualX, absoluteResidualY) };
    maxResidualAbsoluteValue = std::max(maxResidualAbsoluteValue, absoluteResidualZ);

    return maxResidualAbsoluteValue;
}

void runRelaxationMethodLoop(const double epsilon, std::ofstream& outputFile,
    double x, double y, double z)
{
    int currentIteration{ 1 };
    bool keepGoing{ true };
    while (keepGoing)
    {
        double residualX{ getResidualX(x, y, z) };
        double residualY{ getResidualY(x, y, z) };
        double residualZ{ getResidualZ(x, y, z) };

        double maxResidualAbsoluteValue{ getMaxResidualValue(residualX, residualY, residualZ) };

        outputFile << currentIteration << ";" << x << ";" << y << ";" << z <<
            ";" << residualX << ";" << residualY << ";" << residualZ << ";" <<
            maxResidualAbsoluteValue << '\n';

        ++currentIteration;
        if (std::abs(residualX) == maxResidualAbsoluteValue)
            x += residualX;
        else if (std::abs(residualY) == maxResidualAbsoluteValue)
            y += residualY;
        else if (std::abs(residualZ) == maxResidualAbsoluteValue)
            z += residualZ;

        if (std::abs(residualX) <= epsilon && std::abs(residualY) <= epsilon &&
            std::abs(residualZ) <= epsilon)
        {
            keepGoing = false;
        }
    }

}

void runRelaxationMethod(std::ofstream& outputFile, double x, double y,
    double z)
{
    printRelaxationMethodTableHeader(outputFile);
    runRelaxationMethodLoop(constants::firstEpsilon, outputFile, x, y, z);
    outputFile << '\n';
    printRelaxationMethodTableHeader(outputFile);
    runRelaxationMethodLoop(constants::secondEpsilon, outputFile, x, y, z);
}

int main()
{
    setlocale(LC_ALL, "Russian");

    std::ofstream outputFile{ "output.csv" };

    printInitialInformation();

    auto [firstX, firstY, firstZ] { getInitialValues() };

    printIterativeMethodTableHeader(outputFile);
    runIterativeMethod(outputFile, firstX, firstY, firstZ);
    runSeidelMethod(outputFile, firstX, firstY, firstZ);
    runRelaxationMethod(outputFile, firstX, firstY, firstZ);

    return 0;
}