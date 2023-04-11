#include "Menu.h"
#include "BinaryTree.h"
#include <iostream>

void menu()
{
	bool cycle{ true };
	Node* root{};
	while (cycle)
	{
		std::cout << "enter the number of elements of the binary tree: ";
		int number{};
		std::cin >> number;

		addNodes(root, number);

		std::cout << "\nin direct order:\n";
		printTreeInDirectOrder(root, 0);

		std::cout << "\nin symmetric order:\n";
		printTreeInSymmetricOrder(root, 0);
		
		std::cout << "\nin backward symmetric order:\n";
		printTreeInBackwardSymmetricOrder(root, 0);

		int choice{};
		std::cout << "\nenter 1 to exit\n";
		std::cin >> choice;

		if (choice == 1)
		{
			deleteTree(root);
			root = nullptr;
			cycle = false;
		}
	}
}