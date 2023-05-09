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
	std::cout << "4. sort by heap method.\n";
	std::cout << "5. sort by shell method.\n";
	std::cout << "6. sort by quick method.\n";
	std::cout << "7. make vector.\n";
	std::cout << "8. exit.\n";
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
	case 4:
		heapSort(numbers);
		break;
	case 5:
		shellSort(numbers);
		break;
	case 6:
		std::vector<int> numbersCopy{ numbers };
		int numberOfComparisons{ 0 };
		int numberOfAssignments{ 0 };

		quickSort(numbersCopy, 0, static_cast<int>(numbersCopy.size() - 1),
			numberOfComparisons, numberOfAssignments);

		std::cout << "\nsorted:\n";
		printVector(numbersCopy);
		std::cout << "number of comparisons: " << numberOfComparisons << '\n';
		std::cout << "number of assignments: " << numberOfAssignments << '\n';
		break;

	}
}


void menu(std::vector<int>& numbers, int command)
{
	bool cycle{ true };
	switch (command)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		handleSorting(numbers, command);
		break;
	case 7:
		makeVector(numbers);
		break;
	case 8:
		cycle = false;
	}
}

void run()
{
	std::vector<int> numbers{};

	int command{};
	while (command != 8)
	{
		menuText();
		command = getNumber();
		menu(numbers, command);
	}
}