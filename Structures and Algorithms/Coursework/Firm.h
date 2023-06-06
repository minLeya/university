#ifndef FIRM_H
#define FIRM_H

#include "Provider.h"
#include <string>

// пронстранство имен с константой-размером стека
namespace constants
{
	int constexpr size{ 5 };
}

class Firm
{
private:
	std::string m_name{}; //название торговой фирмы
	Provider m_stack[constants::size]{}; // стек из поставщиков
	int m_top{}; // указатель на индекс числа-вершины
	int m_count{}; // количество элементов в стеке
	
public:
	// конструкторы
	Firm();
	Firm(std::string& name);

	// set-методы
	void setName(std::string& name);
	void setTop(int newTop);
	void setCount(int newCount);

	//get-методы
	std::string getName();
	int getTop();
	int getCount();
	const Provider& getProvider(int index) const;
	Provider& getProvider(int index);

	std::string getString();

	// операции для стека
	bool isProviderEmpty();
	bool isProviderFull();
	void addProvider(std::string& name);
	void removeProvider();
	int findProvider(std::string& providerName);
	void printProviders();

	void addProduct(std::string& providerName, std::string& productName, int productQuantity);

	// деструктор
	~Firm() = default;
};

#endif // !FIRM_H