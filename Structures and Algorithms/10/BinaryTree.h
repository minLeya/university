#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct Node //node of binaty tree
{
	int data{};
	Node* left{};
	Node* right{};
};

//стек для хранения последовательности пройденных вершин от корня до текущей вершины и уровня этих вершин в дереве 
struct Stack
{
	int level{ -1 };				 //"уровень" вершины
	Node* nodePointer{ nullptr };	 //указатели на пройденную вершину дерева
	Stack* next{ nullptr };			 //указатели на следующий элемент стека
};

void addNodes(Node*& root, int numberOfElements);
void printTreeInSymmetricOrder(Node* root, int level);
void printTreeInSymmetricOrderNonRecursive(Node* root);
void destroyTree(Node* root);
#endif // !BINARY_TREE_H
