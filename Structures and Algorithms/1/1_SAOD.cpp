#include <iostream>
#include <random>
#include <string>

int getRandom()
{
	std::mt19937 mt{ std::random_device{}() };

	std::uniform_int_distribution value(1, 10000);
	return value(mt);
}

struct Stack
{//it has the value that becomes the top of the stack
	//that's why i called it "top"
	int top{}; //the value in the one (this) node/struct/(rectangle of the memory(visialize a table from _that_presentation))
	Stack* next{}; //pointer to the next struct stack
} *m_stackPointer, *m_auxiliaryStackPointer; //pointer to the head of the stack - to the last element - to the top of the stack

void emptyStackInitialization()
{
	m_stackPointer = nullptr;
	m_auxiliaryStackPointer = nullptr;
}

bool isEmpty()
{
	if (m_stackPointer == nullptr)
	{
		return true;//1
	}
	else
		return false;//0
}

bool isAuxiliaryEmpty()
{
	if (m_auxiliaryStackPointer == nullptr)
	{
		return true;//1
	}
	else
		return false;//0
}

Stack* push(Stack* stackPointer, int newTop)
{
	Stack* current = new Stack; //dynamically allocate new node/element
	current->top = newTop; //initialization of a new value
	current->next = stackPointer; //point to the previous node/element (we need to archieve the element before the last)
	stackPointer = current; //making the new element the last element of the stack
	return current;
}

int pop()
{
	if (isEmpty()) //if empty, then true; if not empty, then false;
	{
		return -1; //how can we delete nothing?
		
	}
	else
	{
		//we need to delete current
		Stack* current = m_stackPointer; //making from the last node/element/head/or tail? of the stack the "current"
		//bc we cannot delete m_stackPointer
		m_stackPointer = m_stackPointer->next; //so we need m_stackPointer to be the element before the last
		//we can acsess it using next, bc the last node/tail points to the previous node
		delete current;  //aand finally we delete current! good job
		return 1;
	}
}

void show(Stack* stackPointer) 
{
	if (stackPointer != nullptr)
	{
		std::cout << "\n";
		Stack* current;
		current = stackPointer;
		for (int i{ 1 }; current != nullptr; i++)
		{
			std::cout << i << ". " << current->top << '\n';
			current = current->next;
		}
	}
	else
	{
		std::cout << "Stack is empty.\n";
	}
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

void pushManyRandomValues()
{
	std::cout << "Enter the number of values to be entered into the stack: ";
	int number{ getNumber() };
	for (int i{ 0 }; i < number; i++)
	{
		m_stackPointer = push(m_stackPointer, getRandom());
	}
}

void moveToAuxiliaryStack() {
	Stack* current = m_stackPointer;
	m_stackPointer = m_stackPointer->next;
	current->next = m_auxiliaryStackPointer;
	m_auxiliaryStackPointer = current;
}

void getElementsFromAuxiliaryStack()
{
	Stack* current = m_auxiliaryStackPointer;
	m_auxiliaryStackPointer = m_auxiliaryStackPointer->next;
	current->next = m_stackPointer;
	m_stackPointer = current;
}

void MenuForChoices()
{
	std::cout << "\nWhat do you want to do?" << '\n' <<
		"1) Check if the main stack is empty." << '\n' <<
		"2) Check if the auxiliary stack is empty." << '\n' <<
		"3) Add the element to the top of the main stack." << '\n' <<
		"4) Add several random elements to the top of the main stack." << '\n' <<
		"5) Delete the element from the top of the main stack." << '\n' <<
		"6) Show the main stack." << '\n' <<
		"7) Show the auxiliary stack." << '\n' <<
		"8) Exit." << '\n';
}

char getCase()
{
	while (true)
	{
		MenuForChoices(); //here the text
		std::cout << "Your choice is: ";
		std::string choice{};
		std::getline(std::cin, choice);
		if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8")
		{
			return choice[0];
		}
		else
		{
			std::cout << '\n' << "Input error! Repeat, please: " << '\n';
		}
	}
}

//char getOneOrTwo()
//{
//	while (true)
//	{
//		std::cout << "Your choice is: ";
//		std::string choice{};
//		std::getline(std::cin, choice);
//		if (choice == "1" || choice == "2")
//		{
//			return choice[0];
//		}
//		else
//		{
//			std::cout << '\n' << "Input error! Repeat, please: " << '\n';
//		}
//	}
//}

int getOneOrTwo()
{
	while (true)
	{
		std::cout << "Your choice is: ";
		int choice{};
		std::cin >> choice;
		if (choice == 1 || choice == 2)
		{
			return choice;
		}
		else
		{
			std::cout << '\n' << "Input error! Repeat, please: " << '\n';
			return 0;
		}
	}
}

void addElementToMainStack()
{
	std::cout << "\nI have a question about the origin of the element:\n"
		<< "1. Really creating a new element.\n"
		<< "2. Selecting it from the top of the auxiliary stack.\n";

	int answer{ getOneOrTwo()};
	if (answer == 1)
	{
		std::cout << "Please, enter the number: ";
		int value{ getNumber() };
		m_stackPointer = push(m_stackPointer, value);
	}
	else if (answer == 2) //doesn't work
	{
		if (isAuxiliaryEmpty())
		{
			std::cout << "Oh, it seems like the auxiliary stack is empty :(\n";
		}
		else
		{
			getElementsFromAuxiliaryStack();
		}
	}
	else if (answer == 0)
	{
		std::cout << '\n';
	}
}

void deleteElementFromMainstack()
{
	int answ{ getOneOrTwo() };
	if (answ == 1)//this too
	{
		pop();
	}
	else if(answ == 2)//this too
	{
		moveToAuxiliaryStack();
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
			if (isEmpty())
			{
				std::cout << "The main stack is empty!\n\n";
			}
			else
			{
				std::cout << "The main stack is NOT empty!\n\n";
			}
			break;

		case '2':
			std::cout << '\n';
			if (isAuxiliaryEmpty())
			{
				std::cout << "The auxiliary stack is empty!\n\n";
			}
			else
			{
				std::cout << "The auxiliary stack is NOT empty!\n\n";
			}
			break;

		case '3':
			addElementToMainStack();
			break;

		case '4':
			pushManyRandomValues();
			break;

		case '5':
			if (isEmpty())
			{
				std::cout << "\nThe main stack is empty, you cannot delete elements!\n";
			}
			else
			{
				std::cout << "\nWhat to do with the top element?\n"
					<< "1. Really delete with memory release.\n"
					<< "2. Include it at the top of the auxiliary stack.\n";
				
				deleteElementFromMainstack();
			}
			break;

		case '6':
			std::cout << "\nThis is how the main stack looks like:\n";
			show(m_stackPointer);
			break;

		case '7':
			std::cout << "\nThis is how the auxiliary stack looks like:\n";
			show(m_auxiliaryStackPointer);
			break;

		case '8':
			cycle = false;
		}
	}
}

int main()
{
	emptyStackInitialization();
	menu();
	return 0;
}
