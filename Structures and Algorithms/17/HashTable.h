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
	inline std::array <std::string, constants::keySize> keys
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
	std::string array[constants::tableSize]{};
	int size{ 0 };
};

std::optional<int> addToTable(HashTable& table, const std::string& newValue);

bool findInTable(const HashTable& table, const std::string& value);
void showTable(const HashTable& table);
void fillTable(HashTable& table);


#endif // !HASHTABLE_H
