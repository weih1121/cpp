#include <iostream>
#include <stack>

struct stack {
	void push(const int &num);
	void pop();
	int getMin();

	std::stack<int> stackData;
	std::stack<int> stackMin;
};//自定义栈 实现pop,push，getmin 时间复杂度o(1)

int main()//主函数
{
	stack stk;
	for (int i = 0; i < 10; ++i)
	{
		stk.push((rand() % 152));
	}

	for (int i = 0; i < 5; ++i)
	{
		stk.pop();
		std::cout << stk.getMin() << std::endl;
	}

	system("pause");
	return 0;
}

void stack::push(const int &num)//push
{
	stackData.push(num);
	
	if (stackMin.empty())
	{
		stackMin.push(num);
	}
	else
	{
		if (stackMin.top() > num)
		{
			stackMin.push(num);
		}
	}
}

void stack::pop()//pop 相对来讲pop比较费时
{
	if (stackData.top() > stackMin.top() && !stackData.empty())
	{
		stackData.pop();
	}
	else
	{
		stackData.pop();
		stackMin.pop();
	}
}

int stack::getMin()//getmin()
{
	if (stackMin.empty())
	{
		std::cout << "stack is null" << std::endl;
		return -1;
	}
	else
	{
		return stackMin.top();

	}
	
}