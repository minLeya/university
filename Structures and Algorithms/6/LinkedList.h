#ifndef LINKEDLIST_H
#define LNKEDLIST_H

struct Node
{
	int data{};
	Node* next{ nullptr };
};

int getChoice();
int getValue();
bool isEmpty(Node* head);
void addElement(Node* head);
void showList(Node* head);
void deleteElement(Node* head);
void moveElement(Node* head, Node* auxiliary);
int searchForElement(Node* head, int searchItem);
void freeUpMemory(Node* head);
#endif