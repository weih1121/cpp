#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

struct student {
	int no;
	int de;
	int cai;
	int sum;
	student() :no(0), de(0), cai(0), sum(0) {};

	bool operator<(const student &rhs)
	{
		if (this->sum != rhs.sum)
			return this->sum > rhs.sum;
		else if (this->de != rhs.de)
			return this->de > rhs.de;
		else
			return this->no < rhs.no;
	}
};

void print(vector<student> &v)
{

	vector<student>::iterator it;
	for(it = v.begin(); it != v.end(); ++it)
		cout << it->no << " " << it->de << " " << it->cai << endl;
}

//bool comp(student &lhs, student &rhs)
//{
//	if (lhs.sum != rhs.sum)
//		return lhs.sum > rhs.sum;
//	else if (lhs.de != rhs.de)
//		return lhs.de > rhs.de;
//	else 
//		return lhs.no < rhs.no;
//}

int main()
{
	int n, l1, l2;//n为输入学生总数，l1最低录取分,l2优先录取分
	std::vector<student> sr;//圣人
	std::vector<student> yr;//愚人
	std::vector<student> jz;//君子
	std::vector<student> xr;//小人及符合条件的人

	cin >> n >> l1 >> l2;

	for (int i = 1; i <= n; ++i)
	{
		student tmp;
		std::cin >> tmp.no >> tmp.de >> tmp.cai;
		if (tmp.de >= l2 && tmp.cai >= l2)//sr
		{
			tmp.sum = tmp.de + tmp.cai;
			sr.push_back(tmp);
		}
		if (tmp.de >= l2 && tmp.cai >= l1 && tmp.cai < l2)//jz
		{
			tmp.sum = tmp.de + tmp.cai;
			jz.push_back(tmp);
		}
		if (tmp.de >= l1 && tmp.de < l2 && tmp.cai >= l1 && tmp.cai < l2 && tmp.de >= tmp.cai)//yr
		{
			tmp.sum = tmp.de + tmp.cai;
			yr.push_back(tmp);
		}
		if (tmp.de >= l1 && tmp.de < l2 && tmp.cai >= l1 && tmp.de < tmp.cai)//xr
		{
			tmp.sum = tmp.de + tmp.cai;
			xr.push_back(tmp);
		}
	}

	//std::sort(sr.begin(), sr.end(), comp);
	//std::sort(jz.begin(), jz.end(), comp);
	//std::sort(yr.begin(), yr.end(), comp);
	//std::sort(xr.begin(), xr.end(), comp);

	sort(sr.begin(), sr.end());
	sort(jz.begin(), jz.end());
	sort(yr.begin(), yr.end());
	sort(xr.begin(), xr.end());

	cout << sr.size() + jz.size() + yr.size() + xr.size() << endl;
	print(sr);
	print(jz);
	print(yr);
	print(xr);
	//system("pause");
	return 0;
}