#ifndef MENU_H
#define MENU_H
#include "LinkedList.h"

void menuForChoices();
int getNumber();
int getCase();
void addToMainList(NodeOfList* listHead);
void addToSublist(NodeOfList* listHead);
void removeFromList(NodeOfList* listHead);
void removeFromSublist(NodeOfList* listHead);
void search(NodeOfList* listHead);
void showList(NodeOfList* listHead);
void menu(NodeOfList* listHead);
void run();


#endif // !MENU_H