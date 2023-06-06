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

bool Provider::isProviderEmpty() const
{
	return (m_productHead == nullptr); //список незакольцованный без заголовочного элемента
}

// добавление товара
void Provider::addProduct() 
{
	if (isProviderEmpty()) //если у поставщика нет товаров
	{
		std::cout << "\nenter new product's name: ";
		std::string newName{ getString() };
		std::cout << "\nenter new product's quantity: ";
		int newQuantity{ getValue() };
		
		Product* newProduct{ new Product{newName, newQuantity} }; //создается товар, заполняются информационные поля

		m_productHead = newProduct; //добавленный товар становится m_productHead
		
		newProduct->setNext(nullptr); 
		newProduct->setPrev(nullptr); 
	}
	else //если у поставщика есть товары
	{
		//спрашиваем у пользователя, добавить до (1) или после (2) определенного товара
		std::cout << "\nenter 1 to add before specific product, enter 2 to add after: "; 
		int choice{ getValue() };

		if (choice == 1) //до
		{
			//спрашиваем у пользователя название товара, до которого будет добавляться новый товар
			std::cout << "\nenter the name of product before which you'd like to add new element: ";
			std::string currentItem{ getString() };

			//поиск этого товара в списке
			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}
			
			//если товар не найден
			if (current == nullptr)
			{
				std::cerr << "there's no such product in the list!\n";
				return;
			}

			//товар найден - спршиваем название и количество нового товара
			std::cout << "\nenter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nenter new product's quantity: ";
			int newQuantity{ getValue() };
			
			//создаем товар
			Product* newProduct{ new Product{newName, newQuantity} };
			newProduct->setNext(current);
			
			//если добавляется до первого элемента в списке
			if (current == m_productHead)
			{
				m_productHead = newProduct;
			}
			//иначе
			else
			{
				Product* temp{ current->getPrev() };
				newProduct->setPrev(temp);
				if (temp)
					temp->setNext(newProduct);
			}
			
			current->setPrev(newProduct);
		}
		else if (choice == 2) //после
		{
			//спрашиваем у пользователя название товара, после которого будет добавляться новый товар
			std::cout << "\nenter the name of product after which you'd like to add new element: ";
			std::string currentItem{ getString() };

			//поиск этого товара в списке
			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			//если товар не найден
			if (current == nullptr)
			{
				std::cerr << "there's no such product in the list!\n";
				return;
			}

			//товар найден - спршиваем название и количество нового товара
			std::cout << "\nenter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nenter new product's quantity: ";
			int newQuantity{ getValue() };

			//создаем новый товар
			Product* newProduct{ new Product{newName, newQuantity} };

			Product* temp{ current->getNext() };
			newProduct->setNext(temp);
			newProduct->setPrev(current);
			if (temp)
				temp->setPrev(newProduct);
			current->setNext(newProduct);
		}
		else //если пользователь ввел не 1 и не 2
		{
			std::cerr << "\ninput error, please repeat!\n";
		}
	}
}

//поиск товара
bool Provider::findProduct(const std::string& productName) 
{
	//начинаем с первого элемента
	Product* current{ m_productHead };
	//поиск продолжается до тех пор, пока не дойдем до конца списка
	//или не найдем элемент, который ищем
	while (current != nullptr)
	{
		if (current->getName() == productName)
			return true;

		current = current->getNext();
	}

	return false;
	
}

//удаление товара из списка
void Provider::removeProduct(std::string& providerName, std::string& productName)
{
	//если в поставщике нет товаров
	if (isProviderEmpty())
	{
		std::cout << "provider " << providerName << " is empty\n";
		return;
	}
	//поиск товара у данного поставщика
	if (!findProduct(productName))
	{
		std::cout << "\ncouldn't find this product\n";
		return;
	}
	
	//поиск удаляемого товара
	Product* current{ m_productHead };
	while (current->getName() != productName)
		current = current->getNext();

	//если удаляемый товар - первый элемент
	if (current == m_productHead)
		m_productHead = current->getNext();

	// если удаляемый товар - НЕ первый элемент
	if (current->getPrev() != nullptr)
		current->getPrev()->setNext(current->getNext());
	if (current->getNext() != nullptr)
		current->getNext()->setPrev(current->getPrev());

	delete current;
}

// вывод товаров на экран
void Provider::printProducts() const
{
	// если у поставщика нет товаров
	if (isProviderEmpty())
	{
		std::cout << "there's no products\n";
		return;
	}
	// начинаем с первого элемента
	Product* current{ m_productHead }; //nullptr
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

// функция добавления продукта в список при считывании с файла
// добавляет последовательно. так, как в самом файле
void Provider::addProduct(std::string& productName, int productQuantity)
{					
	//создается новый продукт
	Product* newProduct{ new Product{productName, productQuantity} };

	if (isProviderEmpty())
	{
		m_productHead = newProduct;

		newProduct->setNext(nullptr);
		newProduct->setPrev(nullptr);
	}
	else
	{
		Product* current{ m_productHead }; //переменная для отслеживания
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

//деструтор 
Provider::~Provider()
{
	Product* current{ m_productHead };
	Product* old{ current };
	while (current != nullptr)
	{
		current = current->getNext();
		delete old;
		old = current;
	}
}