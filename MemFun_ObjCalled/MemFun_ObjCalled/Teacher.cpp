#include "Teacher.h"



Teacher::Teacher(std::string _name, int _age) : name(_name), age(_age)
{
	std::cout << "Construct Fun Called" << std::endl;
}

Teacher::Teacher(const Teacher& t1)
{
	this->age = t1.age;
	this->name = t1.name;
}

Teacher& Teacher::operator=(const Teacher& t1)
{
	this->age = t1.age;
	this->name = t1.name;
	return *this;
}

Teacher::~Teacher()
{
}

void Teacher::print()
{
	std::cout << this->name << " " << this->age << std::endl;
}
