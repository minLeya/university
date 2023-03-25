#ifndef MENU_H
#define MENU_H

#include"LinkedList.h"

void menuForChoices();
int getNumber();
int getCase();
void printIsEmpty(Node* head);
void add(Node* head);
void remove(Node* head, Node* auxiliary);
void search(Node* head);
void show(Node* head);
void menu(Node* head, Node* auxiliary);

#endif // !MENU_H