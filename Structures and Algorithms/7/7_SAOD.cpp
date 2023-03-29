#include <iostream>
#include "Menu.h"
//линейный динамический двунаправленный список с закольцованным заголовочным элементом


int main()
{
	Node* head{ new Node{} };
	head->next = head;
	head->prev = head;
	menu(head);
	freeUpMemory(head);
	return 0;
}
