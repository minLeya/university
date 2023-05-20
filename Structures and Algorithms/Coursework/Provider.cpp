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

std::string Provider::getName()
{
	return m_name;
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

bool Provider::isProductEmpty(Product* productHead)
{
	return(productHead->getNext() == productHead);
}

void Provider::addProduct(Product* productHead)
{
	if (Provider::isProductEmpty(productHead))
	{
		std::cout << "\nEnter new element: ";
		int newQuantity{ getValue() };
		std::string newName{ getString() };

		Product* newProduct{ new Product{} };
		productHead->setNext(newProduct);
		productHead->setPrev(newProduct);
		newProduct->setQuantity(newQuantity);
		newProduct->setName(newName);
		newProduct->setNext(productHead);
		newProduct->setPrev(productHead);
	}

}