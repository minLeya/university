#include "LinkedList.h"
#include "Menu.h"
#include <iostream>

int main()
{
    NodeOfList* listHead{ new NodeOfList{} };
    listHead->head = new Node{};
    listHead->head->next = listHead->head;
    listHead->head->prev = listHead->head;
    listHead->next = listHead;
    listHead->prev = listHead;


    menu(listHead);

    return 0;
}