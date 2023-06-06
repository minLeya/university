#include "Product.h"
#include <iostream>

Product::Product()	:	m_name{ "Default Product" }, m_quantity{ 1 },
						m_next{ nullptr }, m_prev{ nullptr }
{
}

Product::Product(std::string& name, int quantity) :
						m_name{ name }, m_quantity{ quantity },
						m_next{ nullptr }, m_prev{ nullptr }
{
}

void Product::setName(std::string& name)
{
	m_name = name;
}

void Product::setQuantity(int quantity)
{
	m_quantity = quantity;
}

void Product::setNext(Product* const next)
{
	m_next = next;
}

void Product::setPrev(Product* const prev)
{
	m_prev = prev;
}

std::string Product::getName()
{
	return m_name;
}

int Product::getQuantity()
{
	return m_quantity;
}

Product*& Product::getNext()
{
	return m_next;
}

Product*& Product::getPrev()
{
	return m_prev;
}

