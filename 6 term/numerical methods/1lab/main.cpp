#include <iostream>
#include "myfuncs.h"
#include "constants.h"

int main()
{
	setlocale(LC_ALL, "Rus");

	//������� n1 = 10, n2 = 20.
	int n1{ 10 }, n2{ 20 };
	double epsilon1{ 1e-6 };
	double epsilon2{ 1e-8 };

		//��� n = 10.
	std::cout << "\n������ ������, �����-����� 4-�� ������� �������� ��� ��������� � ������ " <<
		"��� n = " << n1 << ":\n";
	printTableOne();
	FirstTable_methods(n1);
	std::cout << std::endl;
	//��� n = 20.
	std::cout << "\n��� n = " << n2 << ":" << std::endl;
	printTableOne();
	FirstTable_methods(n2);

	std::cout << std::endl;

	//����� ������ �������.
	std::cout << std::endl << "����� �����-����� 4-�� ������� �������� � ���������� " <<
		"��� n = " << n1 << ", h = " << (b - a) / n1 << " � epsilon = " << epsilon1 << ":\n";
	printTableTwo();
	SecondTable_methods(n1, epsilon1);
	std::cout << std::endl;

	std::cout << std::endl << "����� �����-����� 4-�� ������� �������� � ���������� " <<
		"��� n = " << n2 << ", h = " << (b - a) / n2 << " � epsilon = " << epsilon2 << ":\n";
	printTableTwo();
	SecondTable_methods(n2, epsilon2);

	
	return 0;
}