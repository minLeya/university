#include "Firm.h"
#include "Menu.h"
#include "FileIO.h"

#include <iostream>
#include <string>

void menuText()
{
	std::cout << "\nwhat do you want to do?\n" <<
		"1. add a provider\n" <<
		"2. find a provider\n" <<
		"3. print structure\n" <<
		"4. remove a provider\n" <<
		"5. add a product to provider\n" <<
		"6. find a product in provider \n" <<
		"7. remove a product from provider\n" <<
		"8. give a name to firm\n" <<
		"9. load data from file\n" <<
		"0. load data to file\n" <<
		"-1. exit\n";
}

int getNumber()
{
	int number{};
	std::cin >> number;
	return number;
}

std::string getString()
{
	std::string string{};
	std::cin >> string;
	return string;
}

void menuNameFirm(Firm& firm)
{
	std::cout << "enter the name of the firm: ";
	std::string name{ getString() };
	firm.setName(name);
}

void menuAddProvider(Firm& firm)
{
	if (firm.isProviderFull())
	{
		std::cout << "stack is full\n";
	}
	else
	{
		std::cout << "enter the name of provider: ";
		std::string newName{ getString() };
		firm.addProvider(newName);
	}
}

void menuFindProvider(Firm& firm)
{
	if (firm.isProviderEmpty())
	{
		std::cout << "the provider stack is empty\n";
		return;
	}
	std::cout << "\nenter provider's name: ";
	std::string name{ getString() };
	int index{ firm.findProvider(name) };
	if (index != -1)
		std::cout << "provider " << name << " is found\n";
	else
		std::cout << "provider " << name << " is not found\n";
}

void menuPrintProviders(Firm& firm)
{
	std::cout << '\n';
	std::cout << "\tFirm " << firm.getName() << "\n";
	firm.printProviders();
}

void menuRemoveProvider(Firm& firm)
{
	firm.removeProvider();
}

void menuAddProduct(Firm& firm)
{
	if (firm.isProviderEmpty())
	{
		std::cout << "\nthe provider stack in empty\n";
		return;
	}
	std::cout << "\nenter the name of provider to which you'd like to add new product: ";
	std::string providerName{ getString() };
	int index{ firm.findProvider(providerName) };
	if (index == -1)
	{
		std::cout << "\nthere's no provider with the name " << providerName << '\n';
		return;
	}
	Provider& currentProvider{ firm.getProvider(index) };
	currentProvider.addProduct();
}

void menuFindProduct(Firm& firm)
{
	if (firm.isProviderEmpty())
	{
		std::cout << "\nthe list is empty, you cannot search\n";
		return;
	}
	std::cout << "enter the name of product you'd like to search for: ";
	std::string name{ getString() };
	int productCount{};
	for (int i{ 0 }; i < constants::size; ++i)
	{
		Provider& current{ firm.getProvider(i) };

		if (current.findProduct(name))
		{
			std::cout << "product " << name << " is found in provider " << current.getName() << '\n';
			++productCount;
		}
	}
	if (productCount == 0)
		std::cout << "product " << name << " is not found\n";
	else
		std::cout << "total number of product " << name << ": " << productCount << '\n';
}

void menuRemoveProduct(Firm& firm)
{
	if (firm.isProviderEmpty())
	{
		std::cout << "provider stack is empty\n";
		return;
	}
	std::cout << "enter the name of provider in which you'd like to remove product: ";
	std::string providerName{ getString() };

	int index{ firm.findProvider(providerName) };
	if (index == -1)
	{
		std::cout << "couldn't find provider " << providerName << '\n';
		return;
	}
	Provider& current{ firm.getProvider(index) };
	if (current.getProductHead() == nullptr)
	{
		std::cout << "provider " << providerName << " is empty\n";
		return;
	}
	std::cout << "enter the name of product you'd like to delete: ";
	std::string productName{ getString() };
	current.removeProduct(providerName, productName);
}

void menuRenameFirm(Firm& firm)
{
	std::cout << "\enter new name of firm: ";
	std::string newName{ getString() };
	firm.setName(newName);
}

void menuLoadFromFile(Firm& firm, FileIO& fileIO)
{
	if (!fileIO.writeFirmFromFile(firm))
	{
		std::cout << "\ncould not read firm structure from file\n";
		return;
	}
}

void menuLoadToFile(Firm& firm, FileIO& fileIO)
{
	fileIO.writeFirmToFile(firm);
}

void menu(Firm& firm, FileIO& fileIO, int command)
{
	switch (command)
	{
	case 1:
		menuAddProvider(firm); 
		break;
	case 2:
		menuFindProvider(firm); 
		break;
	case 3:
		menuPrintProviders(firm); 
		break;
	case 4:
		menuRemoveProvider(firm); 
		break;
	case 5:
		menuAddProduct(firm); 
		break;
	case 6:
		menuFindProduct(firm); 
		break;
	case 7:
		menuRemoveProduct(firm); 
		break;
	case 8:
		menuRenameFirm(firm); 
		break;
	case 9:
		menuLoadFromFile(firm, fileIO);
		break;
	case 0:
		menuLoadToFile(firm, fileIO);
		break;
	}
}

void run()
{
	Firm firm{};
	FileIO fileIO{};

	int command{};
	while (command != -1)
	{
		menuText();
		command = getNumber();
		menu(firm, fileIO, command);
	}
}