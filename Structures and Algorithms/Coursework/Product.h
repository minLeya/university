#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
private:
	std::string m_name{}; //�������� ��������
	int m_quantity{}; //���������� ��������

	Product* m_next{}; //��������� �� ��������� ������� � ������
	Product* m_prev{}; // ��������� �� ���������� ������� � ������

public:
	//������������
	Product();
	Product(std::string& name, int quantity);

	//set-������
	void setName(std::string& name);
	void setQuantity(int quantity);
	void setNext(Product* const next);
	void setPrev(Product* const prev);

	//get-������
	std::string getName();
	int getQuantity();
	Product*& getNext();
	Product*& getPrev();

	//����������
	~Product() = default;
};

#endif // !PRODUCT_H
