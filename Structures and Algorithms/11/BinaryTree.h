#ifndef BINARY_TREE_H
#define BINARY_TREE_H

struct Node
{
	int data{};
	Node* left{};
	Node* right{};
};

bool isTreeEmpty(const Node* root);
void addNode(Node*& root, int newValue);
void findElementInTree(Node* root, Node*& foundParent, int valueToFind, bool continueSearching = true);
void printTreeInDirectOrder(const Node* root, int level = 0);
void printTreeInSymmetricOrder(const Node* root, int level = 0);
void printTreeInBackwardSymmetricOrder(const Node* root, int level = 0);
void destroyTree(Node* root);

#endif // !BINARY_TREE_H
