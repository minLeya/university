#include "Firm.h"
#include "Menu.h"

#include <iostream>
#include <random>
#include <string>

void menuText()
{
	std::cout << "what do you want to do?\n" <<
		"1. add a provider\n"
		"2. find a provider\n" <<
		"3. print providers\n" <<
		"4. remove a provider\n" <<
		"5. add a product to provider\n" <<
		"6. find a product in provider \n" <<
		"7. print product?\n" <<
		"8. remove a product from provider\n";
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

void menuAddProvider(Firm& firm)
{
	/*std::cout << "\nenter provider's name: ";
	std::string name{ getString() };*/
	firm.addProvider();
	std::cout << '\n';
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
		std::cout << "\provider " << name << " is found\n";
	else
		std::cout << "\provider " << name << " is not found\n";
}

void menuPrintProviders(Firm& firm)
{
	std::cout << '\n';
	firm.printProviders();
	std::cout << '\n';
}

void menuRemoveProvider(Firm& firm)
{
	firm.removeProvider();
	std::cout << '\n';
}

void menuAddProduct(Firm& firm)
{
	if (firm.isProviderEmpty())
	{
		std::cout << "\the provider stack in empty\n";
		return;
	}
	std::cout << "\nenter the name of provider to whick you'd like to add new product: ";
	std::string providerName{ getString() };
	int index{ firm.findProvider(providerName) };
	if (index == -1)
	{
		std::cout << "\nthere's no provider with the name " << providerName << '\n';
		return;
	}
	Provider currentProvider{ firm.getProvider(index) };
	std::cout << "\nenter the name of the new product: ";
	std::string productName{ getString() };
	std::cout << "\nenter the quantity of the new product: ";
	int productQuantity{ getNumber() };
	//currentProvider.addProduct()

}

void menu(Firm& firm, int command)
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
		break;
	case 7:
		break;
	}
}

void run()
{
	Firm firm{};
	int command{};
	while (command != -1)
	{
		menuText();
		command = getNumber();
		menu(firm, command);
	}
}