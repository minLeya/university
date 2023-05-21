#include "HashTable.h"
#include <iostream>

void hashFunction(int& index)
{
	index %= constants::tableSize;
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

bool isValueCorrect(const std::string& value)
{
	for (auto& key : Keys::keys)
	{
		if (key == value)
			return true;
	}
	return false;
}

void addToTable(HashTable& table, const std::string& newValue)
{
	if (!isValueCorrect(newValue))
	{
		std::cout << "\nthere's no such key\n";
		return;
	}

	if (table.size == constants::tableSize)
	{
		std::cout << "\nthe table is full\n";
		return;
	}

	int numberOfComparisons{ 0 };
	int index{ getIndex(newValue) }; //индекс введенного элемента
	int currentIndex{ index }; 
	int i{ 1 };
	while (table.array[currentIndex] != "-" && i <= constants::tableSize - 2) //rule in the task
	{
		++numberOfComparisons;
		currentIndex = ((index + i) % i) ;
		++i;
	}

	table.array[currentIndex] = newValue;
	++table.size;

	std::cout << "\nnumber of comparisons: " << numberOfComparisons << '\n';
}

bool findInTable(const HashTable& table, const std::string& value)
{
	int valueIndex{ getIndex(value) }; //индекс введенного ключа 
	int numberOfComparisons{ 0 };
	int i{ 0 };
	while (i <= constants::tableSize - 1)
	{
		++numberOfComparisons;
		if (table.array[valueIndex] == value)
		{
			std::cout << "\nnumber of comparisons: " << numberOfComparisons << 'n';
			return true;
		}
		++valueIndex;
		valueIndex %= constants::tableSize; //чтобы не выходило за пределы хеш-таблицы
		++i;
	}
	std::cout << "\nnumber of comparisons: " << numberOfComparisons << '\n';
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