#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
private:
	std::string m_name{}; //название продукта
	int m_quantity{}; //количество продукта

	Product* m_next{}; //указатель на следующий продукт в списке
	Product* m_prev{}; // указатель на предыдущий продукт в списке

public:
	//конструкторы
	Product();
	Product(std::string& name, int quantity);

	//set-методы
	void setName(std::string& name);
	void setQuantity(int quantity);
	void setNext(Product* const next);
	void setPrev(Product* const prev);

	//get-методы
	std::string getName();
	int getQuantity();
	Product*& getNext();
	Product*& getPrev();

	//деструктор
	~Product() = default;
};

#endif // !PRODUCT_H
