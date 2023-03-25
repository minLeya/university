#include "LinkedList.h"
#include <iostream>

int getValue()
{
	int value{};
	std::cin >> value;
	return value;
}

bool isEmpty(Node* head)
{
	return (head->next == head); //ring
}

void addElement(Node* head)
{
	if (isEmpty(head)) //the first real element
	{
		std::cout << "\nEnter new element: ";
		int newItem{ getValue() };

		Node* newNode{ new Node{} };
		newNode->data = newItem;
		newNode->next = head;
		newNode->prev = head;
		head->next = newNode;
		head->prev = newNode;
	}
	else
	{
		std::cout << "\nEnter 1 to add before element, enter 2 to add after: ";
		int choice{ getValue() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the number about which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ head->next };
			while (current != head && current->data != currentItem)
			{
				current = current->next;
			}

			if (current == head)
			{
				std::cerr << "\There's no such element in the list!\n";
				return;
			}

			std::cout << "\nEnter new element: ";
			int newItem{ getValue() };

			Node* newNode{ new Node{} };
			newNode->data = newItem;
			newNode->next = current;
			newNode->prev = current->prev;
			current->prev = newNode;
			current->prev->next = newNode;

		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the number about which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ head->next };
			while (current != head && current->data != currentItem)
			{
				current = current->next;
			}

			if (current == head)
			{
				std::cerr << "\There's no such element in the list!\n";
				return;
			}

			std::cout << "\nEnter new element: ";
			int newItem{ getValue() };

			Node* newNode{ new Node{} };
			newNode->data = newItem;
			newNode->next = current->next;
			newNode->prev = current;
			current->next->prev = newNode;
			current->next = newNode;
		}
		else
		{
			std::cerr << "\nInput error, please repeat!\n";
		}
	}
}

void showList(Node* head, int option)
{
	if (isEmpty(head))
	{
		std::cout << "\nThe list is empty! There's nothing to print!\n";
		return;
	}
	if (option == 1) //forward
	{
		Node* current{ head->next };
		while (current != head)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
		std::cout << '\n';
	}
	else if (option == 2)//reverse
	{
		Node* current{ head->prev };
		while (current != head)
		{
			std::cout << current->data << " ";
			current = current->prev;
		}
		std::cout << '\n';
	}
}