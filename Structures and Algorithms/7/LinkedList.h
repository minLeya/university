#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct Node
{
	int data{};
	Node* next{ nullptr };
	Node* prev{ nullptr };
};

bool isEmpty(Node* head);
void addElement(Node* head);
void showList(Node* head, int option);
void deleteElement(Node* head);
int indexOfTheLastElement(Node* head);
int searchForElement(Node* head, int option, int searchItem);
int getValue();


#endif // !LINKEDLIST_H