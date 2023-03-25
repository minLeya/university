#include "Menu.h"
#include <iostream>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the list is empty.\n"
		"2) Add the element.\n" <<
		"3) Remove the element.\n" <<
		"4) Search for the element.\n" <<
		"5) Show the main list.\n" <<
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

void remove(Node* head, Node* auxiliary)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty, you cannot delete\n";
	}
	else
	{
		std::cout << "\nEnter 1 to delete the element, enter 2 to move element to auxiliary list: ";
		int choice{ getChoice() };
		show(head);
		if (choice == 1)
		{
			deleteElement(head);
			std::cout << '\n';
		}
		else if (choice == 2)
		{
			moveElement(head, auxiliary);
			std::cout << '\n';
		}
		else
		{
			std::cout << "\ninput error, please repeat!\n";
		}
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
		std::cout << "\nEnter the number you want to find in list: ";
		int number{ getChoice() };
		int index = searchForElement(head, number);
		if (index != -1)
			std::cout << number << "is found, it's index is " << index << '\n';
		else
			std::cout << "There is no element in list!\n";
	}
}

void show(Node* head)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty!\n\n";
		return;
	}
	std::cout << "\nEnter 1 to print the list in the forward, 2 - in the reverse direction: ";
	int option{ getNumber() };
	std::cout << "\nThe list looks like that:\n";
	showList(head, option);
	std::cout << '\n';
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
			add(head);
			break;

		case 3:
			remove()
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