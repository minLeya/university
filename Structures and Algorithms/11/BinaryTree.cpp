#include "BinaryTree.h"

#include <iostream>
#include <random>

bool isTreeEmpty(const Node* root)
{
	return (root == nullptr);
}

void addNode(Node*& node, int newData)
{
	Node* newNode{ new Node{} };
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->data = newData;

	if (node->left == nullptr && node->right != nullptr)
	{
		node->left = newNode;
		std::cout << "\nadded value " << newData << " as the left child of node\n";
	}
	else if (node->left != nullptr && node->right == nullptr)
	{
		node->right = newNode;
		std::cout << "\nadded value " << newData << " as the right child of node\n";
	}
	else
	{
		std::cout << "\n1: add as the right child\n2: add as the left child\n";
		int option{};
		std::cin >> option;

		if (option == 1)
			node->right = newNode;
		else if (option == 2)
			node->left = newNode;
		else
		{
			std::cout << "\nincorrect option\n";
			delete newNode;
		}
	}
}

void findElementInTree(Node* root, Node*& foundParent, int valueToFind, bool continueSearching)
{
	if (!continueSearching || root == nullptr)
		return;

	if (root->data != valueToFind)
	{
		findElementInTree(root->left, foundParent, valueToFind, continueSearching);
		findElementInTree(root->right, foundParent, valueToFind, continueSearching);
	}
	else if (root->data == valueToFind)
	{
		continueSearching = false;
		foundParent = root;
	}
}

void printTreeInDirectOrder(const Node* root, int level)
{
	if (root == nullptr)
		return;

	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInDirectOrder(root->left, level + 4);
	printTreeInDirectOrder(root->right, level + 4);
}

void printTreeInSymmetricOrder(const Node* root, int level)
{
	if (root == nullptr)
		return;

	printTreeInSymmetricOrder(root->left, level + 4);
	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInSymmetricOrder(root->right, level + 4);
}

void printTreeInBackwardSymmetricOrder(const Node* root, int level)
{
	if (root == nullptr)
		return;

	printTreeInBackwardSymmetricOrder(root->right, level + 4);
	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInBackwardSymmetricOrder(root->left, level + 4);
}

void destroyTree(Node* root)
{
	if (root == nullptr)
		return;

	destroyTree(root->left);
	destroyTree(root->right);
	delete root;
}