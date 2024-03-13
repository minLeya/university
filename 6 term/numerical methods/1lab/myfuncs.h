#ifndef MYFUNCS_H_
#define MYFUNCS_H_

void printTableOne();
void printTableTwo();

void FirstTable_methods(const int& n);
void SecondTable_methods(const int& n, const double& epsilon);
double Eulers_method(const double& xi, const double& yi, const double& h);
double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h);
double Adams_method(const double& h, const double Adams_xi_mass[], const double Adams_yi_mass[]);

#endif /* MYFUNCS_H_ */