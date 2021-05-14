#include<stdio.h>
#include<iostream>
using namespace std;
class Date
{
public:
	//ȫȱʡĬ�Ϲ���
	Date(int y = 2021, int m = 5, int d = 1)
	{
		if (y <= 0 || m <= 0 || m > 12 || d <= 0 || d > getDay(y, m))
		{
			//������Ч
			_y = 2021;
			_m = 5;
			_d = 1;
			cout << "������Ч����ΪĬ��ֵ:2021.5.1 " << endl;
		}
		else
		{
			_y = y;
			_m = m;
			_d = d;
		}
	}
	int getDay(int y, int m)
	{
		static int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[m];
		if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0))
		{
			day+=1;
		}
		return day;
	}
	//�������캯��
	Date(const Date& d)
	{
		_y = d._y;
		_m = d._m;
		_d = d._d;
	}
	~Date()
	{
		//û����Դ�Ͳ�����������������������ɶҲ������
	}
	//�������㣺Date+=int
	Date& operator+=(int day)
	{
		//�ж������Ƿ�Ϊ����
		if (day < 0)
			return *this -= -day;

		//�������
		_d += day;
		//�ж������Ƿ����
		while(_d > getDay(_y, _m))
		{
			//��ȥ���µ�����
			_d -= getDay(_y, _m);

			//�·ݽ�λ
			++_m;
			
			//�ж��·��Ƿ����
			if (_m == 13)
			{
				//��ݽ�λ����Ϊ��һ���һ�·�
				++_y;
				_m = 1;
			}
		}
		//�������֮��Ľ��
		return *this;
	}
	
	//�������㣺Date + int 
	//�������֮��Ľ�������������ܸı�
	Date& operator+(int day)
	{
		//����һ�����ݽ�������
		static Date copy_data(*this);

		//����+=�Ľӿ�
		copy_data+= day;

		//�������֮��Ľ��
		return copy_data;
	}

	//ǰ��++
	Date& operator++()
	{
		////����1���� -------��û�еڶ��ּ��
		////������1
		//_d += 1;

		////�ж������Ƿ�Խ��
		//if (_d > getDay(_y, _m))
		//{
		//	_d -= getDay(_y, _m);
		//	_m += 1;
		//	if (_m == 13)
		//	{
		//		_y += 1;
		//		_m = 1;
		//	}
		//}
		//return *this;
		//�ڶ��֣�����+=�ӿ�
		return *this += 1;
	}
	
	//����++�����ǰ��++����һ��int�Ͳ�����ֻ��Ϊ�˺�ǰ��++��������
	Date operator++(int)
	{
		Date copy(*this);
		*this += 1;
		//����++֮ǰ��ֵ
		return copy;
	}
	//-=
	Date operator-=(int day)
	{
		//�ж������Ƿ�Ϊ����
		if (day < 0)
			return *this += -day;

		_d -= day;
		//�ж������Ƿ����
		while(_d <= 0)
		{
			--_m;
			//�ж��·��Ƿ��������
			if (_m == 0)
			{
				_y --;
				_m = 12;
			}
			_d += getDay(_y, _m);
		}
		return *this;
	}
	//-
	Date operator-(int day)
	{
		Date copy = *this;
		copy -= (day);
		return copy;
	}
	//ǰ��--
	Date operator--()
	{
		return *this-=-1;
	}
	//����--
	Date operator--(int)
	{
		Date copy(*this);
		*this-=1;
		return copy;
	}
	//==
	bool operator==(const Date& d)
	{
		return _y == d._y
			&& _m == d._m
			&& _d == d._d;
	}
	//!=
	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}
	//>
	bool operator>(const Date& d)
	{
		if (_y > d._y)
			return true;
		else if (_y == d._y)
		{
			if (_m > d._m)
				return true;
			else if (_m == d._m)
			{
				if (_d > d._d)
					return true;
			}
		}
		return false;
	}
	//<
	bool operator<(const Date& d)
	{
		return !(*this >= d);
	}
	//>=
	bool operator>=(const Date& d)
	{
		return *this > d || *this == d;
	}
	//<=
	bool operator<=(const Date& d)
	{
		return !(*this > d);
	}
	//���������date1-date2
	int operator-(const Date& d)
	{
		//����Ƚ�С�����ھ������ٴ��Լӵ����㣬���ԺͱȽϴ��������ͬ
		//�ԼӵĴ���������������
		Date max = *this;
		Date min = d;
		int flag = 1;//flag=1��ʾ�������Ϊ����

		if (max < min)
		{
			max = d;
			min = *this;
			flag = -1;
		}
		int day = 0;
		while (min < max)
		{
			++min;
			++day;
		}
		return flag*day;
	}
private:
	int _y;
	int _m;
	int _d;
};

void test()
{
	Date d(2000, 4, 10);
	d += 365;
}
//void test()
//{
//	Date d1;	//����Ĭ�ϵ�����
//	Date d2(2021, 2, 7);
//	Date d3(d2);	//���ÿ������캯��
//	Date d4(2000, 1, 2);
//	d1 = d4;	//���ø�ֵ�����
//	Date d5, d6, d7;
//	d5 += 99;	//����+=����
//	d7 = d6 + 13;	//����+����
//	Date d8, d9, d10;
//	d8 -= 360;	//����-=����
//	d10 = d9 - 84;	//����-����
//	Date d11, d12, d13, d14, d15, d16;
//	d12 = ++d11;	//ǰ��++
//	d14 = d13++;	//����++
//	d15 = d13--;	//����--
//	d16 = --d14;	//ǰ��--
//	bool b1, b2, b3, b4, b5, b6;
//	b1 = (d11 == d12);
//	b2 = (d13 != d14);
//	b3 = (d1 > d3);
//	b4 = (d4 >= d15);
//	b5 = (d7 < d14);
//	b6 = (d9 <= d8);
//	int day1 = d5 - d4;
//	int day2 = d10 - d13;
//}
void main()
{
	test();
}