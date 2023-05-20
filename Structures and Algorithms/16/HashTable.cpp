#include "HashTable.h"

#include <iostream>


void hashFunction(int& index)
{
	index %= 10;
}

int getIndex(const std::string& value)
{
	int index{};
	for (auto& character : value)
	{
		index += static_cast<int>(character);
	}
	hashFunction(index);

	return index;
}

//проверка
bool isValueCorrect(const std::string& value)
{
	for (auto& key : Keys::keys)
	{
		if (key == value)
			return true;
	}
	return false;
}

void addToTable(HashTable& table,const std::string& newValue)
{
	if (!isValueCorrect(newValue))
	{
		std::cout << "\nthere's no such key\n";
		return;
	}
	bool isInTable{ findInTable(table, newValue) };
	if (isInTable)
	{
		std::cout <<'\n' << newValue << " is already in the table\n";
		return;
	}
	int index{ getIndex(newValue) };
	table.array[index] = newValue;
}

bool findInTable(const HashTable& table, const std::string& value)
{
	int valueIndex{ getIndex(value) };
	if (table.array[valueIndex] == value)
	{
		return true;
	}
	return false;
}

void showTable(const HashTable& table)
{
	for (auto& element : table.array)
	{
		std::cout << element << ' ';
	}
	std::cout << '\n';
}

void fillTable(HashTable& table)
{
	for (auto& key : Keys::keys)
	{
		addToTable(table, key);
	}
}

void removeFromTable(HashTable& table, const std::string& valueToRemove)
{
	if (!isValueCorrect(valueToRemove))
	{
		std::cout << "\nthere's no such key\n\n";
		return;
	}
	bool isInTable{ findInTable(table, valueToRemove) };
	if (!isInTable)
	{
		std::cout << "\nthere's no such element in the table\n\n";
		return;
	}
	int index{ getIndex(valueToRemove) };
	table.array[index] = "-";
}