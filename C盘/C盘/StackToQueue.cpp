#include <iostream>
#include <stack>

class queue
{
public:
	void add(const int &num);
	int poll();
	int peek();

private:
	std::stack<int> stackPush;
	std::stack<int> stackPop;
};

void queue::add(const int &num)
{
	stackPush.push(num);
	while (!stackPush.empty())
	{
		stackPop.push(stackPush.top());
		stackPush.pop();
	}
}

int queue::poll()//删除队头元素 返回队头元素
{
	if (!stackPop.empty())
	{
		int tmp = stackPop.top();
		stackPop.pop();
		return tmp;
	}
}

int queue::queue::peek()//读取队头元素
{
	if (!stackPop.empty())
	{
		return stackPop.top();
	}
}