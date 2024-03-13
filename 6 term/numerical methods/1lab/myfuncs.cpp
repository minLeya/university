#include <iostream>
#include <iomanip>
#include <string>
#include "myfuncs.h"
#include "constants.h"

void printTableOne()
{
	std::cout << std::string(144, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^Э     " <<
		"|" << std::setw(20) << "     |yi - yi^Э|    " <<
		"|" << std::setw(15) << "yi^(Р-К)  " <<
		"|" << std::setw(20) << "   |yi - yi^(Р-К)|  " <<
		"|" << std::setw(15) << "yi^А     " <<
		"|" << std::setw(20) << "     |yi - yi^А|    " <<
		"|" << std::endl;
	std::cout << std::string(144, '_') << std::endl;
}

void printTableTwo()
{
	std::cout << std::string(134, '_') << std::endl;
	std::cout << "|" << std::setw(15) << "xi     " <<
		"|" << std::setw(15) << "yi     " <<
		"|" << std::setw(15) << "yi^(Р-К)  " <<
		"|" << std::setw(20) << "   |yi - yi^(Р-К)|  " <<
		"|" << std::setw(15) << "step" <<
		"|" << std::setw(15) << "y_H      " <<
		"|" << std::setw(20) << "|yi^(Р-К) - y_H|  " <<
		"|" << std::setw(10) << " correct  " <<
		"|" << std::endl;
	std::cout << std::string(134, '_') << std::endl;
}

//Метод Эйлера, метод Рунге-Кутта без пересчета и метод Адамса
void FirstTable_methods(const int& n)
{
	double h{ (b - a) / n };
	
	//начальное условие
	double xi{ x_0 }, yi{ y_0 };

	double yi_E{ y_0 };
	double yi_RK{ y_0 };
	double yi_A{ y_0 };

	//Массивы из 4-х последних вычисленных значений xi, xi_1, xi_2, xi_3 и yi, yi_1, yi_2, yi_3 для метода Адамса
	double Adams_xi_mass[4]{}, Adams_yi_mass[4]{};

	for (int i{}; i <= n; i++)
	{
		//Начальное условие y(x0) = y0
		if (i == 0)
		{
			//Формирование значений в массивах для метода Адамса
			Adams_xi_mass[3] = xi;
			Adams_yi_mass[3] = yi;
		}

		else
		{
			//Точное значение
			yi = exp((1 - cos(2 * xi)) / 2);

			//Метод Эйлера
			yi_E = Eulers_method(xi - h, yi_E, h);

			//Метод Рунге-Кутта без пересчета
			yi_RK = RKs_method_without_recalculation(xi - h, yi_RK, h);

			//Метод Адамса
			//При i < 4 yi считаются по формуле метода Рунге-Кутта 4-го порядка точности без пересчета
			if (i < 4)
			{
				yi_A = yi_RK;

				//Формирование значений в массивах для метода Адамса
				Adams_xi_mass[3 - i] = xi;
				Adams_yi_mass[3 - i] = yi_A;
			}

			//Иначе по формуле метода Адамса
			else
			{
				yi_A = Adams_method(h, Adams_xi_mass, Adams_yi_mass);

				//Переформирование массивов для метода Адамса
				for (int i{ 3 }; i > 0; i--)
				{
					// сдвиг вправо, первый элемент - текущий
					Adams_xi_mass[i] = Adams_xi_mass[i - 1];
					Adams_yi_mass[i] = Adams_yi_mass[i - 1];
				}
				Adams_xi_mass[0] = xi;
				Adams_yi_mass[0] = yi_A;
			}
		}
		//		std::cout << std::fixed << std::setprecision(12);
		std::cout << "|" << std::setw(15) << std::setprecision(10) << xi <<
			"|" << std::setw(15) << std::setprecision(10) << yi <<
			"|" << std::setw(15) << std::setprecision(10) << yi_E <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_E) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_RK <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_RK) <<
			"|" << std::setw(15) << std::setprecision(10) << yi_A <<
			"|" << std::setw(20) << std::setprecision(10) << abs(yi - yi_A) <<
			"|" << std::endl;
		std::cout << std::string(144, '_') << std::endl;

		xi += h;
	}
}

//Метод Рунге-Кутта с пересчетом при n = 10;20
void SecondTable_methods(const int& n, const double& epsilon)
{
	double h{ (b - a) / n };
	double H{ 2 * h };

	//Начальное условие
	double xi{ x_0 };
	double yi{ y_0 };
	double yi_RK{ y_0 };

	double y_h{};
	double y_H{};

	//Массив, хранящий значения xi с шагом h на протяжении 2-х шагов
	double RK_xi_mass[3]{};

	//Массив, хранящий значения yi^(Р-К) с шагом h на протяжении 2-х шагов
	double RK_yi_mass[3]{};

	//флаг, чтобы не было дублирования 
	bool correct_ouput{};

	//Метод Рунге-Кутта 4-го порядка точности с пересчетом
	
	//Пока рассматриваемые значения xi, x_(i+1), x_(i+2) находится на [-2, -1]
	while ((xi + 2 * h) - b <= 0.000000000000001) // xi + 2h <= b
	{
		//Первые элементы массивов значений xi и yi^(Р-К) равны текущим xi и yi^(Р-К)
		RK_xi_mass[0] = xi;
		RK_yi_mass[0] = yi_RK;

		//Вычесление y_(i+1) по методу Рунге-Кутта 4-го порядка точности
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);

		//Занесение y_(i+1) в массив значений yi^(Р-К)
		RK_yi_mass[1] = yi_RK;

		//Вычисление x_(i+1)
		xi += h;

		//Занесение вычисленного x_(i+1) в массив значений xi
		RK_xi_mass[1] = xi;

		//Вычисление y_(i+2) по методу Рунге-Кутта 4-го порядка точности
		yi_RK = RKs_method_without_recalculation(xi, yi_RK, h);

		//Занесение вычисленного y_(i+2) в массив значений yi^(Р-К)
		RK_yi_mass[2] = yi_RK;

		//Вычисление x_(i+2)
		xi += h;

		//Занесение вычисленного x_(i+2) в массив значений xi
		RK_xi_mass[2] = xi;

		//Вычисление y_h (последний элемент массива значений yi^(Р-К)) и y_H с двойным шагом H (используются первые элементы массивов значений xi и yi^(Р-К))
		y_h = RK_yi_mass[2];
		y_H = RKs_method_without_recalculation(RK_xi_mass[0], RK_yi_mass[0], H);

		//Заполнение таблицы при текущем i (на протяжении 2-х шагов)
		for (int i{}; i <= 2; i++) 
		{
			//Первые элементы массивов RK_xi_mass и RK_yi_mass используются для "отката" в случае неверного выбора шага и "старта" при рассмотрении 2-х шагов на данной итерации
			//В каждой последующей итерации после первой первым элементом каждого массива является последний элемент на предыдущей итерации
			
			if (i == 0 && correct_ouput)
				continue;

			//Вычисление точного значения yi
			yi = exp((1 - cos(2 * RK_xi_mass[i])) / 2);

			std::cout << "|" << std::setw(15) << std::setprecision(10) << RK_xi_mass[i] <<
				"|" << std::setw(15) << std::setprecision(10) << yi <<
				"|" << std::setw(15) << std::setprecision(10) << RK_yi_mass[i] <<
				"|" << std::setw(20) << std::setprecision(10) << abs(yi - RK_yi_mass[i]) <<
				"|" << std::setw(15) << std::setprecision(10) << h << "|";
			if (i != 2)
				std::cout << std::setw(15) << std::setprecision(10) << "" <<
				"|" << std::setw(20) << std::setprecision(10) << "" <<
				"|" << std::setw(10) << "" <<
				"|" << std::endl;
			else
			{
				std::cout << std::setw(15) << std::setprecision(10) << y_H <<
					"|" << std::setw(20) << std::setprecision(10) << abs(y_h - y_H) << "|";
				if (abs(y_h - y_H) <= epsilon)
					std::cout << std::setw(10) << "true";
				else
					std::cout << std::setw(10) << "false";
				std::cout << "|" << std::endl;
			}
			if (!correct_ouput)
				correct_ouput = true;
			std::cout << std::string(134, '_') << std::endl;
		}

		//Проверка правильности выбора шага h
		if (abs(y_h - y_H) > epsilon)
		{
			//Отходим на два шага назад
			xi = RK_xi_mass[0];
			yi_RK = RK_yi_mass[0];

			h /= 2;

			H = 2 * h;
		}
	}
}

//Метод Эйлера
double Eulers_method(const double& xi, const double& yi, const double& h)
{
	return (yi + h * yi * sin(2 * xi));
}

//Метод Рунге-Кутта 4-го порядка точности без пересчета
double RKs_method_without_recalculation(const double& xi, const double& yi, const double& h)
{
	double K1i{ h * yi * sin(2 * xi)};
	double K2i{ h * (yi + K1i / 2) * sin(2 * (xi + h / 2)) };
	double K3i{ h * (yi + K2i / 2) * sin(2 * (xi + h / 2)) };
	double K4i{ h * (yi + K3i) * sin(2 * (xi + h)) };

	return (yi + 1.0 / 6.0 * (K1i + 2 * K2i + 2 * K3i + K4i));
}

// Метод Адамса
double Adams_method(const double& h, const double Adams_xi_mass[], const double Adams_yi_mass[])
{
	//Вычисление y'i, y'i_1, y'i_2, y'i_3.
	double yi{ Adams_yi_mass[0] }, dyi{ Adams_yi_mass[0] * sin(2 * Adams_xi_mass[0]) }, dyi_1{ Adams_yi_mass[1] * sin(2 * Adams_xi_mass[1]) },
		dyi_2{ Adams_yi_mass[2] * sin(2 * Adams_xi_mass[2])}, dyi_3{Adams_yi_mass[3] * sin(2 * Adams_xi_mass[3])};

	return (yi + h / 24.0 * (55 * dyi - 59 * dyi_1 + 37 * dyi_2 - 9 * dyi_3));
}
