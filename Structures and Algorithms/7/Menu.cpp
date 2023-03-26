#include "Menu.h"
#include <iostream>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the list is empty.\n"
		"2) Add the element.\n" <<
		"3) Remove the element.\n" <<
		"4) Search for the element.\n" <<
		"5) Show the list.\n" <<
		"6) Exit.\n";
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
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6)
		{
			return choice;
		}
		else
		{
			std::cout << "\nInput error, please repeat:\n";
		}
	}
}

void printIsEmpty(Node* head)
{
	if (isEmpty(head))
		std::cout << "\nThe list is empty!\n\n";
	else
		std::cout << "\nThe list is not empty!\n\n";
}

void add(Node* head)
{
	addElement(head);
	std::cout << '\n';
}

void remove(Node* head)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty, you cannot delete\n\n";
	}
	else
	{
		show(head);
		deleteElement(head);
	}
}

void search(Node* head)
{
	if (isEmpty(head))
	{
		std::cout << "\nThe list is empty, you cannot search!\n\n";
		return;
	}
	
	std::cout << "\nEnter 1 to search in the forward, 2 - int the reverse direction: ";
	int option{};
	std::cin >> option;

	std::cout << "\nEnter the number you want to find in list: ";
	int number{ getNumber() };

	int index = searchForElement(head, option, number);
	if (index != -1)
		std::cout << number << " is found, it's index is " << index << "\n\n";
	else
		std::cout << "\nThere is no such element in list!\n";

}

void show(Node* head)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty!\n\n";
		return;
	}
	std::cout << "\nEnter 1 to print the list in the forward, 2 - in the reverse direction: ";
	int option{};
	std::cin >> option;
	std::cout << "\n";
	showList(head, option);
	std::cout << '\n';
}

void menu(Node* head)
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase())
		{
		case 1:
			printIsEmpty(head);
			break;

		case 2:
			add(head);
			break;

		case 3:
			remove(head);
			break;

		case 4:
			search(head);
			break;

		case 5:
			show(head);
			break;

		case 6:
			cycle = false;
		}
	}
}