#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <array>
#include <string>


namespace constants
{
	constexpr int size{ 10 };
}

namespace Keys
{
	inline std::array <std::string, constants::size> keys
	{   "int", 
		"inline",
		"bool", 
		"new",
		"explicit",
		"void",
		"else",
		"private",
		"struct",
		"case"
	};
}

struct HashTable
{
	std::string array[constants::size]{};
};


void addToTable(HashTable& table, const std::string& newValue);
bool findInTable(const HashTable& table, const std::string& value);
void showTable(const HashTable& table);
void fillTable(HashTable& table);
void removeFromTable(HashTable& table, const std::string& valueToDelete);
#endif // !HASHTABLE_H
