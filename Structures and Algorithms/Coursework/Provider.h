#ifndef PROVIDER_H
#define PROVIDER_H

#include "Product.h"

#include <string>
 
class Provider
{
private:
	std::string m_name{}; //имя поставщика

	Product* m_productHead{}; //указатель на первый реальный элемент списка товаров

public:
	//конструкторы
	Provider();
	Provider(std::string& name);

	//set-методы
	void setName(std::string& name);
	void setProductHead(Product* producthead);
	
	//вспомогательные функции
	int getValue();
	std::string getString();

	//get-методы
	std::string getName();
	Product* getProductHead() const;
	
	//операции с двунаправленным списком
	bool isProviderEmpty() const;
	void addProduct();
	void addProduct(std::string& productName, int productQuantity);
	bool findProduct(const std::string& productName);
	void removeProduct(std::string& providerName, std::string& productName);
	void printProducts() const;

	//деструктор
	~Provider();
};

#endif