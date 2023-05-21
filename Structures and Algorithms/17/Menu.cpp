#include "Menu.h"
#include "HashTable.h"

#include <iostream>


void textForMenu()
{
	std::cout << "1. add a key to the table\n";
	std::cout << "2. find an element in the table\n";
	std::cout << "3. print the table\n";
	std::cout << "4. fill the table completely\n";
	std::cout << "-1. exit\n";
}

std::string getString()
{
	std::string newString{};
	std::cin >> newString;
	return newString;
}

void menuAdd(HashTable& table)
{
	std::cout << "\nenter the key to add: ";
	std::string newValue{ getString() };
	auto add{ addToTable(table, newValue) };
	if (add)
	{
		std::cout << "\nthe number of comparisons: " << add.value() << "\n\n";
	}
}

void menuSearch(HashTable& table)
{
	std::cout << "\nenter the key to find: ";
	std::string valueToFind{ getString() };
	if (findInTable(table, valueToFind))
	{
		std::cout << "\nthe key " << valueToFind << " is found\n\n";
	}
	else
	{
		std::cout << "\nthe key " << valueToFind << " is not in the table\n\n";
	}
}

void menuPrint(HashTable& table)
{
	std::cout << "\nthe table looks like that:\n";
	showTable(table);
	std::cout << '\n';
}

void menu(HashTable& table, int choice)
{
	switch (choice)
	{
	case 1:
		menuAdd(table);
		break;
	case 2:
		menuSearch(table);
		break;
	case 3:
		menuPrint(table);
		break;
	case 4:
		fillTable(table);
		break;
	}
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

void run()
{
	HashTable table{};
	for (int i{ 0 }; i < constants::tableSize; ++i)
		table.array[i] = "-";

	int choice{};
	while (choice != -1)
	{
		textForMenu();
		choice = getNumber();
		menu(table, choice);
	}
}