#include "Provider.h"
#include <iostream>

Provider::Provider()  : m_name{ "Default Provider" },
						m_productHead{ nullptr }
{

}

Provider::Provider(std::string& name) : m_name{ name },
						m_productHead{ nullptr }
{

}

void Provider::setName(std::string& name)
{
	m_name = name;
}

void Provider::setProductHead(Product* producthead)
{
	m_productHead = producthead;
}

void Provider::setNext(Provider* next)
{
	m_next = next;
}

std::string Provider::getName()
{
	return m_name;
}

Product* Provider:: getProductHead()
{
	return m_productHead;
}

Provider* Provider::getProviderNext()
{
	return m_next;
}

int Provider::getValue()
{
	int value{};
	std::cin >> value;
	return value;
}

std::string Provider::getString()
{
	std::string string{};
	std::cin >> string;
	return string;
}

bool Provider::isProviderEmpty()
{
	return(m_productHead->getNext() == m_productHead); //закольцованный с заголовком
}

void Provider::addProduct(std::string& newName, int newQuantity)
{
	Product* productHead{};
	if (isProviderEmpty())
	{
		std::cout << "\nEnter new product's name: ";
		std::string newName{ getString() };
		std::cout << "\nEnter new product's quantity: ";
		int newQuantity{ getValue() };
		
		Product* newProduct{ new Product{} };
		newProduct->setQuantity(newQuantity);
		newProduct->setName(newName);

		productHead->setNext(newProduct);
		productHead->setPrev(newProduct);
		
		newProduct->setNext(productHead);
		newProduct->setPrev(productHead);
	}
	else
	{
		std::cout << "\nEnter 1 to add before specific product, enter 2 to add after: ";
		int choice{ getValue() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the name of product before which you'd like to add new element: ";
			std::string currentItem{ getString() };

			Product* current{ productHead->getNext()};
			while (current != productHead && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			if (current == productHead)
			{
				std::cerr << "\There's no such product in the list!\n";
				return;
			}

			std::cout << "\nEnter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nEnter new product's quantity: ";
			int newQuantity{ getValue() };

			Product* newProduct{ new Product{} };

			newProduct->setName(newName);
			newProduct->setQuantity(newQuantity);
			
			newProduct->setNext(current);
			Product* temp{ current->getPrev() };
			newProduct->setPrev(temp);
			newProduct->getPrev()->setNext(newProduct);
			newProduct->setPrev(newProduct);

		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the name of product after which you'd like to add new element: ";
			std::string currentItem{ getString() };

			Product* current{ productHead->getNext()};
			while (current != productHead && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			if (current == productHead)
			{
				std::cerr << "\There's no such product in the list!\n";
				return;
			}

			std::cout << "\nEnter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nEnter new product's quantity: ";
			int newQuantity{ getValue() };

			Product* newProduct{ new Product{} };

			newProduct->setName(newName);
			newProduct->setQuantity(newQuantity);

			Product* temp{ current->getNext() };
			newProduct->setNext(temp);
			newProduct->setPrev(current);
			current->getNext()->setPrev(newProduct);
			current->setNext(newProduct);
		}
		else
		{
			std::cerr << "\nInput error, please repeat!\n";
		}
	}
}

bool Provider::findProduct(std::string& productName) //check if the list is empty?
{
	Product* current{ m_productHead };
	while (current != m_productHead && current->getName() != productName)
	{
		current = current->getNext();
	}
	
	if (current == m_productHead)
		return false;

	std::cout << "\nproduct " << productName << " was found\n"; //should i add in which provider??
	return true;
}

//it looks more correct to me
//void Provider::removeProduct()
//{
//	std::cout << "\nEnter the name of the product you'd like to delete: ";
//	std::string productName{ getString()};
//	
//	if (!findProduct(productName))
//	{
//		std::cout << "\ncouldn't find this product\n";
//		return;
//	}
//
//}

void Provider::removeProduct(std::string& productName)
{
	if (isProviderEmpty())//should it be there?
		//'cause it'll be like: enter the name of product to delete,
		// but then oh wait the list is empty, you cannot delete
	{
		std::cout << "\nthee provider list is empty\n";
		return;
	}
	if (!findProduct(productName))
	{
		std::cout << "\ncouldn't find this product\n";
		return;
	}
	Product* current{ m_productHead->getNext() };
	while (current != m_productHead && current->getName() != productName)
		current = current->getNext();

	Product* currNext{ current->getNext() };
	current->getPrev()->setNext(currNext);
	Product* currPrev{ current->getPrev() };
	current->getNext()->setPrev(currPrev);
	delete current;
}

void Provider::printProducts()
{
	if (isProviderEmpty())
	{
		std::cout << "\nthere's no products\n";
		return;
	}
	Product* current{ m_productHead };
	while (current != m_productHead)
	{
		std::cout << "product: " << current->getName() << " (" << current->getQuantity() << ")\n";
		current = current->getNext();
	}
}

//Provider::~Provider()
//{
//	//??
//}