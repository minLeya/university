#include "Firm.h"
#include <iostream>
#include <functional>

Firm::Firm() : m_name{ "Default Firm" }, m_stack{},
				m_count{ 0 }, m_top{ -1 } 
{

}

Firm::Firm(std::string& name) : m_name{ name }, m_stack{},
				m_count{ 0 }, m_top{ -1 } 
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

// проверка стека на пустоту
bool Firm::isProviderEmpty()
{
	return m_count == 0;
}

// проверка стека на полноту
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

// добавление поставщика
void Firm::addProvider(std::string& name)
{
	// если стек полон
	if (isProviderFull())
	{
		std::cout << "stack is full\n";
	}
	// иначе
	else
	{
		// создаетс€ поставщик
		Provider newProvider{ name };
		// ставитс€ на следующую €чейку после вершины стека
		m_stack[m_top + 1] = newProvider;
		// указатель на вершину стека и количество элментов в стеке
		// увеличиваютс€ на 1
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
		Provider* auxiliaryStack[constants::size]{};
		while (m_top >= 0)
		{
			if (m_top != index)
			{
				++auxiliaryTop;
				auxiliaryStack[auxiliaryTop] = &m_stack[m_top];
			}
			--m_top;
		}

		while (auxiliaryTop >= 0)
		{
			++m_top;
			m_stack[m_top] = *auxiliaryStack[auxiliaryTop];
			--auxiliaryTop;
		}

		--m_count;
	}
}

// вывод поставщиков на экран
void Firm::printProviders()
{
	// если поставщиков нет
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

// поиск поставщика по его имени
int Firm::findProvider(std::string& providerName)
{
	for (int i{ 0 }; i <= m_top; ++i)
	{
		if (m_stack[i].getName() == providerName)
			return i; // возвращает индекс, если поставщик найден
	}
	return -1; //возвращает -1, если не найден
}

// функци€ добавлени€ продукта при считывании с файла
void Firm::addProduct(std::string& providerName, std::string& productName, int productQuantity) 
{
	// ищем поставщика по имени
	int currentIndex{ findProvider(providerName) };
	if (currentIndex == -1)
	{
		return;
	}
	// добавл€ем в стек
	Provider& currentProvider{ m_stack[currentIndex] };
	currentProvider.addProduct(productName, productQuantity);
}