#include "Firm.h"
#include <iostream>

Firm::Firm() : m_name{ "Firm" }, m_stack{},
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

//void Firm::setProviderHead(Provider* newHead)
//{
//	m_providerHead = newHead;
//}

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

//Provider* Firm::getProviderHead()
//{
//	return m_providerHead;
//}

Provider Firm::getProvider(int index)
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

void Firm::addProvider() //add to the end
{
	if (isProviderFull())
	{
		std::cout << "stack is full\n";
	}
	else
	{
		std::cout << "enter the name of provider: ";
		Provider newProvider{};
		std::string newName{ getString() };
		newProvider.setName(newName);
		m_stack[m_top + 1] = newProvider;
		setTop(getTop() + 1);
		setCount(getCount() + 1);
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
	int auxiliaryTop{ 0 };
	Provider auxiliaryStack[5]{};
	if (index == -1)
	{
		std::cout << "\nthere's no such provider\n";
		return;
	}
	else if (index == getTop()) 
	{
		setTop(getTop() - 1);
		setCount(getCount() - 1);
	}
	else
	{
		
		for (int i{ getTop() }; i > index; --i)
		{
			auxiliaryStack[auxiliaryTop] = m_stack[i];
			++auxiliaryTop;
		}
		setTop(getTop() - 1);
		setCount(getCount() - 1);
		/*while (index < getTop())
		{
			m_stack[index] = auxiliaryStack[auxiliaryTop];
			--auxiliaryTop;
			++index;
		}*/

		/*for (int t{ index }; t < getTop(); ++t)
		{
			m_stack[t] = auxiliaryStack[auxiliaryTop];
			--auxiliaryTop;
		}*/
		
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
		std::cout << "provider: " << m_stack[i].getName() << '\n';
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

//destructor!!