#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <array>
#include <iostream>

namespace constants
{
	inline constexpr int size{ 5 };
}

struct Node
{
	int data{};
	int next{}; //-1 if free, 1 if not
};

struct LinkedList
{
	Node array[constants::size + 1]{}; //+1 для заголовка
	int itemCount{};
};

int getChoice();
int getValue();
void initialize(LinkedList& list);
bool isEmpty(LinkedList& list);
bool isFull(LinkedList& list);
int findPrevious(LinkedList& list, int currentItem);
void addElement(LinkedList& list);
void removeElement(LinkedList& list);
void showList(LinkedList& list);
int searchForElement(LinkedList& list, int searchItem);

#endif // !LINKEDLIST_J