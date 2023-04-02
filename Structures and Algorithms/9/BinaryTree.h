#ifndef BINARY_TREE_H
#define BINATY_TREE_H

struct Node
{
	int data{};
	Node* left{};
	Node* right{};
};

void addNodes(Node*& root, int numberOfElements);
void printTreeInDirectOrder(Node* root, int level);
void printTreeInSymmetricOrder(Node* root, int level);
void printTreeInBackwardSymmetricOrder(Node* root, int level);
void deleteTree(Node* root);

#endif // !BINARY_TREE_H
