#include <random>
#include <iostream>
#include <algorithm>
#include "SortingAlgorithms.h"
#include "Menu.h"

namespace rnd
{
	std::mt19937 mt{ std::random_device{}() };

	int get(int min, int max)
	{
		std::uniform_int_distribution range{ min, max };
		return range(mt);
	}
}

void menuText()
{
	std::cout << "what do you want to do?\n";
	std::cout << "1. sort by simple bucket method.\n";
	std::cout << "2. sort by generic bucket method.\n";
	std::cout << "3. sort by radix sort.\n";
	std::cout << "4. exit.\n";
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

bool generateVectorForRadix(std::vector<int>& numbers)
{
	numbers.clear();
	std::cout << "\nenter number digits: ";
	int numberOfDigits{ getNumber() };
	if (numberOfDigits < 1 || numberOfDigits > 9)
	{
		std::cout << "incorrect number of digits\n";
		return false;
	}
	std::cout << "\nenter number of elements: ";
	int numberOfElements{ getNumber() };
	numbers.reserve(numberOfElements);

	for (int i{ 0 }; i < numberOfElements; ++i)
		numbers.push_back(rnd::get(0, static_cast<int>(std::pow(10.0, static_cast<double>(numberOfDigits)) - 1)));

	return true;
}

//с повтором чисел
void makeVector(std::vector<int>& numbers)
{
	numbers.clear();
	std::cout << "\nenter number of elements to generate: ";
	int numberOfElements{ getNumber() };
	numbers.reserve(numberOfElements);

	for (int i{ 0 }; i < numberOfElements; ++i)
		numbers.push_back(rnd::get(0, numberOfElements));
}

//без повтора чисел
void generateUniformDistribution(std::vector<int>& numbers)
{
	std::cout << "\nenter number of elements to generate: ";
	int numberOfElements{ getNumber() };
	numbers.clear();

	for (int i{ 0 }; i < numberOfElements; ++i)
		numbers.push_back(i);

	std::shuffle(numbers.begin(), numbers.end(), rnd::mt);
}

void handleSorting(std::vector<int>& numbers, int command)
{
	switch (command)
	{
	case 1:
	{
		generateUniformDistribution(numbers); 

		std::cout << "\n0: use secondary array";
		std::cout << "\n1: don't use secondary array\n";
		int option{ getNumber() };

		std::cout << "\noriginal:\n";
		printVector(numbers);
		bucketSort(numbers, option);
		break;
	}
	case 2:
	{
		makeVector(numbers);

		std::cout << "\noriginal:\n";
		printVector(numbers);
		genericBucketSort(numbers);
		break;
	}
	case 3:
	{
		if (generateVectorForRadix(numbers))
		{
			std::cout << "\noriginal:\n";
			printVector(numbers);
			radixSort(numbers);
		}
		break;
	}
	}
}

void run()
{
	std::vector<int> numbers{};

	int command{};
	while (command != 5)
	{
		menuText();
		command = getNumber();
		handleSorting(numbers, command);
	}
}