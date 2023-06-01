#ifndef FIRM_H
#define FIRM_H
//����������� ���� �������������� �������
//�������� ����� (��������) - ���������� ����������� (�����)
//����� �������� ��� ����� 
#include "Provider.h"
#include <string>

namespace constants
{
	int constexpr size{ 5 };
}

class Firm
{
private:
	std::string m_name{};
	Provider m_stack[constants::size]{};
	int m_top{}; //��������� �� �����-���
	int m_count{}; //���������� ���������
	//int m_stackPointer{}; //��������� �� ������ ��������� ������
	//Provider* m_providerHead{};
public:
	Firm();
	Firm(std::string& name);

	void setName(std::string& name);
	void setTop(int newTop);
	void setCount(int newCount);
	//void setProviderHead(Provider* newHead);

	std::string getName();
	int getTop();
	int getCount();
	//Provider* getProviderHead();
	Provider getProvider(int index);

	std::string getString();

	bool isProviderEmpty();
	bool isProviderFull();

	void addProvider();
	void removeProvider();
	int findProvider(std::string& providerName);
	void printProviders();

};

#endif // !FIRM_H