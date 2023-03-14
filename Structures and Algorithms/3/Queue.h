#ifndef QUEUE_H
#define	QUEUE_H

struct Node
{
	char data{};
	Node* next{};
};

struct Queue
{
	Node* front{ nullptr };
	Node* rear{ nullptr };
};

bool isEmpty(Queue& queue);
void enQueue(Queue& queue, int newData);
void deQueue(Queue& queue);
void show(Queue& queue);

#endif
