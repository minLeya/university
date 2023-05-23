#include "HashTable.h"
//бесконфликтная хеш-таблица
#include <iostream>

int hashFunction(const std::string& value)
{
	int index{};
	for (auto& character : value)
	{
		index += static_cast<int>(character);
	}
	index %= 10;

	return index;
}

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
	int index{ hashFunction(newValue) };
	table.array[index] = newValue;
}

bool findInTable(const HashTable& table, const std::string& value)
{
	int valueIndex{ hashFunction(value) };
	if (table.array[valueIndex] == value)
	{
		return true;
	}
	return false;
}

void showTable(const HashTable& table)
{
	for (int i{0}; i<constants::size; ++i)
	{
		std::cout << i << ". " << table.array[i] << '\n';
	}
	std::cout << '\n';
}

void fillTable(HashTable& table)
{
	for (const auto& key : Keys::keys)
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
	int index{ hashFunction(valueToRemove) };
	table.array[index].clear();
}