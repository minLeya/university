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
	int m_top{}; //��������� �� �����-��� ��� ������ �����-����?
	int m_count{}; //���������� ���������

public:
	Firm();
	Firm(std::string& name);

	void setName(std::string& name);
	void setTop(int newTop);
	void setCount(int newCount);

	std::string getName();
	int getTop();
	int getCount();

	std::string getString();

	bool isProviderEmpty();
	bool isProviderFull();

	void addProvider();
	void deleteProvider();
	void showProviders();

};


#endif // !FIRM_H
