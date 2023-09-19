#include <fstream>

void runRelaxationMethod(std::ofstream& outputFile, double x, double y, double z);
void printRelaxationMethodTableHeader(std::ofstream& outputFile);
double getMaxResidualValue(double residualX, double residualY, double residualZ);
void runRelaxationMethodLoop(const double epsilon, std::ofstream& outputFile, double x, double y, double z);
