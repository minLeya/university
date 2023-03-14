#include <iostream>
#include <random> 
#include <windows.h> 
#include <string>
#include "Queue.h"
//ascii from 65 to 90
//enter q to exit from modeling queue

namespace rng
{
	std::mt19937 mt{ std::random_device{}() };
	int getNumber(int min, int max)
	{
		std::uniform_int_distribution value(min, max);
		return value(mt);
	}
	char getChar()
	{
		std::uniform_int_distribution value(65, 90);
		return value(mt);
	}
}

void enqueueModeling(Queue& queue)
{
	int numberOfElementsToEnqueue{ rng::getNumber(1, 3) };
	std::cout << "\nAdding " << numberOfElementsToEnqueue << " elements\n";
	for (int i{ 0 }; i < numberOfElementsToEnqueue; i++)
	{
		char newData{ rng::getChar() };
		enQueue(queue, newData);
	}
}

void dequeueModeling(Queue& queue)
{
	int numberOfElementsToDequeue{ rng::getNumber(1, 3) };
	std::cout << "\nDeleting " << numberOfElementsToDequeue << " elements\n";
	for (int i{ 0 }; i < numberOfElementsToDequeue; i++)
	{
		if (isEmpty(queue)) break;
		else deQueue(queue);
	}
}

void showModeling(Queue& queue)
{
	std::cout << '\n';
	show(queue);
	std::cout << '\n';
}

void addOrDelete(Queue& queue)
{
	int number{ rng::getNumber(1, 100) };
	if (isEmpty(queue))
	{
		enqueueModeling(queue);
		showModeling(queue);
	}
	else if (number % 2 == 0)
	{
		enqueueModeling(queue);
		showModeling(queue);
	}
	else if (number != 0)
	{
		dequeueModeling(queue);
		showModeling(queue);
	}
}

void modelingQueue(Queue& queue)
{
	bool cycle{ true };
	while (cycle)
	{
		/*char exit{};
		std::cin >> exit;
		if (exit == 'q')
			cycle = false;*/
		//else
		//{
		addOrDelete(queue);
		Sleep(1000);
		std::cout << "Press q to exit.\n";
		//}
	}
}

void MenuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the circular queue is empty.\n" <<
		"2) Add an element to the end.\n" <<
		"3) Remove the first element.\n" <<
		"4) Show.\n" <<
		"5) Queue modeling.\n" <<
		"6) Exit.\n";
}

char getCase()
{
	while (true)
	{
		MenuForChoices(); //here the text
		std::cout << "Your choice is: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6")
		{
			return choice[0];
		}
		else
		{
			std::cout << "\nInput error! Repeat, please: \n";
		}
	}
}

void checkIfEmpty(Queue& queue)
{
	if (isEmpty(queue))
	{
		std::cout << "\nThe circular queue is empty!\n\n";
	}
	else
	{
		std::cout << "\nThe circular queue is NOT empty!\n\n";
	}
}

void menu(Queue& queue)
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase()) //here menu
		{
		case '1':
			checkIfEmpty(queue);
			break;
		case '2':
			enQueue(queue, rng::getChar());
			std::cout << '\n';
			break;
		case '3':
			deQueue(queue);
			std::cout << '\n';
			break;
		case '4':
			std::cout << "\nYour circular queue looks like that:\n";
			show(queue);
			std::cout << "\n\n";
			break;
		case '5':
			modelingQueue(queue);
			break;
		case '6':
			cycle = false;
		}
	}
}

int main()
{
	Queue queue{};
	menu(queue);
	return 0;
}
