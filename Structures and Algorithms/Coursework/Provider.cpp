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
	return (m_productHead == nullptr); //������ ���������������� ��� ������������� ��������
}

// ���������� ������
void Provider::addProduct() 
{
	if (isProviderEmpty()) //���� � ���������� ��� �������
	{
		std::cout << "\nenter new product's name: ";
		std::string newName{ getString() };
		std::cout << "\nenter new product's quantity: ";
		int newQuantity{ getValue() };
		
		Product* newProduct{ new Product{newName, newQuantity} }; //��������� �����, ����������� �������������� ����

		m_productHead = newProduct; //����������� ����� ���������� m_productHead
		
		newProduct->setNext(nullptr); 
		newProduct->setPrev(nullptr); 
	}
	else //���� � ���������� ���� ������
	{
		//���������� � ������������, �������� �� (1) ��� ����� (2) ������������� ������
		std::cout << "\nenter 1 to add before specific product, enter 2 to add after: "; 
		int choice{ getValue() };

		if (choice == 1) //��
		{
			//���������� � ������������ �������� ������, �� �������� ����� ����������� ����� �����
			std::cout << "\nenter the name of product before which you'd like to add new element: ";
			std::string currentItem{ getString() };

			//����� ����� ������ � ������
			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}
			
			//���� ����� �� ������
			if (current == nullptr)
			{
				std::cerr << "there's no such product in the list!\n";
				return;
			}

			//����� ������ - ��������� �������� � ���������� ������ ������
			std::cout << "\nenter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nenter new product's quantity: ";
			int newQuantity{ getValue() };
			
			//������� �����
			Product* newProduct{ new Product{newName, newQuantity} };
			newProduct->setNext(current);
			
			//���� ����������� �� ������� �������� � ������
			if (current == m_productHead)
			{
				m_productHead = newProduct;
			}
			//�����
			else
			{
				Product* temp{ current->getPrev() };
				newProduct->setPrev(temp);
				if (temp)
					temp->setNext(newProduct);
			}
			
			current->setPrev(newProduct);
		}
		else if (choice == 2) //�����
		{
			//���������� � ������������ �������� ������, ����� �������� ����� ����������� ����� �����
			std::cout << "\nenter the name of product after which you'd like to add new element: ";
			std::string currentItem{ getString() };

			//����� ����� ������ � ������
			Product* current{ m_productHead };
			while (current != nullptr && current->getName() != currentItem)
			{
				current = current->getNext();
			}

			//���� ����� �� ������
			if (current == nullptr)
			{
				std::cerr << "there's no such product in the list!\n";
				return;
			}

			//����� ������ - ��������� �������� � ���������� ������ ������
			std::cout << "\nenter new product's name: ";
			std::string newName{ getString() };
			std::cout << "\nenter new product's quantity: ";
			int newQuantity{ getValue() };

			//������� ����� �����
			Product* newProduct{ new Product{newName, newQuantity} };

			Product* temp{ current->getNext() };
			newProduct->setNext(temp);
			newProduct->setPrev(current);
			if (temp)
				temp->setPrev(newProduct);
			current->setNext(newProduct);
		}
		else //���� ������������ ���� �� 1 � �� 2
		{
			std::cerr << "\ninput error, please repeat!\n";
		}
	}
}

//����� ������
bool Provider::findProduct(const std::string& productName) 
{
	//�������� � ������� ��������
	Product* current{ m_productHead };
	//����� ������������ �� ��� ���, ���� �� ������ �� ����� ������
	//��� �� ������ �������, ������� ����
	while (current != nullptr)
	{
		if (current->getName() == productName)
			return true;

		current = current->getNext();
	}

	return false;
	
}

//�������� ������ �� ������
void Provider::removeProduct(std::string& providerName, std::string& productName)
{
	//���� � ���������� ��� �������
	if (isProviderEmpty())
	{
		std::cout << "provider " << providerName << " is empty\n";
		return;
	}
	//����� ������ � ������� ����������
	if (!findProduct(productName))
	{
		std::cout << "\ncouldn't find this product\n";
		return;
	}
	
	//����� ���������� ������
	Product* current{ m_productHead };
	while (current->getName() != productName)
		current = current->getNext();

	//���� ��������� ����� - ������ �������
	if (current == m_productHead)
		m_productHead = current->getNext();

	// ���� ��������� ����� - �� ������ �������
	if (current->getPrev() != nullptr)
		current->getPrev()->setNext(current->getNext());
	if (current->getNext() != nullptr)
		current->getNext()->setPrev(current->getPrev());

	delete current;
}

// ����� ������� �� �����
void Provider::printProducts() const
{
	// ���� � ���������� ��� �������
	if (isProviderEmpty())
	{
		std::cout << "there's no products\n";
		return;
	}
	// �������� � ������� ��������
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

// ������� ���������� �������� � ������ ��� ���������� � �����
// ��������� ���������������. ���, ��� � ����� �����
void Provider::addProduct(std::string& productName, int productQuantity)
{					
	//��������� ����� �������
	Product* newProduct{ new Product{productName, productQuantity} };

	if (isProviderEmpty())
	{
		m_productHead = newProduct;

		newProduct->setNext(nullptr);
		newProduct->setPrev(nullptr);
	}
	else
	{
		Product* current{ m_productHead }; //���������� ��� ������������
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

//��������� 
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