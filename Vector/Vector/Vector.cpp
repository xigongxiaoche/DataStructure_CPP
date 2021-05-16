#include<iostream>
#include<string>
#include<string.h>

using namespace std;

template<class T>
class Vector{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	//�޲ι��캯��
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{}
	
	//�����ж��ֵ�Ĺ��캯��
	Vector(size_t n,const T& val=T())
		:_start(new T[n])
		, _finish(_start+n)
		,_endofStorage(_start+n)
	{
		for (size_t i = 0; i < n; ++i)
		{
			_start[i] = val;
		}
	}

	//�����������inputIterator��Ϊһ����ͨ�����ͣ�����*�����
	//�õ����������������캯��
	template<class inputIterator>
	Vector(inputIterator first,inputIterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{
		//[first,last)
		while (first != last)
		{
			//��ʾ��һ�δ��������⣬�Ƿ��ļ��Ѱַ
			//����firstΪָ���������������
			pushBack(*first);	
			first++;
		}
	}

	//[]�������������
	//thisָ������const,����ԭ��û���������������������
	const T& operator[](size_t pos) const
	{
		//���λ�õ���Ч��
		if (pos >= 0 && pos < size())
		{
			return _start[pos];
		}
	}

	//�������캯��
	Vector(const Vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{
		int n = v.capacity();
		//���ٿռ�
		_start = new T[n];
		//�����Դ�Ŀ���
		for (size_t i = 0; i < v.size(); ++i)
		{ 
			_start[i] = v[i];
		}
		//���³�Ա
		_finish = _start + v.size();
		_endofStorage = _start + n;
	}

	////��ֵ���������
	//Vector<T>& operator=(const Vector<T>& v)
	//{
	//	if (this != &v)
	//	{
	//		//�ͷ�ԭ���Ŀռ�
	//		delete[] _start;
	//		int n = v.capacity();
	//		//���ٿռ�
	//		_start = new T[n];
	//		//�����Դ�Ŀ���
	//		for (size_t i = 0; i < v.size(); ++i)
	//		{
	//			_start[i] = v[i];
	//		}
	//		//���³�Ա
	//		_finish = _start + v.size();
	//		_endofStorage = _start + n;
	//	}
	//	return *this;
	//}

	//�������������ֵ
	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endofStorage, v._endofStorage);
	}

	//��ֵ����������ִ�д��
	//����ô������Ķ���v���п������죬
	//����һ����ʱ���������������ʱ�����ͱ���ֵ���������
	Vector<T>& operator=(Vector<T> v)
	{
		Swap(v);
		return *this;
	}

	//��������
	~Vector()
	{
		if (_start)
		{
 			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endofStorage = nullptr;
		}
	}

	//β��
	void pushBack(const T& val)
	{
		//�������
		if (_finish == _endofStorage)
		{
			//�����¿ռ�
			size_t newC = _endofStorage == nullptr ? 1 : 2 * capacity();
			//����
			reserve(newC);
		}
		//����Ԫ��
		*_finish = val;
		//����
		++_finish;
	}

	//βɾ
	void popBack()
	{
		erase(end() - 1);
	}

	//����,ֻ��������
	void reserve(size_t n)
	{
		if (n > capacity())
		{
			//����ԭʼ��size
			size_t sz = size();

			//�����¿ռ�
			T* arr = new T[n];

			if (_start)
			{
				////�Զ������ͣ�ǳ����
				////�������Դ���������Դ������ͷ�
				////��������Դ�ͷţ��һ��ǲ�������е�ϸ�ڣ�����������������
				//memcpy(arr, _start, sizeof(T) * sz);

				//���ԭ�пռ������
				//������Զ������ͣ�����ø�ֵ��������غ���
				//ֻҪ��ֵ�����ʵ����������˴��������
				for (size_t i = 0; i < sz ; ++i)
				{
					arr[i] = _start[i];
				}

				//�ͷ�ԭ�еĿռ�
 				delete[] _start;
			}
			
			//����
			_start = arr;
			_finish = _start + sz;
			_endofStorage = _start + n;
		}
	}

	//�ı���ЧԪ��
	void resize(size_t n, const T& val = T())
	{
		//n>capacity  ����
		if (n > capacity())
		{
			reserve(n);
		}

		//size<n<capacity   ���
		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish = val;
				_finish++;
			}
		}
		
		//n<size    �ı�_finishλ��
		_finish = _start + n;
	}

	//����������Ϊ��������ʧЧ����Ԫ�ص��ƶ���ͣ����
	//ÿ�ν��� ���� �� ɾ�� ʱҪ���ǵ�����ʧЧ������
	//����
	void insert(iterator pos, const T& val)
	{
		//���λ���Ƿ���Ч
		if (pos >= begin() && pos <= end())
		{
			//�������
			if (_finish == _endofStorage)
			{
				//���ݻᵼ�µ�����ʧЧ
				//����Ԫ�صĸ���
				size_t num = pos - _start;
				size_t newC = _endofStorage == nullptr ? 1 : 2 * capacity();
				reserve(newC);
				//���µ�����
				pos =_start + num;
			}
			//�ƶ�Ԫ��
			iterator it = _finish;
			while (it != pos)
			{
				*it = *(it - 1);
				it--;
			}
			//����Ԫ��
			*pos = val;
			//����
			++_finish;
		}
	}

	//ɾ��
	iterator erase(iterator pos)
	{
		//���ɾ��λ�õ���Ч��
		if (pos >= _start && pos < _finish)
		{
			iterator it = pos+1;
			while (it != _finish)
			{
				*(it -1) = *it;
				it++;
			}

			//����_finish
			--_finish;

			//����ɾ��λ�õ���һ��λ��
			return pos;
		}
	}

	//������
	iterator begin() 
	{
		return _start;
	}

	const_iterator begin() const
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator end() const
	{
		return _finish;
	}

	//��ЧԪ�ظ���
	size_t size() const
	{
		return _finish - _start;
	}

	//����
	size_t capacity() const
	{
		return _endofStorage - _start;
	}

private:
	T* _start;		//�ռ����ʼλ��
	T* _finish;		//���һ����ЧԪ�ص�ĩβ
	T* _endofStorage;		//�ռ��ĩβ
};

//�Զ������ͳ�Ա��������߱���ֵ��������أ�����ʹ��������������
template<class T>
ostream& operator<<(ostream& out,Vector<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		out << v[i] << " ";
	}
	out << endl;
	return out;
}

template<class T>
//��������ʽ��ӡVector��Ԫ�ص�ֵ
void printVector(const Vector<T>& v)
{
	Vector<T>::const_iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

template<class T>
//��Χfor��ӡVector��Ԫ�ص�ֵ
void printForVector(const Vector<T>& v)
{
	for (const auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test()
{
	Vector<int> v;
	v.pushBack(1);
	v.pushBack(2);
	v.pushBack(3);
	v.pushBack(4);
	v.pushBack(5);
	cout << v[1] << endl;
	
}

//
//void test()
//{
//	Vector<string> v;
//	string str = "I am ";
//	string str2 = "so lack ";
//	string str3 = "of faculty!";
//	v.pushBack(str);
//	v.pushBack(str2);
//	v.pushBack(str3);
//	cout << v;
//
//	Vector<int> v2;
//	v2.pushBack(2);
//	v2.pushBack(4);
//	v2.pushBack(8);
//	v2.pushBack(16);
//	v2.pushBack(32);
//	cout << v2;
//
//}


////���Կ������캯���͸�ֵ��������غ���
//void test()
//{
//	Vector<int> v;
//	v.pushBack(0);
//	v.pushBack(1);
//	v.pushBack(2);
//	v.pushBack(3);
//	v.pushBack(4);
//	printVector(v);
//	cout << "v  size:" << v.size() << endl;
//	cout << "v  capacity:" << v.capacity() << endl;
//
//	Vector<int> v2(v);
//	printVector(v2);
//	cout << "v2  size:" << v2.size() << endl;
//	cout << "v2  capacity:" << v2.capacity() << endl;
//	
//	Vector<int> v3;
//	v3.insert(v3.begin(), 2);
//	v3.pushBack(4);
//	v3.pushBack(8);
//	v3.pushBack(16);
//	v3.pushBack(32);
//	v3.pushBack(64);
//	printVector(v3);
//
//	v3 = v2;
//	printVector(v3);
//
//}

//void test()
//{
//	Vector<int> v;
//	v.pushBack(1);
//	v.pushBack(2);
//	v.pushBack(3);
//	v.pushBack(4);
//	v.pushBack(5);
//	printVector(v);
//
//	//Vector<int>::iterator it=v.erase(v.begin());
//	////v.erase(v.end()-1);
//	//cout << *it << endl;
//	//printVector(v);
//	v.popBack();
//	v.popBack();
//	printVector(v);
//}

//void test()
//{
//	Vector<int> v;
//	v.insert(v.begin(), 0);
//	v.insert(v.begin(), -1);
//	v.insert(v.begin(), -2);
//	v.insert(v.end(), 1);
//	v.insert(v.end(), 2);
//	v.insert(v.end(), 3);
//	printVector(v);
//
//	v.insert(v.end(), 1024);
//	printVector(v);
//}

//void test()
//{
//	Vector<int> v;
//	v.pushBack(1);
//	v.pushBack(2);
//	v.pushBack(3);
//	v.pushBack(4);
//	v.pushBack(5);
//	printVector(v);
//	cout << "capacity:" << v.capacity() << endl;
//
//	//size<n<capacity
//	v.resize(6, 4);
//	printVector(v);
//	cout << "capacity:" << v.capacity() << endl;
//
//	//n<size
//	v.resize(3);
//	printVector(v);
//	cout << "capacity:" << v.capacity() << endl;
//
//	//n>capacity
//	v.resize(10,1);
//	printVector(v);
//	cout << "capacity:" << v.capacity() << endl;
//}

////explicit������ֻ��һ�������Ĺ��캯��������������캯����Ҫ������ʾת��
////explicit�ؼ��ֵ����þ��Ƿ�ֹ�๹�캯������ʽ�Զ�ת��.
//struct A{
//	explicit A(int a=32)
//		:_a(a)
//	{
//		cout << " A(int) " << endl;
//	}
//	int _a = 512;
//};
//
//ostream& operator<<(ostream& out, A a)
//{
//	out << a._a << endl;
//	return out;
//}
//void test()
//{
//	//�Զ������͵�β�壬���ȵ��ù��캯������һ������
//	//Ȼ���ٸ��ݿռ��С�����Ƿ���Ҫ���ݣ������ݵ�ͬʱ����ù��캯��
//
//	Vector<A> v;
//	v.pushBack(A(-1));
//	cout << endl;
//	v.pushBack(A(0));
//	cout << endl;
//	v.pushBack(A(1));
//	cout << endl;
//	v.pushBack(A(2));
//	cout << endl;
//	v.pushBack(A(3));
//	cout << endl;
//	v.pushBack(A(4));
//	cout << endl;
//	printVector(v);
//}

////���õ���������һ��vector
//void test()
//{
//	Vector<int> v(5, 4);
//	Vector<int>::iterator it = v.begin();
//	printVector(v);
//	Vector<int> v2(v.begin(), v.end());
//	v.reserve(10);
//	printForVector(v2);
//	cout << v.capacity() << endl;
//}

////���õ�����ָ����Χ���г�ʼ��
//void test()
//{
//	Vector<int> v((size_t)5, 32);
//	printForVector(v);
//	Vector<int> v2(v.begin(), v.end());
//	printForVector(v2);
//}

////�ǳ�Ա��������ӡVector��Ա
//void test()
//{
//	Vector<int> v(6, 2);
//	printForVector(v);
//	printVector(v);
//}

////��������ֻ������������
//void test()
//{
//	//������
//	Vector<int> v(6, 5);
//	Vector<int>::iterator it = v.begin();
//	while (it != v.end())
//	{
//		cout << *it << " ";
//		*it = 1024;
//		it++;
//	}
//	cout << endl;
//	it = v.begin();
//	while (it != v.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//
//	//read only iterator
//	Vector<char> v2(8, 'a');
//	Vector<char>::const_iterator it2 = v2.begin();
//	while (it2 != v2.end())
//	{
//		cout << *it2 << " ";
//		//*it2 = 'A';		//��ͼ�޸�����ʱ����
//		it2++;
//	}
//	cout << endl;
//}

////���캯���Ĳ��ԣ�Vector(size_t n,const T& val=T())
//void test()
//{
//	Vector<int> v1(10,5);
//	Vector<int>::iterator it = v1.begin();
//	while (it != v1.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//	cout << endl;
//
//	int a = 1024;
//	Vector<int*> v2(3,&a);
//	Vector<int*>::iterator it2 = v2.begin();
//	while (it2 != v2.end())
//	{
//		cout << **it2 << " ";
//		it2++;
//	}
//	cout << endl;
//
//	Vector<A> v3(5);
//	cout << v3.size() << endl;
//
//	Vector<A>::iterator it3 = v3.begin();
//	while (it3 != v3.end())
//	{
//		cout << *it3 ;
//		it3++;
//	}
//
//
//}

//struct A{
//private:
//	int _a;
//};
////�޲ι��캯������
//void test()
//{
//	Vector<int> i;
//	Vector<char> c;
//	Vector<A> a;
//	Vector<A*> ptrA;
//
//	cout << i.size() << endl;
//	cout << c.size() << endl;
//	cout << a.size() << endl;
//	cout << ptrA.size() << endl;
//	cout << i.capacity() << endl;
//	cout << c.capacity() << endl;
//	cout << a.capacity() << endl;
//	cout << ptrA.capacity() << endl;
//}

int main()
{
	test();
	return 0;
}