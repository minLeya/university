#include "Menu.h"
#include <iostream>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1. Check if the main list is empty.\n" 
		"2. Check if the auxiliary list is empty.\n" <<
		"3. Add the element.\n" <<
		"4. Remove the element.\n" <<
		"5. Search for the element.\n" <<
		"6. Show the main list.\n" <<
		"7. Show the auxiliary list.\n" <<
		"8. Exit.\n";
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
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 7 || choice == 8)
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

void remove(Node* head, Node* auxiliary)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty, you cannot delete\n";
	}
	else
	{
		show(head);
		
		moveElement(head, auxiliary);
		std::cout << '\n';
	}
}

void search(Node* head)
{
	if (isEmpty(head))
	{
		std::cout << "\nThe list is empty, you cannot search!\n\n";
	}
	else
	{
		show(head);
		std::cout << "Enter the number you want to find in list: ";
		int number{ getChoice() };
		int index = searchForElement(head, number);
		if (index != -1)
			std::cout << number << " is found " << "\n\n";
		else
			std::cout << "\nThere is no such element in list!\n";
	}
}

void show(Node* head)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty!\n\n";
		return;
	}
		
	std::cout << "\nThe list looks like that:\n";
	showList(head);
	std::cout << "\n\n";
}

void menu(Node* head, Node* auxiliary)
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase())
		{
		case 1:
			printIsEmpty(head);
			break;

		case 2:
			printIsEmpty(auxiliary);
			break;

		case 3:
			add(head);
			break;

		case 4:
			remove(head, auxiliary);
			break;

		case 5:
			search(head);
			break;

		case 6:
			show(head);
			break;

		case 7:
			show(auxiliary);
			break;

		case 8:
			cycle = false;
		}
	}
}