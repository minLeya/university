#include "Menu.h"
#include "BinaryTree.h"
#include <iostream>

void menuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1. add element to tree.\n"
		"2. search for element in tree\n" <<
		"3. print tree.\n" <<
		"4. destroy tree\n" <<
		"5. exit.\n";
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

int getCase()
{
	while (true)
	{
		menuForChoices();
		std::cout << "your choice is: ";
		int choice = getNumber();
		if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)
		{
			return choice;
		}
		else
		{
			std::cout << "\ninput error, please repeat:\n";
		}
	}
}

void add(Node*& root)
{
	if (isTreeEmpty(root))
	{
		std::cout << "\nenter new value: ";
		int newValue{ getNumber() };
		Node* newNode{ new Node{} };
		newNode->data = newValue;
		newNode->left = nullptr;
		newNode->right = nullptr;
		root = newNode;
	}
	else
	{
		std::cout << "\nenter node value to which you want to add children\n";
		int nodeValue{ getNumber() };
		Node* foundNode{};
		findElementInTree(root, foundNode, nodeValue);
		if (!foundNode)
		{
			std::cout << "\nnode with value " << nodeValue << " wasn't found in the tree\n";
			return;
		}

		if (foundNode->left != nullptr && foundNode->right != nullptr)
		{
			std::cout << "\nfound node already has 2 children\n";
			return;
		}

		std::cout << "\nenter new value: ";
		int newValue{ getNumber() };
		addNode(foundNode, newValue);
	}
}

void search(Node* root)
{
	std::cout << "\nenter value to find: ";
	int valueToFind{ getNumber() };
	Node* found{};
	findElementInTree(root, found, valueToFind);
	if (found)
		std::cout << "\nvalue " << valueToFind << " was found in the tree\n";
	else
		std::cout << "\nvalue " << valueToFind << " wasn't found in the tree\n";
}

void print(const Node* root)
{
	if (isTreeEmpty(root))
	{
		std::cout << "\nthe tree is empty\n";
		return;
	}

	/*std::cout << "\ndirect order:\n";
	printTreeInDirectOrder(root);
	std::cout << "\nsymmetric order:\n";
	printTreeInSymmetricOrder(root);*/
	std::cout << "\nbackward symmetric order:\n";
	printTreeInBackwardSymmetricOrder(root);
}

void destroy(Node*& root)
{
	destroyTree(root);
	root = nullptr;
}

void menu(Node* root)
{
	bool cycle{ true };
	while (cycle)
	{
		switch (getCase())
		{
		case 1:
			add(root);
			break;
		case 2:
			search(root);
			break;
		case 3:
			print(root);
			break;
		case 4:
			destroy(root);
			break;
		case 5:
			cycle = false;
		}
	}
}

void run()
{
	Node* root{ nullptr };
	menu(root);
}