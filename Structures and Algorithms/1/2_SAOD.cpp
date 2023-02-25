#include <iostream>
#include <string>
#include <random>
//ring queue 
inline constexpr int size{ 4 };

struct Queue
{
	int front{};//begin
	int rear{};//end
	int array[size];
	int itemCount{0};

	void EmptyCircularQueueInitialization();
	bool isFull(); 
	bool isEmpty();

	void enQueue(int item); //add
	void deQueue(); //delete
	void show();

} queue{};

void Queue::EmptyCircularQueueInitialization()
{
	front = 0;
	rear = 0;
}

bool Queue::isFull()
{
	if (itemCount >= size)
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
	/*if (front == 0 && rear == 0)
	{
		return true;
	}*/
	//if (front == (rear + 1) % size) //front=0, rear=3 or r=0, f=1
	//{
	//	return true;
	//}

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
	/*if (isEmpty())
	{
		array[rear] = item;
	}*/
	/*else if (rear < size - 1)
	{
		rear++;
		array[rear] = item;
	}*/
	if(isFull())
	{
		std::cout << "Circular queue is full! You cannot enqueue new item!\n\n";
	}
	else if (isEmpty())
	{
		array[rear] = item;
		itemCount++;
	}
	else if(!isFull() && !isEmpty())
	{
		//rear = (rear + 1) % size; //(0+1)%4=1; (3+1)%4=0 - reset to zero - it works when rear = -1 so for class
		rear = (rear + 1) % size;
		array[rear] = item;
		//if (rear == size)
		//{
		//	rear = 0;//reset to zero so we start from the "start"
		//}
		itemCount++;
	}
}

void Queue::deQueue() //delete
{
	if (isEmpty())
	{
		std::cout << "The circular queue is empty! You cannot dequeue!\n\n";
	}
	else
	{//????
		int item = array[front];
		array[front] = 0;
		front++;
		if (front == size)
		{
			front = 0;
		}
		itemCount--;
	}
}

void Queue::show()
{
	if (!isEmpty())
	{
		for (int i{ 0 }; i < size; i++)
		{
			std::cout << array[i] << "  ";
		}
	}
	else
	{
		std::cout << "There is no elements in queue to show!\n\n";
	}
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
		else if (static_cast<int>(num) != num)//??? проверка на целое число
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
	std::cout << "\nWhat do you want to do?\n" <<
		"1) Check if the circular queue is empty.\n" <<
		"2) Check if the circular queue is full.\n" <<
		"3) Add the element to the end.\n" <<
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

void menu()
{
	bool cycle{ true };
	while (cycle) {
		switch (getCase()) //here menu
		{
		case '1':
			std::cout << '\n';
			if (queue.isEmpty())
			{
				std::cout << "\nThe circular queue is empty!\n\n";
			}
			else
			{
				std::cout << "\nThe circular queue is NOT empty!\n\n";
			}
			break;
		case '2':
			if (queue.isFull())
			{
				std::cout << "\nThe circular queue is full!\n\n";
			}
			else
			{
				std::cout << "\nThe circular queue is NOT full!\n\n";
			}
			break;
		case '3':
			queue.enQueue(getRandom());
			break;
		case '4':
			queue.deQueue();
			break;
		case '5':
			std::cout << "Your circular queue looks like that:\n";
			queue.show();
			break;
		case '6':
			std::cout << '\n' << queue.front << " " << queue.rear << '\n';
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
	//queue.enQueue(5);
	//std::cout << queue.rear << " " << queue.front << '\n';

	//queue.enQueue(7);
	//std::cout << queue.rear << " " << queue.front << '\n';

	//queue.enQueue(4);
	//std::cout << queue.rear << " " << queue.front << '\n';

	//////queue.show();
	//queue.enQueue(9);
	//std::cout << queue.rear << " " << queue.front << '\n';

	//queue.deQueue();
	//std::cout << queue.rear << " " << queue.front << '\n';

	//queue.deQueue();
	//std::cout << queue.rear << " " << queue.front << '\n';

	//////queue.deQueue();
	//////queue.deQueue();
	//////queue.deQueue();
	//////std::cout << queue.rear<<" "<<queue.front << '\n';
	//queue.enQueue(8);
	//std::cout << queue.rear << " " << queue.front << '\n';

	//queue.enQueue(6);
	//std::cout << queue.rear << " " << queue.front << '\n';


	//queue.show();
	//std::cout << '\n';
	//std::cout << queue.isEmpty();
	//std::cout << queue.isFull();

	return 0;
}

