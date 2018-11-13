#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;
class Date
{
	int m_y, m_m, m_d;
public:
	Date(int y, int m, int d) : m_y(y), m_m(m), m_d(d) {	}
	friend ostream& operator << (ostream &os, const Date &dt);
};
ostream& operator << (ostream &os, const Date &dt)
{
	cout << dt.m_y << "年" << dt.m_m << "月" << dt.m_d << "日";
	return os;
}
const char *Sex[] = { "女", "男", "错误" };
map<int, string> adds;
int a[] = { 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2,2 };
char b[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };

int getCheckCode(const string &id);
bool isRight(const string &id);
int getadd(const string &id);
Date getDate(const string &id);
int getSex(const string &id);
int getOrdernum(const string &id);
bool changeID(string &old_id);
//初始化地址对应表 
void initadds()
{
	ifstream inFile("身份证地址对应表.txt", ios::in);
	int a;
	string add;
	while (inFile >> a >> add)
		adds.insert(make_pair(a, add));
	inFile.close();
}
void menu()
{
	cout << "*************************" << endl
		<< "* 1 身份证号码验证" << endl
		<< "* 2 身份证号码解析" << endl
		<< "* 3 身份证号码转换" << endl
		<< "* 4 退出" << endl
		<< "*************************" << endl
		<< "请选择 ：";
}
int main()
{
	initadds();
	menu();
	int sel;
	string id;
	while (cin >> sel)
	{
		if (0 == sel)
			break;
		cout << "请输入身份证号：";
		cin >> id;
		switch (sel)
		{
		case 1:
			if (isRight(id))
				cout << "输入的身份证号码合法!" << endl;
			else
				cout << "输入的身份证号码非法!" << endl;
			break;
		case 2:
			cout << "地址:\t" << adds[getadd(id)] << endl;
			cout << "生日:\t" << getDate(id) << endl;
			cout << "顺序码:\t" << getOrdernum(id) << endl;
			cout << "性别:\t" << Sex[getSex(id)] << endl;
			break;
		case 3:
			if (changeID(id))
				cout << id << endl;
			else
				cout << "输入的身份证号码非法" << endl;
			break;
		}
	}
}
//计算18位身份证的校验码
//计算得到的是校验码数组中对应的索引值 
int getCheckCode(const string &id)
{
	int n = 0;
	for (int i = 0; i != 17; ++i)
		n += (id[i] - '0') * a[i];
	n %= 11;
	return n;
}
//验证身份证号码是否合法 
bool isRight(const string &id)
{
	if (id.size() == 15)	//验证15位身份证号码，只看是否数字 
	{
		for (int i = 0; i != 17; ++i)
		{
			if (id[i] < '0' || id[i] > '9')
				return false;
		}
		return true;
	}
	else if (id.size() == 18)	//验证18位号码，前十七位为数字
	{							//最后一位式与计算出的校验码比较 
		for (int i = 0; i != 17; ++i)
		{
			if (id[i] < '0' || id[i] > '9')
				return false;
		}
		int n = getCheckCode(id);
		return b[n] == id[17];
	}
	else
		return false;
}
//获取身份证的地址信息 
int getadd(const string &id)
{
	int n = 0;
	for (int i = 0; i != 6; ++i)
		n = n * 10 + id[i] - '0';
	return n;
}
//获取身份证的日期信息 
Date getDate(const string &id)
{
	int y = 0, m = 0, d = 0;
	if (id.size() == 18)
	{
		for (int i = 6; i != 10; ++i)
			y = y * 10 + id[i] - '0';
		for (int i = 10; i != 12; ++i)
			m = m * 10 + id[i] - '0';
		for (int i = 12; i != 14; ++i)
			d = d * 10 + id[i] - '0';
	}
	else if (id.size() == 15)
	{
		for (int i = 6; i != 8; ++i)
			y = y * 10 + id[i] - '0';
		y += 1900;
		for (int i = 8; i != 10; ++i)
			m = m * 10 + id[i] - '0';
		for (int i = 10; i != 12; ++i)
			d = d * 10 + id[i] - '0';
	}
	return Date(y, m, d);
}
//获取性别 
int getSex(const string &id)
{
	if (id.size() == 18)
		return (id[16] - '0') % 2;
	else if (id.size() == 15)
		return (id[14] - '0') % 2;
	else
		return 2;
}
//获取身份证的顺序码 
int getOrdernum(const string &id)
{
	int num = 0;
	//根据身份证位数判断顺序码开始位置 
	int pos = (id.size() == 18) ? 14 : 12;
	for (int i = pos; i != pos + 3; ++i)
		num = num * 10 + id[i] - '0';
	return num;
}
//假定15位身份证都是19--年代生人
//如果输入的号码是15位，则转换成18位号码
//如果输入的号码是18位，则转换成15位号码 
bool changeID(string &old_id)
{
	if (!isRight(old_id))
		return false;
	if (old_id.size() == 15)
	{
		old_id.insert(6, "19");
		int n = getCheckCode(old_id);
		old_id += b[n];
	}
	else
	{
		old_id.erase(17, 1);
		old_id.erase(6, 2);
	}
	return true;
}
