#include "Firm.h"
#include <iostream>

Firm::Firm() : m_name{ "Default Firm" }, m_stack{},
m_count{ 0 }, m_top{ -1 } //m_stackPointer{ 0 } //top{0}
{

}

Firm::Firm(std::string& name) : m_name{ name }, m_stack{},
m_count{ 0 }, m_top{ -1 } //m_stackPointer{ 0 }//top{0}
{

}

void Firm::setName(std::string& name)
{
	m_name = name;
}

void Firm::setTop(int newTop)
{
	m_top = newTop;
}

void Firm::setCount(int newCount)
{
	m_count = newCount;
}

std::string Firm::getName()
{
	return m_name;
}

int Firm::getTop()
{
	return m_top;
}

int Firm::getCount()
{
	return m_count;
}

const Provider& Firm::getProvider(int index) const
{
	return m_stack[index];
}

Provider& Firm::getProvider(int index)
{
	return m_stack[index];
}

bool Firm::isProviderEmpty()
{
	return m_count == 0;
}

bool Firm::isProviderFull()
{
	return m_count >= constants::size;
}

std::string Firm::getString()
{
	std::string string{};
	std::cin >> string;
	return string;
}

void Firm::addProvider(std::string& name) //add to the end
{
	if (isProviderFull())
	{
		std::cout << "stack is full\n";
	}
	else
	{
		Provider newProvider{};
		newProvider.setName(name);
		m_stack[m_top + 1] = newProvider;
		++m_top;
		++m_count;
	}
}

void Firm::removeProvider()
{
	if (isProviderEmpty())
	{
		std::cout << "stack is empty\n";
		return;
	}
	std::cout << "\nenter the name of provider to delete: ";
	std::string providerName{ getString() };
	int index{ findProvider(providerName) };
	if (index == -1)
	{
		std::cout << "\nthere's no such provider\n";
		return;
	}
	
	if (index == m_top) 
	{
		--m_top;
		--m_count;
	}
	else
	{	
		int auxiliaryTop{ -1 };
		Provider auxiliaryStack[constants::size]{};
		while (m_top >= 0)
		{
			if (m_top != index)
			{
				++auxiliaryTop;
				auxiliaryStack[auxiliaryTop] = m_stack[m_top];
			}
			--m_top;
		}

		while (auxiliaryTop >= 0)
		{
			++m_top;
			m_stack[m_top] = auxiliaryStack[auxiliaryTop];
			--auxiliaryTop;
		}

		--m_count;
	}
}

void Firm::printProviders()
{
	if (isProviderEmpty())
	{
		std::cout << "\nempty, there's no provider\n";
		return;
	}
	for (int i{ 0 }; i <= m_top; ++i)
	{
		std::cout << m_stack[i].getName() << ": ";
		m_stack[i].printProducts();
	}
}

int Firm::findProvider(std::string& providerName)
{
	for (int i{ 0 }; i <= m_top; ++i)
	{
		if (m_stack[i].getName() == providerName)
			return i;
	}
	return -1;
}

void Firm::addProduct(std::string& providerName, std::string& productName, int productQuantity) // функция добавления продукта при считывании с файла
{
	
	int currentIndex{ findProvider(providerName) };
	if (currentIndex == -1)
	{
		return;
	}
	Provider& currentProvider{ m_stack[currentIndex] };
	currentProvider.addProduct(productName, productQuantity);
}