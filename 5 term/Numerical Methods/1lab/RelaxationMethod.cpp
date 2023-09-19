#include "RelaxationMethod.h"
#include "constants.h"

double getResidualX(double x, double y, double z)
{
    return -2.0 / 12.0 - x + 2 * y / 12.0 + 5 * z / 12.0;
}

double getResidualY(double x, double y, double z)
{
    return 2.0 - y + x / 6.0 + z / 6.0;
}

double getResidualZ(double x, double y, double z)
{
    return 17.0 / 4.0 - z - x / 2.0 + y / 4.0;
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

void runRelaxationMethodLoop(const double epsilon, std::ofstream& outputFile, double x, double y, double z)
{
    int currentIteration{ 1 };
    bool keepGoing{ true };
    while (keepGoing)
    {
        double residualX{ getResidualX(x, y, z) };
        double residualY{ getResidualY(x, y, z) };
        double residualZ{ getResidualZ(x, y, z) };

        double maxResidualAbsoluteValue{ getMaxResidualValue(residualX, residualY, residualZ) };

        outputFile << currentIteration << "\t;" << x << "\t;" << y << ";\t" << z <<
            "\t;" << residualX << "\t;" << residualY << ";\t" << residualZ << ";\t" <<
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
