#include "BinaryTree.h"

#include <iostream>
#include <random>

namespace rnd
{
	std::mt19937 mt{ std::random_device{}() };

	int getNumber(int min, int max)
	{
		std::uniform_int_distribution range{ min, max };
		return range(mt);
	}
}

void addNodes(Node*& root, int numberOfElements)
{
	if (numberOfElements == 0)
		return;

	int numberOfLeftChildren{ numberOfElements / 2 };
	int numberOfRightChildren{ numberOfElements - numberOfLeftChildren - 1 };

	Node* newNode{ new Node{} };
	newNode->data = rnd::getNumber(0, 99);
	addNodes(newNode->left, numberOfLeftChildren);
	addNodes(newNode->right, numberOfRightChildren);
	root = newNode;
}


void printTreeInSymmetricOrder(Node* root, int level)
{
	if (root == nullptr)
		return;

	printTreeInSymmetricOrder(root->left, level + 4);
	std::cout << std::string(level, ' ') << root->data << '\n';
	printTreeInSymmetricOrder(root->right, level + 4);
}

void printTreeInSymmetricOrderNonRecursive(Node* root)
{
	Stack* top{ new Stack{} }; //иниц. пустого стека
	top->nodePointer = root; 
	top->level = -1;
	top->next = nullptr;

	Node* current{ root };// текущая вершина - корень
	int currentLevel{ 0 };
	while (current != nullptr || top->level >= 0) //пока не достигнута пустая вершина и пока стек не пуст
	{
		while (current != nullptr)
		{
			Stack* newNode{ new Stack{} };
			newNode->level = currentLevel;
			newNode->nodePointer = current;
			newNode->next = top;
			top = newNode;
			current = current->left;
			++currentLevel;
		}
		//извлечение из стека адрес текущей обрабатываемой вершины и ее уровень
		currentLevel = top->level;
		current = top->nodePointer;

		//удаление из стека
		Stack* temporary{ top };
		top = top->next;
		delete temporary;

		//вывод с пробелами
		std::cout << std::string(currentLevel * 4, ' ') << current->data << '\n';

		//переход к правому потомку текущей вершины
		current = current->right;
		++currentLevel;
	}
}

void destroyTree(Node* root)
{
	if (root == nullptr)
		return;

	destroyTree(root->left);
	destroyTree(root->right);
	delete root;
}