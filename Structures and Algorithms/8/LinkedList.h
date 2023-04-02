#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//динамические двунаправленные закольцованные списки с заголовочным элементом

struct Node //sublist
{
	int data{};
	Node* next{ nullptr };
	Node* prev{ nullptr };
};

struct NodeOfList //list
{
	int listData{};
	Node* head{ nullptr }; //ref to the sublist
	NodeOfList* next{ nullptr };
	NodeOfList* prev{ nullptr };
};

int getValue();
bool isListEmpty(NodeOfList* listHead); //main list
bool isSublistEmpty(Node* sublistHead); //sublist
void addElementToMainList(NodeOfList* listHead);
void addElementToSublist(Node* sublistHead);
void showSublist(Node* sublistHead);
void showMainList(NodeOfList* listHead);
void removeElementFromMainList(NodeOfList* listHead);
void removeElementFromSublist(Node* sublistHead);
void deleteSublist(Node* sublistHead);
int searchInList(NodeOfList* listHead, int searchItem);
int searchInSublist(Node* sublistHead, int searchItem);

#endif // !LINKEDLIST_H
