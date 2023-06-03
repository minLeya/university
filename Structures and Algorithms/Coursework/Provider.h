#ifndef PROVIDER_H
#define PROVIDER_H
//поставщик (имя) - композиция товаров (название, количество)
//статический стек двоичных дунаправленных списков
#include "Product.h"

#include <string>
 //операции с двунаправленным списком
class Provider
{
private:
	std::string m_name{};

	Product* m_productHead{};

public:
	Provider();
	Provider(std::string& name);

	void setName(std::string& name);
	void setProductHead(Product* producthead);
	

	int getValue();
	std::string getString();

	std::string getName();
	Product* getProductHead() const;
	

	bool isProviderEmpty();
	void addProduct();
	void addProduct(std::string& productName, int productQuantity);
	bool findProduct(std::string& productName);
	void removeProduct(std::string& providerName, std::string& productName);
	void printProducts();

	 //destructor
	~Provider();
};

#endif