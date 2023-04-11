#include "Menu.h"
#include <iostream>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1. Add element to main list.\n"
		"2. Add element to the sublist.\n" <<
		"3. Remove the element from main list.\n" <<
		"4. Remove the element from sublist list.\n" <<
		"5. Search for the element.\n" <<
		"6. Show the full list.\n" <<
		"7. Exit.\n";
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

void addToMainList(NodeOfList* listHead)
{
	addElementToMainList(listHead);
	std::cout << '\n';
}

void addToSublist(NodeOfList* listHead)
{
	std::cout << "\nenter the value of the list where you'd like to add sublist's elements: ";
	int listValue{};
	std::cin >> listValue;

	NodeOfList* current{ listHead->next };
	while (current != listHead && current->listData != listValue)
	{
		current = current->next;
	}
	if (current == listHead)
	{
		std::cerr << "\nthere's no list with such value!\n";
	}
	else
	{
		addElementToSublist(current->head);
	}
	std::cout << '\n';
}

void removeFromList(NodeOfList* listHead)
{
	if (isListEmpty(listHead))
	{
		std::cerr << "\nThe list is empty, you cannot delete!\n";
		return;
	}
	removeElementFromMainList(listHead);
	std::cout << '\n';
}

void removeFromSublist(NodeOfList* listHead)
{
	std::cout << "\nenter the value of the list from which you'd like to delete element: ";
	int listValue{ getValue() };

	NodeOfList* current{ listHead->next };
	while (current != listHead && current->listData != listValue)
		current = current->next;
	if (current == listHead)
	{
		std::cout << "\nthere's no such element! try again!\n";
		return;
	}
	
	removeElementFromSublist(current->head);
	std::cout << '\n';
}

void search(NodeOfList* listHead) //only in sublists
{

	if (isListEmpty(listHead))
	{
		std::cerr << "\nThe list is empty, cannot search!\n";
		return;
	}

	std::cout << "\nEnter the number you want to find in list: ";
	int searchItem{ getNumber() };

	NodeOfList* current{ listHead->next };
	
	int numberOfFoundElements{ 0 };
	while (current != listHead)
	{
		if (findInList(current->head, searchItem))
		{
			std::cout << "found element with value " << searchItem << " in list with id " <<
				current->listData << '\n';
			++numberOfFoundElements;
		}

		current = current->next;
	}

	if (numberOfFoundElements == 0)
		std::cout << "\ncouldn't find value " << searchItem << " in any of the lists\n";
	else
		std::cout << "\nfound " << numberOfFoundElements << " elements in total\n\n";
}

void showList(NodeOfList* listHead)
{
	std::cout << '\n';
	showMainList(listHead);
}

void menu(NodeOfList* listHead)
{
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case 1:
			addToMainList(listHead);
			break;
		case 2:
			addToSublist(listHead);
			break;
		case 3:
			removeFromList(listHead);
			break;
		case 4:
			removeFromSublist(listHead);
			break;
		case 5:
			search(listHead);
			break;
		case 6:
			showList(listHead);
			break;
		case 7:
			cycle = false;
		}
	}
}

void run()
{
	NodeOfList* listHead{ new NodeOfList{} };
	listHead->head = new Node{};
	listHead->head->next = listHead->head;
	listHead->head->prev = listHead->head;
	listHead->next = listHead;
	listHead->prev = listHead;


	menu(listHead);
}