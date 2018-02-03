#pragma once
#include <iostream>
#include <string>

class Teacher
{
public:
	Teacher(std::string name, int age);
	Teacher(const Teacher &t1);
	Teacher& operator=(const Teacher &t1);
	~Teacher();

public:
	void print();

private:
	std::string name;
	int			age;
};

