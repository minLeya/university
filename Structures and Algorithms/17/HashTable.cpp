#include "HashTable.h"
#include <iostream>

//внутреннее хеширование

int hashFunction(const std::string& value)
{
	int index{};
	for (auto& character : value)
	{
		index += static_cast<int>(character);
	}
	index %= constants::tableSize;
	return index;
}

std::optional<int> addToTable(HashTable& table, const std::string& newValue)
{
	if (table.size == constants::tableSize)
	{
		std::cout << "\nthe table is full\n";
		return std::nullopt;
	}

	int numberOfComparisons{ 0 };
	bool isInTable{ findInTable(table, newValue).first };
	if (isInTable)
	{
		std::cout << "\nthe value was found in the table\n\n";
		return std::nullopt;
	}
	int index{ hashFunction(newValue) };
	int currentIndex{ index }; 
	int i{ 1 };
	++numberOfComparisons;
	while (!table.array[currentIndex].empty())
	{
		++numberOfComparisons;
		currentIndex = (index + i) % constants::tableSize;
		++i;
	}

	table.array[currentIndex] = newValue;
	++table.size;
	
	return numberOfComparisons;
}

std::pair<bool, int> findInTable(const HashTable& table, const std::string& value)
{
	int valueIndex{ hashFunction(value) };
	int numberOfComparisons{ 0 };
	int i{ 0 };
	if (table.array[valueIndex].empty())
	{
		return { false, numberOfComparisons };
	}
	while (i <= constants::tableSize - 1)
	{
		++numberOfComparisons;
		if (table.array[valueIndex] == value)
		{
			return { true, numberOfComparisons };
		}
		++valueIndex;
		valueIndex %= constants::tableSize; 
		++i;
	}
	return { false, numberOfComparisons };
}

void showTable(const HashTable& table)
{
	for (int i{ 0 }; i < constants::tableSize; ++i)
		std::cout << i << ". " << table.array[i] << '\n';
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

	std::cout << "\nnumber of comparisons: " << numberOfComparisons << "\n\n";
}