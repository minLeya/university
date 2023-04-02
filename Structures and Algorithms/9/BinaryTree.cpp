#include "BinaryTree.h"
#include <random>
#include <iostream>

namespace rng
{
	int getRandomNumber(int min, int max)
	{
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ min, max };
		return range(mt);
	}
}

void addNodes(Node*& root, int numberOfElements)
{
	if (numberOfElements == 0)
		return;

	int leftChildren{ numberOfElements / 2 };
	int rightChildren{ numberOfElements - leftChildren - 1 };

	Node* newNode{ new Node{} };
	newNode->data = rng::getRandomNumber(0, 99);
	addNodes(newNode->left, leftChildren);
	addNodes(newNode->right, rightChildren);
	root = newNode;
}

void printTreeInDirectOrder(Node* root, int level)
{
	if (root == nullptr)
		return;

	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInDirectOrder(root->left, level + 4);
	printTreeInDirectOrder(root->right, level + 4);
}

void printTreeInSymmetricOrder(Node* root, int level)
{
	if (root == nullptr)
		return;
	
	printTreeInSymmetricOrder(root->left, level + 4);
	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInSymmetricOrder(root->right, level + 4);
}

void printTreeInBackwardSymmetricOrder(Node* root, int level)
{
	if (root == nullptr)
		return;

	printTreeInBackwardSymmetricOrder(root->right, level + 4);
	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInBackwardSymmetricOrder(root->left, level + 4);
}

void deleteTree(Node* root)
{
	if (root == nullptr)
		return;
		
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}