#ifndef PROVIDER_H
#define PROVIDER_H
//��������� (���) - ���������� ������� (��������, ����������)
//����������� ���� �������� �������������� �������
#include "Product.h"

#include <string>
 //�������� � ��������������� �������
class Provider
{
private:
	std::string m_name{};

	Provider* m_next{}; //?

	Product* m_productHead{};

public:
	Provider();
	Provider(std::string& name);

	void setName(std::string& name);
	void setProductHead(Product* producthead);
	void setNext(Provider* next);

	int getValue();
	std::string getString();

	std::string getName();
	Product* getProductHead();
	Provider* getProviderNext();

	bool isProviderEmpty();
	void addProduct(std::string& newName, int newQuantity);
	bool findProduct(std::string& productName);
	void removeProduct(std::string& productName);
	void printProducts();

	 //destructor
	//~Provider();
};

#endif