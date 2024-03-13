#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//Задание n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 1e-6 };
	double epsilon2{ 1e-8 };

		//При n = 10.
	std::cout << "\nМетоды Эйлера, Рунге-Кутта 4-го порядка точности без пересчета и Адамса " <<
		"при n = " << n1 << ":\n";
	printTableOne();
	FirstTable_methods(n1);
	std::cout << std::endl;
	//При n = 20.
	std::cout << "\nпри n = " << n2 << ":" << std::endl;
	printTableOne();
	FirstTable_methods(n2);

	std::cout << std::endl;

	//Вывод второй таблицы.
	std::cout << std::endl << "Метод Рунге-Кутта 4-го порядка точности с пересчетом " <<
		"при n = " << n1 << ", h = " << (b - a) / n1 << " и epsilon = " << epsilon1 << ":\n";
	printTableTwo();
	SecondTable_methods(n1, epsilon1);
	std::cout << std::endl;

	std::cout << std::endl << "Метод Рунге-Кутта 4-го порядка точности с пересчетом " <<
		"при n = " << n2 << ", h = " << (b - a) / n2 << " и epsilon = " << epsilon2 << ":\n";
	printTableTwo();
	SecondTable_methods(n2, epsilon2);

	
	return 0;
}