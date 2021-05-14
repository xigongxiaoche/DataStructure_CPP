#include<stdio.h>
#include<iostream>
using namespace std;
class Date
{
public:
	//全缺省默认构造
	Date(int y = 2021, int m = 5, int d = 1)
	{
		if (y <= 0 || m <= 0 || m > 12 || d <= 0 || d > getDay(y, m))
		{
			//日期无效
			_y = 2021;
			_m = 5;
			_d = 1;
			cout << "日期无效，设为默认值:2021.5.1 " << endl;
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
	//拷贝构造函数
	Date(const Date& d)
	{
		_y = d._y;
		_m = d._m;
		_d = d._d;
	}
	~Date()
	{
		//没有资源就不调用析构函数，析构函数啥也不用做
	}
	//日期运算：Date+=int
	Date& operator+=(int day)
	{
		//判断日期是否为负数
		if (day < 0)
			return *this -= -day;

		//相加天数
		_d += day;
		//判断天数是否溢出
		while(_d > getDay(_y, _m))
		{
			//减去当月的天数
			_d -= getDay(_y, _m);

			//月份进位
			++_m;
			
			//判断月份是否溢出
			if (_m == 13)
			{
				//年份进位，进为下一年的一月份
				++_y;
				_m = 1;
			}
		}
		//返回相加之后的结果
		return *this;
	}
	
	//日期运算：Date + int 
	//返回相加之后的结果，操作数不能改变
	Date& operator+(int day)
	{
		//拷贝一份数据进行运算
		static Date copy_data(*this);

		//复用+=的接口
		copy_data+= day;

		//返回相加之后的结果
		return copy_data;
	}

	//前置++
	Date& operator++()
	{
		////方法1如下 -------但没有第二种简洁
		////天数加1
		//_d += 1;

		////判断天数是否越界
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
		//第二种，调用+=接口
		return *this += 1;
	}
	
	//后置++，相比前置++多了一个int型参数，只是为了和前置++有所区别
	Date operator++(int)
	{
		Date copy(*this);
		*this += 1;
		//返回++之前的值
		return copy;
	}
	//-=
	Date operator-=(int day)
	{
		//判断日期是否为负数
		if (day < 0)
			return *this += -day;

		_d -= day;
		//判断天数是否合理
		while(_d <= 0)
		{
			--_m;
			//判断月份是否向下溢出
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
	//前置--
	Date operator--()
	{
		return *this-=-1;
	}
	//后置--
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
	//日期相减：date1-date2
	int operator-(const Date& d)
	{
		//计算比较小的日期经过多少次自加的运算，可以和比较大的日期相同
		//自加的次数就是相差的天数
		Date max = *this;
		Date min = d;
		int flag = 1;//flag=1表示日期相减为正数

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
//	Date d1;	//生成默认的日期
//	Date d2(2021, 2, 7);
//	Date d3(d2);	//调用拷贝构造函数
//	Date d4(2000, 1, 2);
//	d1 = d4;	//调用赋值运算符
//	Date d5, d6, d7;
//	d5 += 99;	//日期+=天数
//	d7 = d6 + 13;	//日期+天数
//	Date d8, d9, d10;
//	d8 -= 360;	//日期-=天数
//	d10 = d9 - 84;	//日期-天数
//	Date d11, d12, d13, d14, d15, d16;
//	d12 = ++d11;	//前置++
//	d14 = d13++;	//后置++
//	d15 = d13--;	//后置--
//	d16 = --d14;	//前置--
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