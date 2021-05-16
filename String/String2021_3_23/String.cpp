#include<iostream>
#include<string.h>
#include<string>
#include<assert.h>
using namespace std;

//string��ģ��ʵ��
//�ִ�д��
class String{
public:
	//String������-----�ַ�ָ��
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
		//���һ��Ԫ�ص���һ��λ��
		return _data + _size;
	}

	const_iterator end() const
	{
		//���һ��Ԫ�ص���һ��λ��
		return _data + _size;
	}

	//ȱʡ����
	//dataΪʲô����Ŀռ���_size��1������Ϊ�˴洢'\0'
	String(const char* str = "")
		:_size(strlen(str))
		,_capacity(_size)
		,_data(new char[_size+1])
	{
		strcpy(_data,str);
	}

	//��������
	//���õ�˼���Ǵ���ĸ���
	//����Ҫ�ֶ����ٺ��ͷſռ䣬���Զ�������ʱ����tmp�Ĺ��캯����������������ɿռ��������ͷ�
	//_dataҪ��ʼ��Ϊ�գ�����ʼ����ָ������Ŀռ䣬��ô�ͷ���ʱ����tmpʱ�ᱨ��
	String(const String& str)
		:_size(0)
		,_capacity(0)
		,_data(nullptr)
	{
		//���ù��캯������һ����ʱ������ɿռ����������ݵĿ���
		String tmp(str._data);
		//������ʱ����͵�ǰҪ��ֵ��ȥ�Ķ�������г�Ա������ֵ
		Swap(tmp);
	}
	
	//����
	//��һ��������thisָ��ָ�������
	void Swap(String& str)
	{
		swap(_size, str._size);
		swap(_capacity, str._capacity);
		swap(_data,str._data);
	}
	//��ֵ���������
	//����Ҫ�ֶ����ٺ��ͷſռ䣬���Զ�������ʱ����tmp�Ĺ��캯����������������ɿռ��������ͷ�
	String& operator=(const String& str)
	{
		//���ù��캯������һ����ʱ������ɿռ����������ݵĿ���
		String tmp(str._data);
		//������ʱ����͵�ǰҪ��ֵ��ȥ�Ķ�������г�Ա������ֵ
		Swap(tmp);
		//���ص�ǰthisָ����ָ�Ķ���
		return *this;
	}
	//��������
	~String()
	{
		if (_data)
		{
			delete[] _data;
			_data = nullptr;
		}
	}
	
	//����_dataָ�룬ͨ�������Ա��������ӷ��ʴ�ŵ�����
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

	//�±����
	//���޸�����
	char& operator[](int pos)
	{
		//������Ա�֤�������ȷ��
		assert(pos < _size);
		return _data[pos];
	}
	//�����޸�����
	char& operator[](int pos) const
	{
		//������Ա�֤�������ȷ��
		assert(pos < _size);
		return _data[pos];
	}

	//β��һ���ַ�
	void pushBack(const char& ch)
	{
		//�������
		if (_size == _capacity)
		{
			//��ֹ��Ϊ֮ǰ��_capacityΪ0��������_capacityҲ��0���޷��ﵽ���ݵ�����
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}
		//�����ַ�
		_data[_size] = ch;
		//����
		++_size;

		_data[_size] = '\0';
	}

	//����
	void reserve(size_t  n)
	{
		//ֻ��������
		if (n <= _capacity)
			return;

		//���ռ�,�࿪һ���ռ���Ϊ�˴���ַ���������־
		char* tmp = new char[n + 1];

		//����
		memcpy(tmp, _data, sizeof(char)*(strlen(_data)+1));

		//�ͷ�ԭ�еĿռ�
		delete _data;

		//���³�Ա
		_data = tmp;
		_capacity = n;
	}
	
	void resize(int n, const char& ch = '\0')
	{
		//Ҫ���õ���ЧԪ�صĸ�������������������
		if (n > _capacity)
		{
			reserve(n);
		}

		//Ҫ���õ���ЧԪ�صĸ�������_size,������Ĳ�����ָ�����ַ�ch�������
		if (n > _size)
		{
			////����±��_size��n-1��
			//for (size_t i = _size; i < n; ++i)
			//	_data[i] = ch;
			memset(_data + _size, ch, sizeof(char)*( n - _size));	//Ч�ʸ���
		}

		_size = n;
		_data[_size] = '\0';
	}


	//׷��
	void append(const char* str)
	{
		int len = strlen(str);
		//�������
		if (_size + len > _capacity)
			reserve(_size + len);
		//����
		memcpy(_data + _size, str, sizeof(char) * len);
		
		//����
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
		////�������λ��ʱ���һ����ЧԪ�ؼ�������λ�ã�Ԫ�ص�Ų���ͻ��������
		////ֱ�ӵ���β��ӿڣ�Ȼ���˳�
		//if (pos >= _size)
		//{
		//	pushBack(ch);
		//	return;
		//}
		
		//������λ�õ���Ч��
		assert(pos <= _size);

		//�������
		if (_size == _capacity)
		{
			int newC = _capacity == 0 ? 15 : 2 * _capacity;
			reserve(newC);
		}


		//�Ӻ���ǰŲ��Ԫ��,����Ų������\0
		//�±�Ϊ_size������\0
		for (size_t i = _size + 1; i > pos; --i)
		{
			_data[i] = _data[i - 1];
		}

		//����
		_data[pos] = ch;

		//����
		_size++;
	}

	void insert(size_t pos, const char* ptr)
	{
		//������λ�õ���Ч��
		assert(pos <= _size);

		int len = strlen(ptr);
		//�������
		if (_size +len >  _capacity)
		{
			reserve(_size + len);
		}

		//�Ӻ���ǰŲ��Ԫ�أ���һ��Ų������\0
		int end = _size + len;
		while (end > pos + len - 1)
		{
			_data[end] = _data[end - len];
			end--;
		}

		//����
		memcpy(_data + pos, ptr, sizeof(char)*len);

		//����
		_size += len;
	}

	void insert(size_t pos, const String& str)
	{
		//������λ�õ���Ч��
		assert(pos <= _size);

		int len = strlen(str._data);
		//�������
		if (_size + len >  _capacity)
		{
			reserve(_size + len);
		}

		//�Ӻ���ǰŲ��Ԫ�أ���һ��Ų������\0
		int end = _size + len;
		while (end > pos + len - 1)
		{
			_data[end] = _data[end - len];
			end--;
		}

		//����
		memcpy(_data + pos, str._data, sizeof(char)*len);

		//����
		_size += len;
	}

	
	void erase(size_t pos = 0, size_t len =npos)
	{
		//���ɾ��λ�õ���Ч��
		assert(pos < _size);

		if (len == npos)
		{
			_size = pos;
			_data[_size] = '\0';
		}
		else
		{
			//��pos��ʼ��ɾ��len��Ԫ��
			//���ǽ�Ԫ�شӺ���ǰ�ƶ�������ĩβ��\0
			size_t start = pos + len;
			while (start <= _size)
			{
				_data[start - len] = _data[start];
				start++;
			}
			//����
			_size -= len;
		}
	}

	//���ַ�ch��һ�γ��ֵ�λ��
	size_t find(const char& ch, size_t pos = 0)
	{
		//������λ�õ���Ч��
		assert(pos < _size);

		//���±�Ϊpos������β����ʼ����ch
		for (size_t i = pos; i < _size; ++i)
		{
			if (_data[i] == ch)
				return i;
		}

		//û�ҵ�
		//λ��Խ��:pos >= _size,Խ��Ͳ��ᾭ�������ѭ��
		return npos;
	}

	size_t find(const char* ptr, size_t pos = 0)
	{
		//���ɾ��λ�õ���Ч��
		assert(pos < _size);

		//����ptr����ַ�����_data�е�һ�γ��ֵ�λ�ã��Ҳ������ؿ�
		char* res = strstr(_data, ptr);

		if (res)
		{
			return  res - _data;
		}
		
		return npos;
	}

	size_t find(const String& str, size_t pos = 0)
	{
		//���ɾ��λ�õ���Ч��
		assert(pos < _size);

		//����str._data����ַ�����_data�е�һ�γ��ֵ�λ�ã��Ҳ������ؿ�
		char* res = strstr(_data, str._data);

		if (res)
		{
			return  res - _data;
		}

		return npos;
	}

	String substr(size_t pos = 0, size_t len = npos) const
	{
		//��ȡ��λ�ò��ܳ�����Ч��Χ
		assert(pos < _size);
		
		//��pos������������Ԫ����Ϊ�Ӵ�
		if (len ==npos || pos + len >= _size)
		{
			//����һ����������
			return String(_data + pos);
		}
		else
		{
			char* tmp = new char[len+1];

			memcpy(tmp, _data + pos, sizeof(char)*len);
			tmp[len] = '\0';

			//��return���ͷŵ�˳�����һ�£���������������
			//����ǲ��ܣ���Ϊ�㻹û����tmp�е����ݴ���һ����������
			//�����ͷ���tmp�Ŀռ䣬�����޷�����һ����Ч����������
			//Ӧ���ȴ��������������ͷ�����Ķ��ϵ�tmp�ռ�


			//����һ����������
			return String(tmp);

			//�ͷ���ʱ�ռ�
			delete[] tmp;
		}
	}

	////�����Ա������ʹ�����ƱȽ϶࣬���Ժ���ʹ�ã����ʹ�÷ǳ�Ա����
	//ostream& operator<<(ostream& out)
	//{
	//	//���ǰ���C�����ַ�����ʽ���
	//	for (const auto& ch : *this)
	//	{
	//		out << ch;
	//	}
	//	return out;
	//}

private:
	//_size:��ЧԪ�ظ���
	size_t _size;
	//_capacity:���Ĵ���ַ��ĸ���
	size_t _capacity;
	//_data������
	char* _data;
	//size_t������ֵ���ڳ�Ա�����лᾭ��ʹ��
	static const size_t npos;	
};
//static��Ա���������������npos���������ֵ
const size_t String::npos = -1;

//����Զ���String���Ա
ostream& operator<<(ostream& out, const String& str)
{
	for (const auto& ch : str)
		out << ch;
	return out;
}

//����Ԫ�ط����أ������Զ���String���Ա
istream& operator>>(istream& in,String& str)
{
	char ch;
	////cin��ȡ�����һֱ����ѭ�����޷��ﵽ�����ո�ͻ��н�����Ŀ��
	//while(cin>>ch)
	//{
	//	//����ո�ͻ��н�����������
	//	//���ǻὫ�ո�ͻ���֮�����Ϊ��һ����������ݼ�������
	//	if (ch == ' ' || ch == '\n')
	//		break;
	//	//β��
	//	str += ch;
	//}

	//�����ѭ��Ҳ����ʹ��C��getchar����ʵ��
	//while ((ch = getchar()) != EOF)

	//ʹ��istream��get�ӿڿ��������ȡ�ַ�����
	//û�ж�ȡ���ļ�������־�ͼ�����ȡ
	while ((ch=cin.get()) != EOF)
	{
		//����ո�ͻ��н�����������
		//���ǻὫ�ո�ͻ���֮�����Ϊ��һ����������ݼ�������
		if (ch == ' ' || ch == '\n')
			break;
		//β��
		str += ch;
	}
	return cin;
}

//�������ҳ�����һ�����⣬�ҵ�c_str��Ա����û����const����thisָ��
//������ʹ��const������÷�constָ��ʱ���ᱨ��
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



//��ӡString���������
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

//��Χfor���ײ�ͨ�����õ�����ʵ��
void PrintFor(const String& str)
{
	for (const char& e : str)
		cout << e << " ";
	cout << endl;
}

//const���͵ĵ��������ǲ����޸��������զ���ԣ�   
//��Ϊ֮ǰ��typedef������const_iterator������const char*,��֮ǰд����char*
//����Ϊconst_iterator����const char* 
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

//�ǳ�Ա����  +���������
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
	cout << "cin֧����������" << endl;
}


////����substr�еĴ�������������ͷŶ��Ͽռ��˳���ܷ����ǰ�����
//void test()
//{
//	String str("123456789");
//	String str2 = str.substr(0, 3);
//}


//void test()
//{
//	String cxp("1234");
//	cxp.resize(10);
//	cout << cxp.c_str() <<"end"<< endl;		//����C������,��C������\0�����
//	cout << cxp << "end"<<endl;				//����C++����������C++��\0Ҳ�����ֻ����ʾΪ��
//}

//void test()
//{
//	String str("123456789");
//	String str2 = "My name is cxp";
//	cout << str << str2 << endl;
//	String cxp("cxp"), bjh("bjh");
//	cout << cxp << "     " << bjh << endl;
//}

////��Ӧ���������ĳ�Ա����
//void test()
//{
//	String str = "123";
//	//cout << str.c_str() << endl;
//	//str<<(str << cout);		//����ʹ�ó�Ա�������
//	str << cout << endl;	//str<<cout����һ��������������������������endl
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
//	str.erase(3);		//012    βɾ
//	str.erase(0);		//ͷɾ
//}


////const_iteratorʹ�ò���
//void test()
//{
//	const String str("1234");
//	//PrintFor(str);
//	//PrintIterator(str);
//	String::const_iterator it = str.begin();
//	while (it != str.end())
//	{
//		cout << *it << " ";
//		//*it = 'A';   const�������޸�
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
//	str.insert(0, str2);		//ͷ��  --->abcd12345
//	str.insert(9, str3);		//β��  --->abcd12345AAAAA
//	str.insert(3, str4);		//�м�λ�ò���   --->abcEEEEd12345AAAAA
//
//}

//void test()
//{
//	String str = "0123456";
//	str.insert(4, 'A');		//--->0123A456
//	str.insert(8, 'X');		//β��		--->0123A456X
//	str.insert(0, "SSS");	//ͷ��      --->SSS0123A456X
//	str.insert(12, "66666");		//β��   -->SSS0123A456X66666
//	str.insert(3, "11:50");				//�м�λ�ò���   -->SSS11:500123A456X66666
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
//  //���Զ�����iterator
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
//		//e += i;	//const�����޸�
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

////����operaor[]
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


////stringģ��ʵ��
////��ͳд��
//class String{
//public:
//	////�յĹ��캯��
//	////����һ����СΪ1�Ŀռ䣬����ʼ��Ϊ\0
//	//String()
//	//	:_data(new char[1])
//	//{
//	//	_data = '\0';
//	//}
//
//	//��ȱʡֵ�Ĺ��캯��
//	//���ٵĿռ��С+1��Ϊ�˴��\0
//	String(const char* str = "")
//		:_data(new char[strlen(str)+1])
//	{
//		strcpy(_data, str);
//	}
//
//	////ǳ����:ͬһ��ռ�����ݻᱻ�ͷ�����
//	//String(const String& str)
//	//	:_data(str._data)
//	//{
//
//	//}
//
//	//���
//	//���ٵĿռ��С+1��Ϊ�˴��\0
//	String(const String& str)
//		:_data(new char[strlen(str._data)+1])
//	{
//		strcpy(_data, str._data);
//	}
//
//	//��ֵ���������
//	//�ֵ
//	String operator=(const String& str)
//	{
//		if (this != &str)
//		{
//			//���ͷ�Ҫ��ֵ��ȥ��ԭ�еĿռ�
//			delete[] _data;
//			//����һ���µĿռ�
//			_data = new char[strlen(str._data) + 1];
//			//��str�е����ݿ������µĿռ�
//			strcpy(_data, str._data);
//		}
//		return *this;
//	}
//
//	//��������
//	~String()
//	{
//		if (_data)
//		{
//			delete[] _data;
//			_data = nullptr;
//		}
//	}
//
//	//����һ��ָ�����ݵ�ָ��
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