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
	cout << dt.m_y << "��" << dt.m_m << "��" << dt.m_d << "��";
	return os;
}
const char *Sex[] = { "Ů", "��", "����" };
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
//��ʼ����ַ��Ӧ�� 
void initadds()
{
	ifstream inFile("���֤��ַ��Ӧ��.txt", ios::in);
	int a;
	string add;
	while (inFile >> a >> add)
		adds.insert(make_pair(a, add));
	inFile.close();
}
void menu()
{
	cout << "*************************" << endl
		<< "* 1 ���֤������֤" << endl
		<< "* 2 ���֤�������" << endl
		<< "* 3 ���֤����ת��" << endl
		<< "* 4 �˳�" << endl
		<< "*************************" << endl
		<< "��ѡ�� ��";
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
		cout << "���������֤�ţ�";
		cin >> id;
		switch (sel)
		{
		case 1:
			if (isRight(id))
				cout << "��������֤����Ϸ�!" << endl;
			else
				cout << "��������֤����Ƿ�!" << endl;
			break;
		case 2:
			cout << "��ַ:\t" << adds[getadd(id)] << endl;
			cout << "����:\t" << getDate(id) << endl;
			cout << "˳����:\t" << getOrdernum(id) << endl;
			cout << "�Ա�:\t" << Sex[getSex(id)] << endl;
			break;
		case 3:
			if (changeID(id))
				cout << id << endl;
			else
				cout << "��������֤����Ƿ�" << endl;
			break;
		}
	}
}
//����18λ���֤��У����
//����õ�����У���������ж�Ӧ������ֵ 
int getCheckCode(const string &id)
{
	int n = 0;
	for (int i = 0; i != 17; ++i)
		n += (id[i] - '0') * a[i];
	n %= 11;
	return n;
}
//��֤���֤�����Ƿ�Ϸ� 
bool isRight(const string &id)
{
	if (id.size() == 15)	//��֤15λ���֤���룬ֻ���Ƿ����� 
	{
		for (int i = 0; i != 17; ++i)
		{
			if (id[i] < '0' || id[i] > '9')
				return false;
		}
		return true;
	}
	else if (id.size() == 18)	//��֤18λ���룬ǰʮ��λΪ����
	{							//���һλʽ��������У����Ƚ� 
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
//��ȡ���֤�ĵ�ַ��Ϣ 
int getadd(const string &id)
{
	int n = 0;
	for (int i = 0; i != 6; ++i)
		n = n * 10 + id[i] - '0';
	return n;
}
//��ȡ���֤��������Ϣ 
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
//��ȡ�Ա� 
int getSex(const string &id)
{
	if (id.size() == 18)
		return (id[16] - '0') % 2;
	else if (id.size() == 15)
		return (id[14] - '0') % 2;
	else
		return 2;
}
//��ȡ���֤��˳���� 
int getOrdernum(const string &id)
{
	int num = 0;
	//�������֤λ���ж�˳���뿪ʼλ�� 
	int pos = (id.size() == 18) ? 14 : 12;
	for (int i = pos; i != pos + 3; ++i)
		num = num * 10 + id[i] - '0';
	return num;
}
//�ٶ�15λ���֤����19--�������
//�������ĺ�����15λ����ת����18λ����
//�������ĺ�����18λ����ת����15λ���� 
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
