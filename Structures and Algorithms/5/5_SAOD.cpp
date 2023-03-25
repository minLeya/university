#include <iostream>
#include "LinkedList.h"
#include "Menu.h"

int main()
{
	LinkedList list{};
	initialize(list);
	menu(list);
	return 0;
}