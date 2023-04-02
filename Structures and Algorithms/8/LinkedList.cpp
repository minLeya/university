#include "LinkedList.h"
#include <iostream>

int getValue()
{
	int value{};
	std::cin >> value;
	return value;
}

bool isListEmpty(NodeOfList* listHead) //main list
{
	return (listHead->next == listHead);
}

bool isSublistEmpty(Node* sublistHead) //sublist
{
	return (sublistHead->next == sublistHead);
}

void addElementToSublist(Node* sublistHead)
{
	//current->head == Node* sublistHead

	if (isSublistEmpty(sublistHead)) //the first real element
	{
		std::cout << "\nEnter new element: ";
		int newItem{ getValue() };

		Node* newNode{ new Node{} };
		sublistHead->next = newNode;
		sublistHead->prev = newNode;
		newNode->data = newItem;
		newNode->next = sublistHead;
		newNode->prev = sublistHead;
	}
	else
	{
		std::cout << "\nEnter 1 to add before element, enter 2 to add after: ";
		int choice{ getValue() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the number before which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ sublistHead->next };
			while (current != sublistHead && current->data != currentItem)
			{
				current = current->next;
			}

			if (current == sublistHead)
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
			current->prev->next = newNode;
			current->prev = newNode;

		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the number about which you'd like to add new element: ";
			int currentItem{ getValue() };

			Node* current{ sublistHead->next };
			while (current != sublistHead && current->data != currentItem)
			{
				current = current->next;
			}

			if (current == sublistHead)
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

void addElementToMainList(NodeOfList* listHead)
{
	if (isListEmpty(listHead)) //the first real element
	{
		std::cout << "\nEnter new element: ";
		int newItem{ getValue() };

		NodeOfList* newNodeOfList{ new NodeOfList{} };
		newNodeOfList->head = new Node{};

		newNodeOfList->listData = newItem;
		newNodeOfList->next = listHead;
		newNodeOfList->prev = listHead;
		newNodeOfList->head->next = newNodeOfList->head;
		newNodeOfList->head->prev = newNodeOfList->head;
		listHead->next = newNodeOfList;
		listHead->prev = newNodeOfList;
	}
	else
	{
		std::cout << "\nEnter 1 to add before element, enter 2 to add after: ";
		int choice{ getValue() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the number before which you'd like to add new element: ";
			int currentItem{ getValue() };

			NodeOfList* current{ listHead->next };
			while (current != listHead && current->listData != currentItem)
			{
				current = current->next;
			}

			if (current == listHead)
			{
				std::cerr << "\There's no such element in the list!\n";
				return;
			}

			std::cout << "\nEnter new element: ";
			int newItem{ getValue() };

			NodeOfList* newNodeOfList{ new NodeOfList{} };
			newNodeOfList->head = new Node{};
			newNodeOfList->listData = newItem;
			newNodeOfList->next = current;
			newNodeOfList->prev = current->prev;
			current->prev->next = newNodeOfList;
			current->prev = newNodeOfList;

			newNodeOfList->head->next = newNodeOfList->head;
			newNodeOfList->head->prev = newNodeOfList->head;


		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the number after which you'd like to add new element: ";
			int currentItem{ getValue() };

			NodeOfList* current{ listHead->next };
			while (current != listHead && current->listData != currentItem)
			{
				current = current->next;
			}

			if (current == listHead)
			{
				std::cerr << "\There's no such element in the list!\n";
				return;
			}

			std::cout << "\nEnter new element: ";
			int newItem{ getValue() };

			NodeOfList* newNodeOfList{ new NodeOfList{} };
			newNodeOfList->head = new Node{};

			newNodeOfList->listData = newItem;
			newNodeOfList->next = current->next;
			newNodeOfList->prev = current;
			current->next->prev = newNodeOfList;
			current->next = newNodeOfList;

			newNodeOfList->head->next = newNodeOfList->head;
			newNodeOfList->head->prev = newNodeOfList->head;
		}
		else
		{
			std::cerr << "\nInput error, please repeat!\n";
		}
	}
}

void showSublist(Node* sublistHead)
{
	if (isSublistEmpty(sublistHead))
	{
		std::cout << "this sublist is empty!";
	}
	else
	{
		Node* current{ sublistHead->next };
		while (current != sublistHead)
		{
			std::cout << current->data << " ";
			current = current->next;
		}
	}
}

void showMainList(NodeOfList* listHead)
{
	if (isListEmpty(listHead))
	{
		std::cout << "\nThe list is empty! There's nothing to print!\n";
		return;
	}
	
	NodeOfList* current{ listHead->next };
	while (current != listHead)
	{
		std::cout << "[" << current->listData << "] ";
		showSublist(current->head);
		current = current->next;
		std::cout << '\n';
	}
	std::cout << '\n';
}

void removeElementFromMainList(NodeOfList* listHead)
{
	if (isListEmpty(listHead))
	{
		std::cerr << "\nThe main list is empty, you cannot delete!\n";
		return;
	}
	std::cout << "\nEnter the value of  the list you'd like to delete: ";
	int deleteItem{ getValue() };
	NodeOfList* current{ listHead->next };

	while (current != listHead && current->listData != deleteItem)
		current = current->next;

	if (current == listHead)
		std::cerr << "\nthere's no such element in the list!\n";
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
		deleteSublist(current->head);
		delete current;
	}
}

void removeElementFromSublist(Node* sublistHead)
{
	if (isSublistEmpty(sublistHead))
	{
		std::cerr << "\nThe sublist is empty, you cannot delete!\n";
		return;
	}
	std::cout << "\nEnter the number you want to delete: ";
	int deleteItem{ getValue() };
	Node* current{ sublistHead->next };

	while (current != sublistHead && current->data != deleteItem)
		current = current->next;

	if (current == sublistHead)
	{
		std::cerr << "\nthere's no such element!\n";
		return;
	}
	current->prev->next = current->next;
	current->next->prev = current->prev;
	delete current;
}

void deleteSublist(Node* sublistHead)
{
	Node* current{};
	sublistHead->prev->next = nullptr;
	while (sublistHead != nullptr)
	{
		current = sublistHead;
		sublistHead = sublistHead->next;
		delete current;
	}
}

//int searchInList(NodeOfList* listHead, int searchItem)
//{
//	int subIndex{};
//	int index{ 1 };
//	NodeOfList* current{ listHead->next };
//	while (current != listHead && current->listData != searchItem)
//	{
//		subIndex = searchInSublist(current->head, searchItem);
//		current = current->next;
//		index++;
//	}
//	if (current == listHead && subIndex == -1) //no such element in the list and sublist
//		return -1;
//	else if (current == listHead && subIndex != -1)
//		return index;
//	else if (current != listHead && subIndex == -1)
//		return index;
//	else if (current != listHead && subIndex != -1)
//		return index;
//}

int searchInSublist(Node* sublistHead, int searchItem)
{
	Node* temp{ sublistHead->next };

	int index{1};
	//Node* temp{ sublistHead->next };
	while (temp != sublistHead && sublistHead->data != searchItem)
	{
		temp = temp->next;
		index++;
	}
	if (temp == sublistHead)
		return -1;
	else return index;
}