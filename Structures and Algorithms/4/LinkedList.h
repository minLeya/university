#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <array>

namespace size
{
	inline constexpr int size{ 6 };
}

struct LinkedList
{
	int array[size::size]{};
	int itemCount{};
};

//main operations with list 
bool isEmpty(LinkedList& list);
bool isFull(LinkedList& list);
void addElement(LinkedList& list);
void deleteElement(LinkedList& list, int deleteItem);
void showList(LinkedList& list);
int searchForElement(LinkedList& list, int searchItem);
int getValue();

#endif // !LINKED_LIST_H