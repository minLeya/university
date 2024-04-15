#include <iostream>
#include <iomanip>
#include <string>

namespace constants
{
	constexpr double alpha0{ 1.0 };
	constexpr double alpha1{ 1.0 };
	constexpr double beta0{ 1.0 };
	constexpr double beta1{ 1.0 };
	constexpr double a{ 0.0 };
	constexpr double b{ 1.0 };
	constexpr double bigA{ 1.0 };
	constexpr double bigB{ 2.0 };
}

void printTable()
{
	std::cout << std::string(116, '_') << std::endl;
	std::cout << "|" << std::setw(2) << "" <<
		"|" << std::setw(15) << "xi       " <<
		"|" << std::setw(15) << "yi       " <<
		"|" << std::setw(15) << "mi       " <<
		"|" << std::setw(15) << "ri       " <<
		"|" << std::setw(15) << "phi       " <<
		"|" << std::setw(15) << "ci       " <<
		"|" << std::setw(15) << "di       " <<
		"|" << std::endl;
	std::cout << std::string(116, '_') << std::endl;
}

//Значения xi
double* get_mass_x(const int& n, const double& h)
{

	double* mass_x = new double[n + 1] {};
	mass_x[0] = constants::a;
	for (int i{ 1 }; i <= n; i++)
		mass_x[i] = mass_x[i - 1] + h;
	return mass_x;
}
//Значения pi
double* get_mass_p(const double* const mass_x, const int& n, const double& h)
{
	double* mass_p = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_p[i] = mass_x[i] * mass_x[i] - 0.4;
	return mass_p;
}
//Значения qi
double* get_mass_q(const double* const mass_x, const int& n, const double& h)
{
	double* mass_q = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_q[i] = sin(mass_x[i]);
	return mass_q;
}
//Значения fi
double* get_mass_f(const double* const mass_x, const int& n, const double& h)
{
	double* mass_f = new double[n + 1] {};
	for (int i{}; i <= n; i++)
		mass_f[i] = mass_x[i] * mass_x[i];
	return mass_f;
}
//Значения mi
double* get_mass_m(const double* const mass_q, const double* const mass_p, const int& n, const double& h)
{
	double* mass_m = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_m[i] = (2 * h * h * mass_q[i] - 4) / (2 + h * mass_p[i]);
	return mass_m;
}
//Значениями ri
double* get_mass_r(const double* const mass_p, const int& n, const double& h)
{
	double* mass_r = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_r[i] = (2 - h * mass_p[i]) / (2 + h * mass_p[i]);
	return mass_r;
}
//Значения phi
double* get_mass_phi(const double* const mass_p, const double* const mass_f, const int& n, const double& h)
{
	double* mass_phi = new double[n + 1] {};
	for (int i{ 1 }; i < n; i++)
		mass_phi[i] = (2 * h * h * mass_f[i]) / (2 + h * mass_p[i]);
	return mass_phi;
}

//Значения ci
double* get_mass_c(const double* const mass_m, const double* const mass_r, const int& n, const double& h)
{
	double* mass_c = new double[n + 1] {};
	mass_c[0] = constants::alpha0 / (constants::alpha1 * h - constants::alpha0);
	for (int i{ 1 }; i < n; i++)
		mass_c[i] = 1 / (mass_m[i] - mass_r[i] * mass_c[i - 1]);
	return mass_c;
}
//Значения di
double* get_mass_d(const double* const mass_phi, const double* const mass_r, const double* const mass_c, const int& n, const double& h)
{
	double* mass_d = new double[n + 1] {};
	mass_d[0] = constants::bigA * h / constants::alpha0;
	for (int i{ 1 }; i < n; i++)
		mass_d[i] = mass_phi[i] - mass_r[i] * mass_c[i - 1] * mass_d[i - 1];
	return mass_d;
}
//Значения yi
double* get_mass_y(const double* const mass_c, const double* const mass_d, const int& n, const double& h)
{
	double* mass_y = new double[n + 1] {};
	mass_y[n] = (constants::bigB * h + constants::beta0 * mass_c[n - 1] * mass_d[n - 1]) / (constants::beta0 * (1 + mass_c[n - 1]) + h * constants::beta1);
	for (int i{ n - 1 }; i >= 0; i--)
		mass_y[i] = mass_c[i] * (mass_d[i] - mass_y[i + 1]);
	return mass_y;
}

//Метод прогонки
void sweep_method(const int& n)
{
	double h{ (constants::b - constants::a) / n };

	//Прямой ход метода прогонки

	//Формирование массива mass_x
	double* mass_x = get_mass_x(n, h);
	//Получение массивов коэффициентов pi, qi, fi, mi, ri, phi
	double* mass_p = get_mass_p(mass_x, n, h);
	double* mass_q = get_mass_q(mass_x, n, h);
	double* mass_f = get_mass_f(mass_x, n, h);
	double* mass_m = get_mass_m(mass_q, mass_p, n, h);
	double* mass_r = get_mass_r(mass_p, n, h);
	double* mass_phi = get_mass_phi(mass_p, mass_f, n, h);
	//Получение массивов коэффициентов ci, di
	double* mass_c = get_mass_c(mass_m, mass_r, n, h);
	double* mass_d = get_mass_d(mass_phi, mass_r, mass_c, n, h);

	//Обратный ход метода
	//Формирование массива mass_y
	double* mass_y = get_mass_y(mass_c, mass_d, n, h);
	//Вычисление y0 по формуле из первого краевого условия
	double y0 = (constants::bigA * h - constants::alpha0 * mass_y[1]) / (constants::alpha1 * h - constants::alpha0);

	for (int i{}; i <= n; i++)
	{
		std::cout << "|" << std::setw(2) << std::left << i <<
			"|" << std::setw(5) << "" << std::left << std::setw(5) << mass_x[i] << std::setw(5) << "" << std::right <<
			"|" << std::setw(15) << std::setprecision(10) << mass_y[i];

		if (i == 0 || i == n)
			std::cout << "|" << std::setw(15) << std::setprecision(10) << "" <<
			"|" << std::setw(15) << "" <<
			"|" << std::setw(15) << "";
		else
			std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_m[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_r[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_phi[i];


		if (i == n)
			std::cout << "|" << std::setw(15) << std::setprecision(10) << "" <<
			"|" << std::setw(15) << std::setprecision(10) << "";
		else
			std::cout << "|" << std::setw(15) << std::setprecision(10) << mass_c[i] <<
			"|" << std::setw(15) << std::setprecision(10) << mass_d[i];
		std::cout << "|" << std::endl;
		std::cout << std::string(116, '_') << std::endl;
	}
	//Сравнение y0 (по формуле) и yi[0] (по обратному ходу метода прогонки)
	std::cout << std::endl << "Сравнение значений y0 (полученное по формуле из первого краевого условия) и yi[0] (полученное по обратному ходу метода прогонки):" << std::endl;
	std::cout << "y0 = " << std::setprecision(10) << y0 << "\n" << "yi[0] = " << std::setprecision(10) << mass_y[0] << "\n" << "|y0 - yi[0]| = " << std::fixed << std::setprecision(10) << abs(y0 - mass_y[0]) << std::endl << std::endl;
	std::cout << std::defaultfloat;

	delete[] mass_x;
	delete[] mass_p;
	delete[] mass_q;
	delete[] mass_f;
	delete[] mass_m;
	delete[] mass_r;
	delete[] mass_phi;
	delete[] mass_c;
	delete[] mass_d;
	delete[] mass_y;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	
	//n1 = 10, n2 = 20
	int n1{ 10 }, n2{ 20 };

	std::cout << "\nn = " << n1 << ":\n";
	printTable();
	sweep_method(n1);

	std::cout << "\nn = " << n2 << ":\n";
	printTable();
	sweep_method(n2);
	return 0;
}
