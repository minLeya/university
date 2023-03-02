#include <iostream>
#include <string>
#include <random>

namespace size
{
	inline constexpr int size{ 4 };
}

struct Queue
{
	int front{-1};//begin
	int rear{-1};//end
	int array[size::size];
	int itemCount{ 0 };

	void EmptyCircularQueueInitialization();
	bool isFull();
	bool isEmpty();

	void enQueue(int item); //add
	void deQueue(); //delete
	void show();

} queue{};

void Queue::EmptyCircularQueueInitialization()
{
	front = -1;
	rear = -1;
}

bool Queue::isFull()
{
	if (itemCount >= size::size)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Queue::isEmpty()
{
	if (itemCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Queue::enQueue(int item) //add to the end
{
	if (isFull())
	{
		std::cerr << "\nThe circular queue is full! You cannot add new item!\n";
	}
	else
	{
		if (front == -1) front = 0;
		rear = (rear + 1) % size::size;
		array[rear] = item;
		itemCount++;
	}
	
	std::cout << '\n';
}

void Queue::deQueue() //delete
{
	if (isEmpty())
	{
		std::cout << "\nThe circular queue is empty! You cannot delete!\n";
	}
	else if (front==rear)
	{
		front = rear = -1;
		itemCount--;
	}
	else if (front != rear)
	{
		array[front] = 0;
		front=(front+1)%size::size;
		itemCount--;
	}

	std::cout << '\n';
}

void Queue::show()
{
	int i;
	if (!isEmpty())
	{
		for (i = { front }; i!=rear; i=(i+1)%size::size)
		{
			std::cout << array[i] << "  ";
		}
		std::cout << array[i];
	}

	else
	{
		std::cout << "There is no elements in queue to show!";
	}

	std::cout << "\n\n";
}

int getRandom()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution value(1, 20);
	return value(mt);
}

int getNumber()
{
	while (true)
	{
		int num;
		std::cin >> num;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "Input error, you did not enter a number. Repeat the input: \n";
		}
		else if (static_cast<int>(num) != num)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "You entered a non-natural number. Repeat the input: \n ";
		}
		else if (num <= 0)
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "You entered a non-positive number or zero. Repeat the input: \n ";
		}
		else
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return num;
		}
	}
}

void MenuForChoices()
{
	std::cout << "What do you want to do?\n" <<
		"1) Check if the circular queue is empty.\n" <<
		"2) Check if the circular queue is full.\n" <<
		"3) Add an element to the end.\n" <<
		"4) Remove the first element.\n" <<
		"5) Show.\n" <<
		"6) Show front and rear elements\n" <<
		"7) Exit.\n";
}

char getCase()
{
	while (true)
	{
		MenuForChoices(); //here the text
		std::cout << "Your choice is: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7")
		{
			return choice[0];
		}
		else
		{
			std::cout << "\nInput error! Repeat, please: \n";
		}
	}
}

void checkIfEmpty()
{
	if (queue.isEmpty())
	{
		std::cout << "\nThe circular queue is empty!\n\n";
	}
	else
	{
		std::cout << "\nThe circular queue is NOT empty!\n\n";
	}
}

void checkIfFull()
{
	if (queue.isFull())
	{
		std::cout << "\nThe circular queue is full!\n\n";
	}
	else
	{
		std::cout << "\nThe circular queue is NOT full!\n\n";
	}
}

void menu()
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase()) //here menu
		{
		case '1':
			checkIfEmpty();
			break;
		case '2':
			checkIfFull();
			break;
		case '3':
			queue.enQueue(getRandom());
			break;
		case '4':
			queue.deQueue();
			break;
		case '5':
			std::cout << "\nYour circular queue looks like that:\n";
			queue.show();
			break;
		case '6':
			std::cout << '\n' << queue.front << " " << queue.rear << '\n'<<queue.itemCount<<'\n';
			break;
		case '7':
			cycle = false;
		}
	}
}

int main()
{
	queue.EmptyCircularQueueInitialization();
	menu();
	return 0;
}
