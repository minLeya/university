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

std::string Provider::getName()
{
	return m_name;
}

Product* Provider:: getProductHead() const
{
	return m_productHead;
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
	return(m_productHead == nullptr);
}

void Provider::addProduct()
{
	if (isProviderEmpty())
	{
		std::cout << "\nEnter new product's name: ";
		std::string newName{ getString() };
		std::cout << "\nEnter new product's quantity: ";
		int newQuantity{ getValue() };
		
		Product* newProduct{ new Product{newName, newQuantity} };

		m_productHead = newProduct;
		
		newProduct->setNext(nullptr);
		newProduct->setPrev(nullptr);
	}
	else
	{
		std::cout << "\nEnter 1 to add before specific product, enter 2 to add after: ";
		int choice{ getValue() };

		if (choice == 1)//before
		{
			std::cout << "\nEnter the name of product before which you'd like to add new element: ";
			std::string currentItem{ getString() };

			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			if (current == nullptr)
			{
				std::cerr << "There's no such product in the list!\n";
				return;
			}

			std::cout << "\nEnter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nEnter new product's quantity: ";
			int newQuantity{ getValue() };

			Product* newProduct{ new Product{newName, newQuantity} };
			// todo: fix this
			//doen't work if i try to add new element before the first element
			//upd it works but i've to test it more
			newProduct->setNext(current);
			
			if (current == m_productHead)
			{
				m_productHead = newProduct;
				//newProduct->setPrev(nullptr);
			}
			else
			{
				Product* temp{ current->getPrev() };
				newProduct->setPrev(temp);
				if (temp)
					temp->setNext(newProduct);
			}
			
			current->setPrev(newProduct);
		}
		else if (choice == 2)//after
		{
			std::cout << "\nEnter the name of product after which you'd like to add new element: ";
			std::string currentItem{ getString() };

			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			if (current == nullptr)
			{
				std::cerr << "There's no such product in the list!\n";
				return;
			}

			std::cout << "\nEnter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nEnter new product's quantity: ";
			int newQuantity{ getValue() };

			Product* newProduct{ new Product{newName, newQuantity} };

			Product* temp{ current->getNext() };
			newProduct->setNext(temp);
			newProduct->setPrev(current);
			if (temp)
				temp->setPrev(newProduct);
			current->setNext(newProduct);
		}
		else
		{
			std::cerr << "\nInput error, please repeat!\n";
		}
	}
}

bool Provider::findProduct(std::string& productName) 
{
	Product* current{ m_productHead };
	while (current != nullptr && current->getName() != productName)
	{
		current = current->getNext();
	}
	
	if (current == nullptr)
		return false;

	return true;
}


void Provider::removeProduct(std::string& providerName, std::string& productName)
{
	if (isProviderEmpty())
	{
		std::cout << "provider " << providerName << " is empty\n";
	}
	if (!findProduct(productName))
	{
		std::cout << "\ncouldn't find this product\n";
		return;
	}
	
	Product* current{ m_productHead };
	while (current->getName() != productName)
		current = current->getNext();

	if (current == m_productHead)
		m_productHead = current->getNext();

	if (current->getPrev() != nullptr)
		current->getPrev()->setNext(current->getNext());
	if (current->getNext() != nullptr)
		current->getNext()->setPrev(current->getPrev());

	delete current;
}

void Provider::printProducts()
{
	if (isProviderEmpty())
	{
		std::cout << "there's no products\n";
		return;
	}
	Product* current{ m_productHead };
	while (current != nullptr)
	{
		std::cout  << current->getName() << " (" << current->getQuantity() << ")";
		current = current->getNext();
		if (current != nullptr)
			std::cout << ", ";
		else
			std::cout << '\n';
	}
}

void Provider::addProduct(std::string& productName, int productQuantity) // функция добаваления продукта при считывании с файла
{																		// добавляет последовательно. так, как в самом файле
	Product* newProduct{ new Product{productName, productQuantity} };

	if (isProviderEmpty())
	{
		m_productHead = newProduct;

		newProduct->setNext(nullptr);
		newProduct->setPrev(nullptr);
	}
	else
	{
		Product* current{ m_productHead };
		while (current->getNext() != nullptr)
		{
			current = current->getNext();
		}

		Product* temp{ current->getNext() };
		newProduct->setNext(temp);
		newProduct->setPrev(current);
		if (temp)
			temp->setPrev(newProduct);
		current->setNext(newProduct);
	}
}

Provider::~Provider()
{

}