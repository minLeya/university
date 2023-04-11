#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct Node //node of binaty tree
{
	int data{};
	Node* left{};
	Node* right{};
};

//���� ��� �������� ������������������ ���������� ������ �� ����� �� ������� ������� � ������ ���� ������ � ������ 
struct Stack
{
	int level{ -1 };				 //"�������" �������
	Node* nodePointer{ nullptr };	 //��������� �� ���������� ������� ������
	Stack* next{ nullptr };			 //��������� �� ��������� ������� �����
};

void addNodes(Node*& root, int numberOfElements);
void printTreeInSymmetricOrder(Node* root, int level);
void printTreeInSymmetricOrderNonRecursive(Node* root);
void destroyTree(Node* root);
#endif // !BINARY_TREE_H
