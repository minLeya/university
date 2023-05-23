#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <array>
#include <string>
#include <optional>


namespace constants
{
	constexpr int tableSize{ 10 };
	constexpr int keySize{ 13 };

}

namespace Keys
{
	inline const std::array <std::string, constants::keySize> keys
	{   "int", "inline", "bool", "new", "explicit",
		"void", "else", "private", "struct", "case",
		"virtual", "while", "template"
	};
}

struct Node
{
	std::string data{};
	Node* next{ nullptr };
};

struct ElementOfHashTable
{
	Node* head{};
	Node* tail{};
	std::string data{};
};

struct HashTable
{
	ElementOfHashTable array[constants::tableSize]{};
};

std::optional<int> addToTable(HashTable& table, const std::string& newValue);
void removeFromTable(HashTable& table, const std::string& valueToRemove);
std::pair<bool, int> findInTable(const HashTable& table, const std::string& valueToFind);
void printTable(const HashTable& table);
void fillTable(HashTable& table);


#endif // !HASHTABLE_H