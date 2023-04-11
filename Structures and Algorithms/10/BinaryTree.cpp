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
	Stack* top{ new Stack{} }; //����. ������� �����
	top->nodePointer = root; 
	top->level = -1;
	top->next = nullptr;

	Node* current{ root };// ������� ������� - ������
	int currentLevel{ 0 };
	while (current != nullptr || top->level >= 0) //���� �� ���������� ������ ������� � ���� ���� �� ����
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
		//���������� �� ����� ����� ������� �������������� ������� � �� �������
		currentLevel = top->level;
		current = top->nodePointer;

		//�������� �� �����
		Stack* temporary{ top };
		top = top->next;
		delete temporary;

		//����� � ���������
		std::cout << std::string(currentLevel * 4, ' ') << current->data << '\n';

		//������� � ������� ������� ������� �������
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