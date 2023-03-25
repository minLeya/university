#include "LinkedList.h"

void initialize(LinkedList& list)
{
	list.array[0].data = list.array[0].next = 0;
	for (int i{ 1 }; i < constants::size + 1; i++) //0-ой элемент - заголовок
		list.array[i].next = -1;
}

bool isEmpty(LinkedList& list)
{
	if (list.itemCount == 0) return true;
	else return false;
}

bool isFull(LinkedList& list)
{
	if (list.itemCount == constants::size) return true;
	else return false;
}

int getChoice()
{
	int number{};
	std::cin >> number;
	return number;
}

int getValue()
{
	int value{};
	std::cin >> value;
	return value;
}

int findPrevious(LinkedList& list, int currentItem)
{
	int previousIndex{ 0 };
	int currentIndex{ list.array[0].next };
	while (currentIndex != 0)
	{
		if (list.array[currentIndex].data == currentItem)
			break;
		currentIndex = list.array[currentIndex].next;
		previousIndex = list.array[previousIndex].next;
	}

	return previousIndex;
}

void addElement(LinkedList& list) //before and after element :(
{
	if (isFull(list))
	{
		std::cerr << "\nThe list is full, you cannot add new element!\n";
	}
	else if (isEmpty(list))
	{
		std::cout << "\nEnter new element: ";
		int newItem{ getValue() };

		list.array[0].next = 1;
		list.array[1].data = newItem;
		list.array[1].next = 0; 
		list.itemCount++;
	}
	else
	{
		std::cout << "\nLook at the list:\n";
		showList(list);
		std::cout << "\nEnter the number about which you'd like to add new element: ";
		int currentItem{ getValue() };
		int index{ searchForElement(list, currentItem) };

		if (index == -1)
		{
			std::cerr << "\nThere is no such element\n";
		}
		else
		{
			std::cout << "\nEnter 1 to add before that element, enter 2 to add after: ";
			int choice { getChoice() };
			
			if (choice == 1) //before
			{
				int prevoiusIndex{ findPrevious(list, currentItem) };

				std::cout << "\nEnter new element: ";
				int newItem{ getValue() };

				int i{ 1 };
				while (i < constants::size + 1)
				{
					if (list.array[i].next == -1)
						break;
					i++;
				}
				list.array[i].next = index;
				list.array[i].data = newItem;
				list.array[prevoiusIndex].next = i;
				list.itemCount++;
			}

			else if (choice == 2) //after
			{
				std::cout << "\nEnter new element: ";
				int newItem{ getValue() };

				int i{ 1 }; //для нахождения свободной ячейки
				while (i < constants::size + 1)
				{
					if (list.array[i].next == -1)
						break;
					i++;
				}
				list.array[i].data = newItem;
				list.array[i].next = list.array[index].next;
				list.array[index].next = i;
				list.itemCount++;
			}

			else
				std::cerr << "\nInput error!\n";
		}
		
	}
}

void removeElement(LinkedList& list)
{
	if (isEmpty(list))
		std::cerr << "\nThe list is empty! You cannot delete!\n";
	else
	{
		std::cout << "\nLook at the list:\n";
		showList(list);
		std::cout << "\nEnter the element you'd like to delete: ";
		int deleteItem{ getValue() };
		int deleteIndex{ searchForElement(list, deleteItem) };
		if (deleteItem == -1)
			std::cerr << "\nSorry, there's no such element in the list\n\n";
		else
		{
			int previousIndex{ findPrevious(list, deleteItem) };
			list.array[previousIndex].next = list.array[deleteIndex].next;
			list.array[deleteIndex].next = -1;
			list.itemCount--;
		}
	}

}

void showList(LinkedList& list)
{
	if (isEmpty(list))
	{
		std::cerr << "\nThe list is empty! There is no element to show!\n";
	}
	else
	{
		for (int i{ list.array[0].next }; i != 0; i = list.array[i].next)
			std::cout << list.array[i].data << ' ';
		std::cout << "\n";
	}
}

int searchForElement(LinkedList& list, int searchItem)
{
	for (int index{ list.array[0].next }; index != 0; index = list.array[index].next)
	{
		if (list.array[index].data == searchItem)
			return index;
	}
	return -1;
}