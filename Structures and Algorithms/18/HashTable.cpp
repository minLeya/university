#include "HashTable.h"

#include <iostream>

int hashFunction(const std::string& value)
{
	int index{};
	for (const auto& character : value)
		index += static_cast<int>(character);
	index %= constants::tableSize;

	return index;
}

void addToList(Node*& head, const std::string& newValue, int& numberOfComaprisons)
{
	++numberOfComaprisons;
	if (head == nullptr)
	{
		head = new Node{};
		head->data = newValue;
		head->next = nullptr;

		return;
	}

	Node* current{ head };
	++numberOfComaprisons;
	while (current->next != nullptr)
	{
		++numberOfComaprisons;
		current = current->next;
	}

	Node* newElement{ new Node{} };
	newElement->data = newValue;
	newElement->next = nullptr;
	current->next = newElement;
}

std::optional<int> addToTable(HashTable& table, const std::string& newValue)
{
	int numberOfComaprisons{ 0 };

	auto [found, valueIndex] { findInTable(table, newValue) };
	if (found)
	{
		std::cout << "the value " << newValue << " was found in the table\n";
		return std::nullopt;
	}

	int index{ hashFunction(newValue) };
	int currentIndex{ index };
	++numberOfComaprisons;
	if (!table.array[currentIndex].data.empty())
		addToList(table.array[currentIndex].head, newValue, numberOfComaprisons);
	else
		table.array[currentIndex].data = newValue;

	return numberOfComaprisons;
}

std::pair<bool, int> findInTable(const HashTable& table, const std::string& valueToFind)
{
	int numberOfComparisons{ 0 };
	int valueIndex{ hashFunction(valueToFind) };
	ElementOfHashTable tableElement{ table.array[valueIndex] };

	++numberOfComparisons;
	if (tableElement.data.empty())
		return { false, numberOfComparisons };

	++numberOfComparisons;
	if (tableElement.data == valueToFind)
		return { true, numberOfComparisons };

	Node* current{ tableElement.head };
	++numberOfComparisons;
	while (current != nullptr && current->data != valueToFind)
	{
		current = current->next;
		++numberOfComparisons;
	}

	++numberOfComparisons;
	if (current == nullptr)
		return { false, numberOfComparisons };

	return { true, numberOfComparisons };
}

bool findInList(Node* head, const std::string& valueToFind)
{
	Node* current{ head };
	while (current != nullptr)
	{
		if (current->data == valueToFind)
			return true;
		current = current->next;
	}

	return false;
}

void removeFromList(Node*& head, const std::string& valueToRemove)
{
	Node* current{ head };
	Node* previous{};

	if (current != nullptr && current->data == valueToRemove)
	{
		head = head->next;
		delete current;
		return;
	}

	while (current != nullptr && current->data != valueToRemove)
	{
		previous = current;
		current = current->next;
	}

	if (current == nullptr)
		return;

	previous->next = current->next;
	delete current;
}

void removeFromTable(HashTable& table, const std::string& valueToRemove)
{
	int valueIndex{ hashFunction(valueToRemove) };
	std::string& tableValue{ table.array[valueIndex].data };
	if (tableValue == valueToRemove)
	{
		if (table.array[valueIndex].head == nullptr)
			tableValue.clear();
		else
		{
			Node*& tableElementHead{ table.array[valueIndex].head };
			Node* temporary{ tableElementHead };
			tableValue = tableElementHead->data;
			tableElementHead = tableElementHead->next;
			delete temporary;
		}
	}
	else if (findInList(table.array[valueIndex].head, valueToRemove))
		removeFromList(table.array[valueIndex].head, valueToRemove);
	else
		std::cout << "\ncouldn't find element " << valueToRemove << " in the table\n";
}

void printList(Node* head)
{
	Node* current{ head };
	while (current != nullptr)
	{
		std::cout << current->data;
		if (current->next != nullptr)
			std::cout << ", ";
		current = current->next;
	}
	std::cout << '\n';
}

void printTable(const HashTable& table)
{
	for (int i{ 0 }; i < constants::tableSize; ++i)
	{
		std::cout << i << ". " << table.array[i].data << ": ";
		printList(table.array[i].head);
	}
	std::cout << '\n';
}

void fillTable(HashTable& table)
{
	int numberOfComaprisons{ 0 };
	for (const auto& key : Keys::keys)
	{
		auto added{ addToTable(table, key) };
		if (added)
			numberOfComaprisons += added.value();
	}

	std::cout << "\ntotal number of comparisons after filling the table: "
		<< numberOfComaprisons << '\n';
}