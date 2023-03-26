#include <iostream>
#include "Menu.h"
//линейный динамический двунаправленный список с заголовочным элементом


int main()
{
	Node* head{ new Node{} };
	head->next = head;
	head->prev = head;
	menu(head);
	return 0;
}
