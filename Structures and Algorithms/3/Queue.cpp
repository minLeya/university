#include "Queue.h"
#include <iostream>

bool isEmpty(Queue& queue)
{
	if (queue.front == nullptr && queue.rear == nullptr)
	{
		return true;
	}
	else return false;
}

void enQueue(Queue& queue, int newData) //add to the end
{
	Node* newNode{ new Node{} };
	newNode->data = newData;
	newNode->next = nullptr;
	if (isEmpty(queue))
	{
		queue.front = newNode;
		queue.rear = newNode;
		queue.rear->next = queue.front; //circular queue - next should be pointed to the front
	}
	else
	{
		queue.rear->next = newNode;
		queue.rear = newNode;
		newNode->next = queue.front; //it's a circular queue so we need next to be pointed to the front
	}
}

void deQueue(Queue& queue)
{
	if (isEmpty(queue))
	{
		std::cerr << "\nQueue is empty! There is no element to delete!\n";
	}
	else
	{
		Node* nodeToDelete{ queue.front };
		char dataToDelete{ nodeToDelete->data };
		if (queue.front == queue.rear)
		{
			queue.front = nullptr;
			queue.rear = nullptr;
			delete nodeToDelete;
		}
		else
		{
			queue.front = queue.front->next;
			queue.rear->next = queue.front;
			delete nodeToDelete;
		}
	}
}

void show(Queue& queue)
{
	if (isEmpty(queue))
	{
		std::cerr << "\nThe queue is empty\n";
		return;
	}
	Node* current{ queue.front };
	
	do
	{
		std::cout << current->data << ' ';
		current = current->next;
	} while (current != queue.front);
}
