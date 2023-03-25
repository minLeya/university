#include <iostream>
#include "Menu.h"
//линейный динамический список 


int main()
{
	Node* head{ new Node{} };
	Node* auxiliary{ new Node{} };
	menu(head, auxiliary);
	freeUpMemory(head);
	freeUpMemory(auxiliary);
	
	return 0;
}