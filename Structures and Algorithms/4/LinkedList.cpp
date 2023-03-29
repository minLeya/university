#include "LinkedList.h"
#include <iostream>
//2 task from chapter 3
//упорядоченный односвязный список на основе массива, стастистическое распределение памяти
//добавление до и после заданного элемента со сдвигом
//удаление элемента со сдвигом

bool isEmpty(LinkedList& list)
{
	return (list.itemCount == 0);
}

bool isFull(LinkedList& list)
{
	return (list.itemCount == size::size);
}

int getValue()
{
	int value{};
	std::cin >> value;
	return value;
}

void addElement(LinkedList& list)
{
	if (isFull(list))
	{
		std::cerr << "\nA List is full! You cannot add any elements!\n";
	}
	//if there is no element in list, a newItem will be the first
	else if (isEmpty(list))
	{
		std::cout << "\nEnter the number to add: ";
		int newItem = getValue();
		list.array[0] = newItem;
		list.itemCount++;
	}
	//search for the place starts
	else if (!isEmpty(list) && !isFull(list)) //упорядоченный односвязный список
	{
		std::cout << "\nEnter the number to add: ";
		int newItem = getValue();
		int index{ 0 };
		//search for the least
		while (list.array[index] < newItem && index < list.itemCount) //обнаружение первого элемента, большего заданного.
		{//поиск индекса элемента который больше заданного
			index++;
		}
		if (index == size::size - 1) //or while newItem is bigger than all items
		{//если все элементы меньше заданного, он ставится в конец списка
			list.array[index] = newItem;
			list.itemCount++;
		}
		else
		{//если нашелся элемент больше заданного в середине/начале списка, происходит сдвиг вправо для освобождения 
			//ячейки массива для нового элемента
			for (int i{ list.itemCount }; i > index; i--) 
				list.array[i] = list.array[i - 1]; //перенос бо'льших значений вправо

			list.array[index] = newItem;
			list.itemCount++;
		}
	}
}

void deleteElement(LinkedList& list, int deleteItem)
{
	int deleteIndex = searchForElement(list, deleteItem); //возвращает индекс удаляемого элемента
	if (deleteIndex != - 1)
	{
		list.itemCount--;
		for (int i{ deleteIndex }; i < list.itemCount; i++) // сдвиг
		{
			list.array[i] = list.array[i + 1];
		}
	}
	else
	{
		std::cout << "\nThere is no such element!\n\n";
	}
}

void showList(LinkedList & list)
{
	if (isEmpty(list))
	{
		std::cerr << "\nThe list is empty! There is no element to show!\n";
	}
	else
	{
		for (int i{ 0 }; i < list.itemCount; i++) 
		{
			std::cout << list.array[i] << " ";
		}
		std::cout << "\n";
	}
}

int searchForElement(LinkedList& list, int searchItem) 
{
	for (int i{ 0 }; i < list.itemCount; i++)
	{
		if (list.array[i] == searchItem)
		{
			return i;
		}
	}
	return -1;
}

