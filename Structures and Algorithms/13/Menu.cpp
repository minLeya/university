#include <random>
#include <iostream>

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
	std::cout << "1. sort by bubble method.\n";
	std::cout << "2. sort by selection method.\n";
	std::cout << "3. sort by insertion method.\n";
	std::cout << "4. make vector.\n";
	std::cout << "5. exit.\n";
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

void makeVector(std::vector<int>& numbers)
{
	numbers.clear();
	std::cout << "\nenter number of elements to generate: ";
	int numberOfElements{ getNumber() };
	numbers.reserve(numberOfElements);

	for (int i{ 0 }; i < numberOfElements; ++i)
		numbers.push_back(rnd::get(0, numberOfElements));
}

void handleSorting(const std::vector<int>& numbers, int command)
{
	if (numbers.empty())
	{
		std::cout << "\nthe array is empty, cannot sort\n";
		return;
	}

	std::cout << "\noriginal:\n";
	printVector(numbers);

	switch (command)
	{
	case 1:
		bubbleSort(numbers);
		break;
	case 2:
		selectionSort(numbers);
		break;
	case 3:
		insertionSort(numbers);
		break;
	}
}


void menu(std::vector<int>& numbers, int command)
{
	bool cycle{ true };
	switch (command)
	{
	case 1:
		handleSorting(numbers, command);
		break;
	case 2:
		handleSorting(numbers, command);
		break;
	case 3:
		handleSorting(numbers, command);
		break;
	case 4:
		makeVector(numbers);
		break;
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
		menu(numbers, command);
	}
}