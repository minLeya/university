#ifndef MEHU_H
#define MENU_H
#include "LinkedList.h"

void menuForChoices();
int getNumber();
int getCase();
void printIsEmpty(LinkedList& list);
void printIsFull(LinkedList& list);
void add(LinkedList& list);
void remove(LinkedList& list);
void search(LinkedList& list);
void show(LinkedList& list);
void menu(LinkedList& list);

#endif