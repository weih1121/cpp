#define  _CRT_SECURE_NO_WARNINGS
#include "Teacher.h"
#include <functional>



struct student{
	char name[32];
	//std::string name;
	int age;
};

int main()
{
	std::string s = "xiaoming";
	Teacher t1(s, 15);
	//auto fp = Teacher::print;
	std::function<void (Teacher*)> fcn = &Teacher::print;
	fcn(&t1);
	//t1.print();
	student stu;
	memset(&s, 0, 0);
	stu.age = 15;
	strcpy(stu.name, "xiaowang");

	std::cout << stu.name << std::endl;

	system("pause");
	return 0;
}
