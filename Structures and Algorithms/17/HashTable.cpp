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

std::optional<int> addToTable(HashTable& table, const std::string& newValue)
{
	if (!isValueCorrect(newValue))
	{
		std::cout << "\nthere's no such key\n\n";
		return std::nullopt;
	}

	if (table.size == constants::tableSize)
	{
		std::cout << "\nthe table is full\n\n";
		return std::nullopt;
	}

	int numberOfComparisons{ 0 };
	int index{ getIndex(newValue) }; //индекс введенного элемента
	int currentIndex{ index }; 
	int i{ 1 };
	++numberOfComparisons;
	while (table.array[currentIndex] != "-" && i <= constants::tableSize - 2) //rule in the task
	{
		++numberOfComparisons;
		currentIndex = ((index + i) % constants::tableSize);
		++i;
	}

	table.array[currentIndex] = newValue;
	++table.size;
	
	return numberOfComparisons;
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
			std::cout << "\nnumber of comparisons: " << numberOfComparisons << "\n\n";
			return true;
		}
		
		++valueIndex %= constants::tableSize; //чтобы не выходило за пределы хеш-таблицы
		++i;
	}
	std::cout << "\nnumber of comparisons: " << numberOfComparisons << "\n\n";
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
	int numberOfComparisons{ 0 };
	for (const auto& key : Keys::keys)
	{
		auto add{ addToTable(table, key) };
		if (add)
		{
			numberOfComparisons += add.value();
		}
	}

	std::cout << "\nnumber of comparisons: " << numberOfComparisons << '\n';
}