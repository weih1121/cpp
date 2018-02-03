#include <iostream>
#include <string>

class student
{
public:
	student(std::string name, int age) : name(name), age(age)
	{
		std::cout << "student()" << std::endl;
	}
	~student()
	{
		std::cout << "~student()" << std::endl;
	}
private:
	std::string name;
	int age;

};

int main()
{
	int i = 0;
	const int j = 0;
	std::cout << sizeof(i) << std::endl;
	std::cout << sizeof(j) << std::endl;

	system("pause");
	return 0;
}