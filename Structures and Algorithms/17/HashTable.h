#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <array>
#include <string>
#include <optional>


namespace constants
{
	constexpr int tableSize{ 13 };
	constexpr int keySize{ 10 };

}

namespace Keys
{
	inline std::array <std::string, constants::tableSize> keys
	{   "int",
		"inline",
		"bool",
		"new",
		"explicit",
		"void",
		"else",
		"private",
		"struct",
		"case",
	};
}

struct HashTable
{
	std::string array[constants::tableSize]{};
	int size{ 0 };
};

bool findInTable(const HashTable& table, const std::string& value);
void showTable(const HashTable& table);
void fillTable(HashTable& table);
std::optional<int> addToTable(HashTable& table, const std::string& newValue);


#endif // !HASHTABLE_H
