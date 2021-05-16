#include<iostream>
#include<string.h>
#include<string>
#include<assert.h>
using namespace std;

//string的模拟实现
//现代写法
class String{
public:
	//String迭代器-----字符指针
	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		return _data;
	}

	const_iterator begin() const
	{
		return _data;
	}

	iterator end()
	{
		//最后一个元素的下一个位置
		return _data + _size;
	}

	const_iterator end() const
	{
		//最后一个元素的下一个位置
		return _data + _size;
	}

	//缺省构造
	//data为什么申请的空间会比_size多1？这是为了存储'\0'
	String(const char* str = "")
		:_size(strlen(str))
		,_capacity(_size)
		,_data(new char[_size+1])
	{
		strcpy(_data,str);
	}

	//拷贝构造
	//利用的思想是代码的复用
	//不需要手动开辟和释放空间，会自动调用临时对象tmp的构造函数和析构函数来完成空间的申请和释放
	//_data要初始化为空，不初始化会指向随机的空间，那么释放临时对象tmp时会报错
	String(const String& str)
		:_size(0)
		,_capacity(0)
		,_data(nullptr)
	{
		//调用构造函数创建一个临时对象，完成空间的申请和内容的拷贝
		String tmp(str._data);
		//交换临时对象和当前要赋值过去的对象的所有成员变量的值
		Swap(tmp);
	}
	
	//交换
	//第一个参数是this指针指向的内容
	void Swap(String& str)
	{
		swap(_size, str._size);
		swap(_capacity, str._capacity);
		swap(_data,str._data);
	}
	//赋值运算符重载
	//不需要手动开辟和释放空间，会自动调用临时对象tmp的构造函数和析构函数来完成空间的申请和释放
	String& operator=(const String& str)
	{
		//调用构造函数创建一个临时对象，完成空间的申请和内容的拷贝
		String tmp(str._data);
		//交换临时对象和当前要赋值过去的对象的所有成员变量的值
		Swap(tmp);
		//返回当前this指针所指的对象
		return *this;
	}
	//析构函数
	~String()
	{
		if (_data)
		{
			delete[] _data;
			_data = nullptr;
		}
	}
	
	//返回_data指针，通过这个成员函数来间接访问存放的数据
	const char* c_str() const
	{
		return _data;
	}

	size_t size() const
	{
		return _size;
	}

	size_t capacity() const
	{
		return _capacity;
	}

	//下标访问
	//能修改内容
	char& operator[](int pos)
	{
		//加入断言保证程序的正确性
		assert(pos < _size);
		return _data[pos];
	}
	//不能修改内容
	char& operator[](int pos) const
	{
		//加入断言保证程序的正确性
		assert(pos < _size);
		return _data[pos];
	}

	//尾插一个字符
	void pushBack(const char& ch)
	{
		//检查容量
		if (_size == _capacity)
		{
			//防止因为之前的_capacity为0，两倍的_capacity也是0，无法达到增容的作用
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//插入字符
		_data[_size] = ch;
		//更新
		++_size;

		_data[_size] = '\0';
	}

	//增容
	void reserve(size_t  n)
	{
		//只增加容量
		if (n <= _capacity)
			return;

		//开空间,多开一个空间是为了存放字符串结束标志
		char* tmp = new char[n + 1];

		//拷贝
		memcpy(tmp, _data, sizeof(char)*(strlen(_data)+1));

		//释放原有的空间
		delete _data;

		//更新成员
		_data = tmp;
		_capacity = n;
	}
	
	void resize(int n, const char& ch = '\0')
	{
		//要重置的有效元素的个数大于容量，就增容
		if (n > _capacity)
		{
			reserve(n);
		}

		//要重置的有效元素的个数大于_size,多出来的部分用指定的字符ch进行填充
		if (n > _size)
		{
			////填充下标从_size到n-1处
			//for (size_t i = _size; i < n; ++i)
			//	_data[i] = ch;
			memset(_data + _size, ch, sizeof(char)*( n - _size));	//效率更高
		}

		_size = n;
		_data[_size] = '\0';
	}


	//追加
	void append(const char* str)
	{
		int len = strlen(str);
		//检查容量
		if (_size + len > _capacity)
			reserve(_size + len);
		//插入
		memcpy(_data + _size, str, sizeof(char) * len);
		
		//更新
		_size += len;
		_data[_size] = '\0';
	}

	String& operator+=(const String& str)
	{
		append(str._data);
		return *this;
	}

	String& operator+=(const char* str)
	{
		append(str);
		return *this;
	}

	String& operator+=(const char ch)
	{
		pushBack(ch);
		return *this;
	}

	void insert(size_t pos, const char& ch)
	{
		////如果插入位置时最后一个有效元素及其后面的位置，元素的挪动就会产生问题
		////直接调用尾插接口，然后退出
		//if (pos >= _size)
		//{
		//	pushBack(ch);
		//	return;
		//}
		
		//检查插入位置的有效性
		assert(pos <= _size);

		//检查容量
		if (_size == _capacity)
		{
			int newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}


		//从后往前挪动元素,最先挪动的是\0
		//下标为_size处的是\0
		for (size_t i = _size + 1; i > pos; --i)
		{
			_data[i] = _data[i - 1];
		}

		//插入
		_data[pos] = ch;

		//更新
		_size++;
	}

	void insert(size_t pos, const char* ptr)
	{
		//检查插入位置的有效性
		assert(pos <= _size);

		int len = strlen(ptr);
		//检查容量
		if (_size +len >  _capacity)
		{
			reserve(_size + len);
		}

		//从后往前挪动元素，第一个挪动的是\0
		int end = _size + len;
		while (end > pos + len - 1)
		{
			_data[end] = _data[end - len];
			end--;
		}

		//插入
		memcpy(_data + pos, ptr, sizeof(char)*len);

		//更新
		_size += len;
	}

	void insert(size_t pos, const String& str)
	{
		//检查插入位置的有效性
		assert(pos <= _size);

		int len = strlen(str._data);
		//检查容量
		if (_size + len >  _capacity)
		{
			reserve(_size + len);
		}

		//从后往前挪动元素，第一个挪动的是\0
		int end = _size + len;
		while (end > pos + len - 1)
		{
			_data[end] = _data[end - len];
			end--;
		}

		//插入
		memcpy(_data + pos, str._data, sizeof(char)*len);

		//更新
		_size += len;
	}

	
	void erase(size_t pos = 0, size_t len =npos)
	{
		//检查删除位置的有效性
		assert(pos < _size);

		if (len == npos)
		{
			_size = pos;
			_data[_size] = '\0';
		}
		else
		{
			//从pos开始，删除len个元素
			//就是将元素从后往前移动，包括末尾的\0
			size_t start = pos + len;
			while (start <= _size)
			{
				_data[start - len] = _data[start];
				start++;
			}
			//更新
			_size -= len;
		}
	}

	//找字符ch第一次出现的位置
	size_t find(const char& ch, size_t pos = 0)
	{
		//检查查找位置的有效性
		assert(pos < _size);

		//从下标为pos处到结尾处开始查找ch
		for (size_t i = pos; i < _size; ++i)
		{
			if (_data[i] == ch)
				return i;
		}

		//没找到
		//位置越界:pos >= _size,越界就不会经过上面的循环
		return npos;
	}

	size_t find(const char* ptr, size_t pos = 0)
	{
		//检查删除位置的有效性
		assert(pos < _size);

		//查找ptr这个字符串在_data中第一次出现的位置，找不到返回空
		char* res = strstr(_data, ptr);

		if (res)
		{
			return  res - _data;
		}
		
		return npos;
	}

	size_t find(const String& str, size_t pos = 0)
	{
		//检查删除位置的有效性
		assert(pos < _size);

		//查找str._data这个字符串在_data中第一次出现的位置，找不到返回空
		char* res = strstr(_data, str._data);

		if (res)
		{
			return  res - _data;
		}

		return npos;
	}

	String substr(size_t pos = 0, size_t len = npos) const
	{
		//截取的位置不能超过有效范围
		assert(pos < _size);
		
		//将pos及其后面的所有元素作为子串
		if (len ==npos || pos + len >= _size)
		{
			//返回一个匿名对象
			return String(_data + pos);
		}
		else
		{
			char* tmp = new char[len+1];

			memcpy(tmp, _data + pos, sizeof(char)*len);
			tmp[len] = '\0';

			//将return和释放的顺序调整一下，还能正常运行吗？
			//结果是不能，因为你还没有用tmp中的内容创建一个匿名对象，
			//就先释放了tmp的空间，这样无法创建一个有效的匿名对象
			//应该先创建匿名对象，再释放申请的堆上的tmp空间


			//返回一个匿名对象
			return String(tmp);

			//释放临时空间
			delete[] tmp;
		}
	}

	////这个成员函数的使用限制比较多，所以很少使用，最好使用非成员函数
	//ostream& operator<<(ostream& out)
	//{
	//	//不是按照C风格的字符串形式输出
	//	for (const auto& ch : *this)
	//	{
	//		out << ch;
	//	}
	//	return out;
	//}

private:
	//_size:有效元素个数
	size_t _size;
	//_capacity:最大的存放字符的个数
	size_t _capacity;
	//_data：内容
	char* _data;
	//size_t类的最大值，在成员函数中会经常使用
	static const size_t npos;	
};
//static成员在类外进行声明，npos：正的最大值
const size_t String::npos = -1;

//输出自定义String类成员
ostream& operator<<(ostream& out, const String& str)
{
	for (const auto& ch : str)
		out << ch;
	return out;
}

//输入元素符重载：输入自定义String类成员
istream& operator>>(istream& in,String& str)
{
	char ch;
	////cin获取输入会一直继续循环，无法达到遇见空格和换行结束的目的
	//while(cin>>ch)
	//{
	//	//输入空格和换行结束本次输入
	//	//但是会将空格和换行之后的作为下一次输入的数据继续输入
	//	if (ch == ' ' || ch == '\n')
	//		break;
	//	//尾插
	//	str += ch;
	//}

	//下面的循环也可以使用C的getchar函数实现
	//while ((ch = getchar()) != EOF)

	//使用istream的get接口可以逐个获取字符输入
	//没有读取到文件结束标志就继续读取
	while ((ch=cin.get()) != EOF)
	{
		//输入空格和换行结束本次输入
		//但是会将空格和换行之后的作为下一次输入的数据继续输入
		if (ch == ' ' || ch == '\n')
			break;
		//尾插
		str += ch;
	}
	return cin;
}

//在这里我出现了一个问题，我的c_str成员函数没有用const修饰this指针
//所以在使用const对象调用非const指针时，会报错
bool operator<(const String& str1,const String& str2)
{
	int ret = strcmp(str1.c_str(), str2.c_str());
	if (ret < 0)
		return true;
	else
		return false;
}

bool operator==( String& str1,String& str2)
{
	int ret = strcmp(str1.c_str(), str2.c_str());
	if (ret == 0)
		return true;
	else
		return false;
}

bool operator!=(String& str1, String& str2)
{
	return !(str1 == str2);
}

bool operator<=(String& str1, String& str2)
{
	return str1 < str2 || str1 == str2;
}

bool operator>(String& str1, String& str2)
{
	return !(str1 <= str2);
}

bool operator>=(String& str1, String& str2)
{
	return !(str1 < str2);
}



//打印String对象的内容
void PrintString(String& str)
{
	size_t i = 0;
	while (i < str.size())
	{
		cout << str[i] << " ";
		++i;
	}
	cout << endl;
}

void PrintString(const String& str)
{
	size_t i = 0;
	while (i < str.size())
	{
		cout << str[i] << " ";
		++i;
	}
	cout << endl;
}

//范围for，底层通过调用迭代器实现
void PrintFor(const String& str)
{
	for (const char& e : str)
		cout << e << " ";
	cout << endl;
}

//const类型的迭代器不是不能修改吗？我这个咋可以？   
//因为之前用typedef声明的const_iterator本质是const char*,我之前写的是char*
//自认为const_iterator就是const char* 
void PrintIterator(const String& str)
{
	String::const_iterator it = str.begin();
	while (it != str.end())
	{
		cout << *it << " ";
		//*it = '2';
		it++;
	}

	cout << endl;
}

//非成员函数  +运算符重载
String operator+(const String& str1,const String& str2)
{
	String res = str1;
	res += str2;
	return res;
}

String operator+(const String& str1,const char* ptr)
{
	String res = str1;
	res += ptr;
	return res;
}
String operator+(const String& str1,const char ch)
{
	String res=str1;
	res += ch;
	return res;
}


void test()
{
	String str, str2, str3, str4;
	cin >> str >> str2 >> str3 >> str4;
	cout << "str:"<<str << endl;
	cout << "str2:"<<str2 << endl;
	cout << "str3:"<<str3<< endl;
	cout <<"str4:"<<str4<< endl;
	cout << "cin支持连续输入" << endl;
}


////测试substr中的创建匿名对象和释放堆上空间的顺序能否进行前后调整
//void test()
//{
//	String str("123456789");
//	String str2 = str.substr(0, 3);
//}


//void test()
//{
//	String cxp("1234");
//	cxp.resize(10);
//	cout << cxp.c_str() <<"end"<< endl;		//按照C风格输出,在C语言中\0不输出
//	cout << cxp << "end"<<endl;				//按照C++风格输出，在C++中\0也输出，只是显示为空
//}

//void test()
//{
//	String str("123456789");
//	String str2 = "My name is cxp";
//	cout << str << str2 << endl;
//	String cxp("cxp"), bjh("bjh");
//	cout << cxp << "     " << bjh << endl;
//}

////对应输出运算符的成员函数
//void test()
//{
//	String str = "123";
//	//cout << str.c_str() << endl;
//	//str<<(str << cout);		//连续使用成员函数输出
//	str << cout << endl;	//str<<cout返回一个输出流对象，这个输出流对象输出endl
//}


//void test()
//{
//	String str1("123");
//	String str2(str1);
//	String str3 = "I am so strong";
//
//	bool ret = str1 < str2;
//	ret = str1 < str3;
//
//	ret = str1 == str2;
//	ret = str1 == str3;
//
//	ret = str1 <= str2;
//	ret = str1 <= str3;
//
//	ret = str1 != str2;
//	ret = str1 != str3;
//
//	ret = str1>str2;
//	ret = str1>str3;
//
//	ret = str1>=str2;
//	ret = str1>=str3;
//}

//void test()
//{
//	String str = "abcdefghijklmnopq";
// 	String str2 = str.substr(0, 5);
//	//str2 = str.substr(100, 10);
//	str2 = str.substr(10, 10);
//	str2 = str.substr(0, 100);
//	PrintFor(str2);
//}

//void test()
//{
//	String str = "Something just like this";
//	String str2 = "this";
//	char* ptr = "just";
//	size_t pla = str.find('S');
//	pla = str.find('n', 4);
//	pla = str.find('x', 4);
//	pla = str.find(ptr, 0);
//	pla = str.find(str2, 5);
//	pla = str.find(str2, 100);
//}


//void test()
//{
//	String str = "0123456789";
//	str.erase(5, 2);	//01234789
//	str.erase(4);		//0123
//	str.erase(3);		//012    尾删
//	str.erase(0);		//头删
//}


////const_iterator使用测试
//void test()
//{
//	const String str("1234");
//	//PrintFor(str);
//	//PrintIterator(str);
//	String::const_iterator it = str.begin();
//	while (it != str.end())
//	{
//		cout << *it << " ";
//		//*it = 'A';   const对象不能修改
//		it++;
//	}
//	cout << endl;
//	PrintFor(str);
//}


//void test()
//{
//	String str("12345");
//	String str2 = "abcd";
//	String str3 = "AAAAA";
//	String str4 = "EEEE";
//	str.insert(0, str2);		//头插  --->abcd12345
//	str.insert(9, str3);		//尾插  --->abcd12345AAAAA
//	str.insert(3, str4);		//中间位置插入   --->abcEEEEd12345AAAAA
//
//}

//void test()
//{
//	String str = "0123456";
//	str.insert(4, 'A');		//--->0123A456
//	str.insert(8, 'X');		//尾插		--->0123A456X
//	str.insert(0, "SSS");	//头插      --->SSS0123A456X
//	str.insert(12, "66666");		//尾插   -->SSS0123A456X66666
//	str.insert(3, "11:50");				//中间位置插入   -->SSS11:500123A456X66666
//}

//void test()
//{
//	String str = "1234";
//	String str2 = "abcd";
//	char ch = 'Q';
//	char* ptr = "implicit";
//	String str3 = str + ch;
//	String str4 = str + ptr;
//	String str5 = str + str2;
//}

//void test()
//{
//	String str("1234");
//	String str2 = "fhehreu";
//	char ch = 'A';
//	char* ptr = "I am strong!";
//	str += ch;		//1234A
//	str += ptr;		//1234AI am strong!
//	str += str2;	//1234AI am strong!fhehreu
//}

//void test()
//{
//	String str = "012345";
//	PrintString(str);
//	str.append("AAAAA");
//	PrintString(str);
//	str.append("BCDEF");
//	PrintString(str);
//}

//void test()
//{
//	String str("1234");
//	PrintFor(str);
//	str.pushBack('A');
//	PrintFor(str);
//}

//void test()
//{
//	String str("12345");
//	str.resize(1,'A');
//	str.resize(4,'B');
//	str.resize(10,'C');
//}

//void test()
//{
//	String str("0123456");
//	const String str2("abcdefghijk");
//	int i = 0;
//  //会自动调用iterator
//	for (auto& e : str)
//	{
//		cout << e << " ";
//		e += i;
//		i++;
//	}
//		
//	cout << endl;
//
//	i = 0;
//	for (const auto& e : str2)
//	{
//		cout << e << " ";
//		//e += i;	//const不可修改
//		//i++;
//	}
//}

//void test()
//{
//	String str = "I am so handsome!";
//	str[0] = 'A';
//	PrintString(str);
//	const String str2 = "Study hard,day day up!";
//	str2[0] = 'K';
//	PrintString(str2);
//}

//void test()
//{
//	String str = "QWERRRR";
//	const String str2 = "jiejrgiejgie";
//	PrintString(str);
//	PrintString(str2);
//
//}

////测试operaor[]
//void test()
//{
//	String str = "12345678";
//	size_t i = 0;
//	while (i < str.size())
//	{
//		cout << str[i] << " ";
//		++i;
//	}
//	cout << endl;
//
//	String str2 = "ABCDEFGHIJK";
//	i = 0;
//	while (i < str2.size())
//	{
//		cout << str2[i] <<" ";
//		++i;
//	}
//	cout << endl;
//}

//void test()
//{
//	String str = "So?";
//	String str2("2021/3/23");
//	String str3(str);
//	String str4 = str2;
//	cout << "str:"<<str.c_str(str) << endl;
//	cout << "str size:" << str.size() << endl;
//	cout << "str2:"<<str.c_str(str2) << endl;
//	cout << "str2 size:" << str2.size() << endl;
//	cout <<"str3:"<< str.c_str(str3) << endl;
//	cout << "str4:"<<str.c_str(str4) << endl;
//}


////string模拟实现
////传统写法
//class String{
//public:
//	////空的构造函数
//	////开辟一个大小为1的空间，并初始化为\0
//	//String()
//	//	:_data(new char[1])
//	//{
//	//	_data = '\0';
//	//}
//
//	//有缺省值的构造函数
//	//开辟的空间大小+1是为了存放\0
//	String(const char* str = "")
//		:_data(new char[strlen(str)+1])
//	{
//		strcpy(_data, str);
//	}
//
//	////浅拷贝:同一块空间的内容会被释放两次
//	//String(const String& str)
//	//	:_data(str._data)
//	//{
//
//	//}
//
//	//深拷贝
//	//开辟的空间大小+1是为了存放\0
//	String(const String& str)
//		:_data(new char[strlen(str._data)+1])
//	{
//		strcpy(_data, str._data);
//	}
//
//	//赋值运算符重载
//	//深赋值
//	String operator=(const String& str)
//	{
//		if (this != &str)
//		{
//			//先释放要赋值过去的原有的空间
//			delete[] _data;
//			//开辟一块新的空间
//			_data = new char[strlen(str._data) + 1];
//			//将str中的内容拷贝到新的空间
//			strcpy(_data, str._data);
//		}
//		return *this;
//	}
//
//	//析构函数
//	~String()
//	{
//		if (_data)
//		{
//			delete[] _data;
//			_data = nullptr;
//		}
//	}
//
//	//返回一个指向数据的指针
//	const char* c_str()const
//	{
//		return _data;
//	}
//private:
//	char* _data;
//};



//void test()
//{
//	String str = "I am lack of faculty!";
//	String str2("life is a struggle!");
//	String str3="Try";
//	String str4(str);
//	str3 = str2;
//	cout << str.c_str() << endl;
//	cout << str2.c_str() << endl;
//	cout << str3.c_str() << endl;
//	cout << str4.c_str() << endl;
//}


//void test()
//{
//	string str("1001");
//	char* ptr = "IIIIIII";
//	String str2;
//	String str3("12345555");
//	cout << str << endl;
//	cout << str.c_str() << endl;
//	cout << ptr << endl;
//	cout << str2.c_str() << endl;
//	cout << str3.c_str() << endl;
//}

int main()
{
	test();
	return 0;
}