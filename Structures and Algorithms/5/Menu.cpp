#include "Menu.h"

#include "Menu.h"
#include <iostream>
#include <string>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the list is empty.\n" <<
		"2) Check if the list is full.\n" <<
		"3) Add the element.\n" <<
		"4) Remove the element.\n" <<
		"5) Search for the element.\n" <<
		"6) Show.\n" <<
		"7) Exit.\n";
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

int getCase()
{
	while (true)
	{
		menuForChoices();
		std::cout << "Your choice is: ";
		int choice = getNumber();
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7)
		{
			return choice;
		}
		else
		{
			std::cout << "\nInput error, please repeat:\n";
		}
	}
}

void printIsEmpty(LinkedList& list)
{
	if (isEmpty(list))
		std::cout << "\nThe list is empty!\n\n";
	else
		std::cout << "\nThe list is not empty!\n\n";
}

void printIsFull(LinkedList& list)
{
	if (isFull(list))
		std::cout << "\nThe list is full!\n\n";
	else
		std::cout << "\nThe list is not full!\n\n";
}

void add(LinkedList& list)
{
	addElement(list);
	std::cout << '\n';
}

void remove(LinkedList& list)
{
	removeElement(list);
	std::cout << '\n';
}

void search(LinkedList& list)
{
	if (isEmpty(list))
	{
		std::cout << "\nThe list is empty, you cannot search!\n\n";
	}
	else
	{
		std::cout << "\nEnter the number you want to find in list: ";
		int number{};
		std::cin >> number;
		int index = searchForElement(list, number);
		if (index != -1)
			std::cout << number << "is found, it's index is " << index << '\n';
		else
			std::cout << "There is no element in list!\n";
	}
}

void show(LinkedList& list)
{
	if (isEmpty(list))
		std::cerr << "\nThe list is empty!\n\n";
		return;

	std::cout << "\nThe list looks like that:\n";
	showList(list);
	std::cout << '\n';
}

void menu(LinkedList& list)
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase())
		{
		case 1:
			printIsEmpty(list);
			break;

		case 2:
			printIsFull(list);
			break;

		case 3:
			add(list);
			break;

		case 4:
			remove(list);
			break;

		case 5:
			search(list);
			break;

		case 6:
			show(list);
			break;

		case 7:
			cycle = false;
		}
	}
}