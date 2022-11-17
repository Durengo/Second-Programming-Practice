#include "item.h"

item::item(const std::string &nametemp, int agetemp, const std::string &addresstemp, double salarytemp)
{
	if (nametemp.length() > 60)
	{
		std::cout << "NAME TOO LONG\n";
		delete (this);
		return;
	}
	if (agetemp <= 0 || agetemp > 101)
	{
		std::cout << "INVALID AGE\n";
		delete (this);
		return;
	}
	if (salarytemp <= 0)
	{
		std::cout << "INVALID SALARY\n";
		delete (this);
		return;
	}
	name = nametemp;
	age = agetemp;
	address = addresstemp;
	salary = salarytemp;
}

const std::string &item::getName() const
{
	return name;
}

void item::setName(const std::string &name)
{
	item::name = name;
}

int item::getAge() const
{
	return age;
}

void item::setAge(int age)
{
	item::age = age;
}

std::string item::getAddress() const
{
	return address;
}

void item::setAddress(std::string address)
{
	item::address = address;
}

double item::getSalary() const
{
	return salary;
}

void item::setSalary(double salary)
{
	item::salary = salary;
}
