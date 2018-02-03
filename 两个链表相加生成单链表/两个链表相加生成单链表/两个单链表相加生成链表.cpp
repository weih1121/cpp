#include <iostream>

struct Node {
	int		value;
	Node	*next;
	Node(int data) : value(data), next(nullptr) {};
};

Node	*reverse(Node * head);
Node	*addTwoList(Node * head1, Node *head2);
void	print(Node *head);

int main()
{
	Node n1(9);
	Node n2(3);
	Node n3(8);
	n1.next = &n2;
	n2.next = &n3;

	Node b1(6);
	Node b2(3);
	b1.next = &b2;

	//print(reverse(&n1));			//	测试链表翻转函数以及print函数
	print(addTwoList(&n1, &b1));

	system("pause");
	return 0;
}

Node * reverse(Node * head) {
	if (head == nullptr) {
		return head;
	}

	Node * pre	= nullptr;
	Node * next = nullptr;
	while (head != nullptr) {
		next = head->next;
		head->next = pre;
		pre = head;
		head = next;
	}
	return pre;
}

void print(Node * head)
{
	while (head != nullptr) {
		std::cout << head->value << std::endl;
		head = head->next;
	}
}

Node *addTwoList(Node * head1, Node *head2)
{
	head1 = reverse(head1);
	head2 = reverse(head2);

	int add = 0, n1 = 0, n2 = 0;
	Node * cur1 = head1, *cur2 = head2, *n = nullptr;

	while (cur1 != nullptr || cur2 != nullptr) {
		n1 = cur1 == nullptr ? 0 : cur1->value;
		n2 = cur2 == nullptr ? 0 : cur2->value;

		if (cur1!= nullptr)
			cur1 = cur1->next;
		if (cur2 != nullptr)
			cur2 = cur2->next;

		Node * node = new Node((n1 + n2 + add) % 10);
		if (n1 + n2 + add >= 10)
			add = 1;
		else
			add = 0;

		node->next = n;
		n = node;
	}
	if (add == 1) {
		Node * node = new Node(1);
		node->next = n;
		n = node;
	}

	reverse(head1);
	reverse(head2);
	return n;
}
