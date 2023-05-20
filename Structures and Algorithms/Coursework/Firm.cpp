#include "Firm.h"
#include <iostream>

Firm::Firm() : m_name{ "Firm" }, m_stack{},
			   m_top{ -1 }, m_count{ 0 } //top{0}
{

}

Firm::Firm(std::string& name) : m_name{ name }, m_stack{},
								m_top{ -1 }, m_count{ 0 }//top{0}
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

void Firm::setCount(int newTop)
{
	m_top = newTop;
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

bool Firm::isProviderEmpty()
{
	return (m_count == 0);
}

bool Firm::isProviderFull()
{
	return (m_count >= constants::size);
}

std::string Firm::getString()
{
	std::string string{};
	std::cin >> string;
	return string;
}

void Firm::addProvider()
{
	if (isProviderFull())
	{
		std::cout << "stack is full\n";
	}
	else
	{
		Provider newProvider{};
		std::string newName{ getString() };
		newProvider.setName(newName);
		setTop(getTop() + 1);
		setCount(getCount() + 1);	
		m_stack[m_top] = newProvider;
	}
}

void Firm::deleteProvider()
{
	if (isProviderEmpty())
	{
		std::cout << "stack is empty\n";
	}
	else
	{
		setTop(getTop() - 1);
		setCount(getCount() - 1);
	}
}

void Firm::showProviders()
{
	if (isProviderEmpty())
	{
		std::cout << "empty, there's no provider\n";
		return;
	}
	for (int i{ 0 }; i <= m_count - 1; ++i)
	{
		std::cout << "provider: " << m_stack[i].getName() << '\n';
	}
}
