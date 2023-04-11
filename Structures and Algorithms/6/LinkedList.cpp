#include "LinkedList.h"
#include <iostream>

//односвязный линейный список c заголовочным элементом без кольца, динамическое распределение памяти
//есть вспомогательный список - stack, куда заносятся удаленные с главного списка элементы 
//+ функция перемещения

bool isEmpty(Node* head)
{
	return (head->next == nullptr);
}

int getChoice()
{
	int choice{};
	std::cin >> choice;
	return choice;
}

int getValue()
{
	int number{};
	std::cin >> number;
	return number;
}

void addElement(Node* head)
{
	if (isEmpty(head)) // after
	{
		std::cout << "\nEnter new element: ";
		int newItem{ getValue() };

		Node* newNode{ new Node{} };
		newNode->data = newItem;
		newNode->next = nullptr;
		head->next = newNode;
	}
	else//not empty
	{
		std::cout << "\nLook at the list:\n";
		showList(head);
		
		std::cout << "\n\nEnter 1 to add before element, enter 2 to add after: ";
		int choice{ getChoice() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the number about which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ head->next };
			Node* previous{ head };

			while (current != nullptr && current->data != currentItem)
			{
				current = current->next;
				previous = previous->next;
			}
			if (current == nullptr)
				std::cerr<<"\nthere's no such element in the list!\n";
			else
			{
				std::cout << "\nEnter new element: ";
				int newItem{ getValue() };

				Node* newNode{ new Node{} };
				newNode->data = newItem;
				newNode->next = current;
				previous->next = newNode;
			}

		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the number about which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ head->next };
			while (current != nullptr && current->data != currentItem)
				current = current->next;

			if (current == nullptr)
				std::cout << "\nThere's no such element!\n";
			else
			{
				std::cout << "\nEnter new element: ";
				int newItem{ getValue() };

				Node* newNode{ new Node{} };
				newNode->next = current->next;
				newNode->data = newItem;
				current->next = newNode;
			}
		}
		else
		{
			std::cerr << "\ninput error, repeat again!\n";
		}
	}
}

void showList(Node* head)
{
	if (isEmpty(head))
		std::cerr << "\nThe list is empty!\n";

	else
	{
		Node* current{ head->next };
		while (current != nullptr)
		{
			std::cout << current->data << ' ';
			current = current->next;
		}
	}
}

void deleteElement(Node* head)
{
	if (isEmpty(head))
	{
		std::cerr << "\nThe list is empty! You cannot delete!\n";
	}
	else
	{
		std::cout << "Enter the number to delete: ";
		int deleteItem{ getValue() };

		Node* current{ head->next };
		Node* previous{ head };

		while (current != nullptr && current->data != deleteItem)
		{
			current = current->next;
			previous = previous->next;
		}
		if (current == nullptr)
		{
			std::cout << "\nThere's no such element!\n";
		}
		else
		{
			previous->next = current->next;
			delete current;
		}
	}
}

void moveElement(Node* head, Node* auxiliary)
{
	std::cout << "Enter the number to move: ";
	int moveItem{ getValue() };
	Node* current{ head->next };
	Node* previous{ head };

	while (current != nullptr && current->data != moveItem)
	{
		current = current->next;
		previous = previous->next;
	}
	if (current == nullptr)
	{
		std::cout << "\nThere's no such element!\n";
	}
	else
	{
		previous->next = current->next;
		current->next = auxiliary->next;
		auxiliary->next = current;
	}
}

int searchForElement(Node* head, int searchItem)
{
	Node* current{ head->next };
	int index{ 1 };
	while (current != nullptr && current->data != searchItem)
	{
		current = current->next;
		index++;
	}
	if (current == nullptr)
		return -1;

	else return index;
}

void freeUpMemory(Node* head)
{
	Node* current{};
	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
}