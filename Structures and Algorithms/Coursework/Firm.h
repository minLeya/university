#ifndef FIRM_H
#define FIRM_H

#include "Provider.h"
#include <string>

// ������������� ���� � ����������-�������� �����
namespace constants
{
	int constexpr size{ 5 };
}

class Firm
{
private:
	std::string m_name{}; //�������� �������� �����
	Provider m_stack[constants::size]{}; // ���� �� �����������
	int m_top{}; // ��������� �� ������ �����-�������
	int m_count{}; // ���������� ��������� � �����
	
public:
	// ������������
	Firm();
	Firm(std::string& name);

	// set-������
	void setName(std::string& name);
	void setTop(int newTop);
	void setCount(int newCount);

	//get-������
	std::string getName();
	int getTop();
	int getCount();
	const Provider& getProvider(int index) const;
	Provider& getProvider(int index);

	std::string getString();

	// �������� ��� �����
	bool isProviderEmpty();
	bool isProviderFull();
	void addProvider(std::string& name);
	void removeProvider();
	int findProvider(std::string& providerName);
	void printProviders();

	void addProduct(std::string& providerName, std::string& productName, int productQuantity);

	// ����������
	~Firm() = default;
};

#endif // !FIRM_H