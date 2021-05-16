#include<iostream>
#include<string>
#include<string.h>

using namespace std;

template<class T>
class Vector{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	//无参构造函数
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{}
	
	//声明有多个值的构造函数
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

	//编译器将这个inputIterator视为一个普通的类型，加上*后好了
	//用迭代器区间声明构造函数
	template<class inputIterator>
	Vector(inputIterator first,inputIterator last)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{
		//[first,last)
		while (first != last)
		{
			//显示这一段代码有问题，非法的间接寻址
			//定义first为指针变量后，问题解决了
			pushBack(*first);	
			first++;
		}
	}

	//[]括号运算符重载
	//this指针必须加const,具体原因还没搞清楚！！！！！！！！
	const T& operator[](size_t pos) const
	{
		//检查位置的有效性
		if (pos >= 0 && pos < size())
		{
			return _start[pos];
		}
	}

	//拷贝构造函数
	Vector(const Vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofStorage(nullptr)
	{
		int n = v.capacity();
		//开辟空间
		_start = new T[n];
		//完成资源的拷贝
		for (size_t i = 0; i < v.size(); ++i)
		{ 
			_start[i] = v[i];
		}
		//更新成员
		_finish = _start + v.size();
		_endofStorage = _start + n;
	}

	////赋值运算符重载
	//Vector<T>& operator=(const Vector<T>& v)
	//{
	//	if (this != &v)
	//	{
	//		//释放原来的空间
	//		delete[] _start;
	//		int n = v.capacity();
	//		//开辟空间
	//		_start = new T[n];
	//		//完成资源的拷贝
	//		for (size_t i = 0; i < v.size(); ++i)
	//		{
	//			_start[i] = v[i];
	//		}
	//		//更新成员
	//		_finish = _start + v.size();
	//		_endofStorage = _start + n;
	//	}
	//	return *this;
	//}

	//交换两个对象的值
	void Swap(Vector<T>& v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endofStorage, v._endofStorage);
	}

	//赋值运算符重载现代写法
	//会调用传进来的对象v进行拷贝构造，
	//生成一个临时变量，交换这个临时变量和被赋值对象的内容
	Vector<T>& operator=(Vector<T> v)
	{
		Swap(v);
		return *this;
	}

	//析构函数
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

	//尾插
	void pushBack(const T& val)
	{
		//检查容量
		if (_finish == _endofStorage)
		{
			//开辟新空间
			size_t newC = _endofStorage == nullptr ? 1 : 2 * capacity();
			//增容
			reserve(newC);
		}
		//插入元素
		*_finish = val;
		//更新
		++_finish;
	}

	//尾删
	void popBack()
	{
		erase(end() - 1);
	}

	//增容,只增加容量
	void reserve(size_t n)
	{
		if (n > capacity())
		{
			//保存原始的size
			size_t sz = size();

			//开辟新空间
			T* arr = new T[n];

			if (_start)
			{
				////自定义类型，浅拷贝
				////如果有资源，会产生资源被多次释放
				////这个多次资源释放，我还是不理解其中的细节！！！！！！！！！
				//memcpy(arr, _start, sizeof(T) * sz);

				//深拷贝原有空间的内容
				//如果是自定义类型，会调用赋值运算符重载函数
				//只要赋值运算符实现了深拷贝，此处就是深拷贝
				for (size_t i = 0; i < sz ; ++i)
				{
					arr[i] = _start[i];
				}

				//释放原有的空间
 				delete[] _start;
			}
			
			//更新
			_start = arr;
			_finish = _start + sz;
			_endofStorage = _start + n;
		}
	}

	//改变有效元素
	void resize(size_t n, const T& val = T())
	{
		//n>capacity  增容
		if (n > capacity())
		{
			reserve(n);
		}

		//size<n<capacity   填充
		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish = val;
				_finish++;
			}
		}
		
		//n<size    改变_finish位置
		_finish = _start + n;
	}

	//在这里我因为迭代器的失效而让元素的移动不停进行
	//每次进行 增容 和 删除 时要考虑迭代器失效的问题
	//插入
	void insert(iterator pos, const T& val)
	{
		//检查位置是否有效
		if (pos >= begin() && pos <= end())
		{
			//检查容量
			if (_finish == _endofStorage)
			{
				//增容会导致迭代器失效
				//保存元素的个数
				size_t num = pos - _start;
				size_t newC = _endofStorage == nullptr ? 1 : 2 * capacity();
				reserve(newC);
				//更新迭代器
				pos =_start + num;
			}
			//移动元素
			iterator it = _finish;
			while (it != pos)
			{
				*it = *(it - 1);
				it--;
			}
			//插入元素
			*pos = val;
			//更新
			++_finish;
		}
	}

	//删除
	iterator erase(iterator pos)
	{
		//检查删除位置的有效性
		if (pos >= _start && pos < _finish)
		{
			iterator it = pos+1;
			while (it != _finish)
			{
				*(it -1) = *it;
				it++;
			}

			//更新_finish
			--_finish;

			//返回删除位置的下一个位置
			return pos;
		}
	}

	//迭代器
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

	//有效元素个数
	size_t size() const
	{
		return _finish - _start;
	}

	//容量
	size_t capacity() const
	{
		return _endofStorage - _start;
	}

private:
	T* _start;		//空间的起始位置
	T* _finish;		//最后一个有效元素的末尾
	T* _endofStorage;		//空间的末尾
};

//自定义类型成员必须自身具备赋值运算符重载，才能使用输出运算符重载
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
//迭代器方式打印Vector中元素的值
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
//范围for打印Vector中元素的值
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


////测试拷贝构造函数和赋值运算符重载函数
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

////explicit仅用于只有一个参数的构造函数，表明这个构造函数需要进行显示转换
////explicit关键字的作用就是防止类构造函数的隐式自动转换.
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
//	//自定义类型的尾插，会先调用构造函数建立一个对象，
//	//然后再根据空间大小考虑是否需要增容，在增容的同时会调用构造函数
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

////采用迭代器定义一个vector
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

////利用迭代器指定范围进行初始化
//void test()
//{
//	Vector<int> v((size_t)5, 32);
//	printForVector(v);
//	Vector<int> v2(v.begin(), v.end());
//	printForVector(v2);
//}

////非成员函数，打印Vector成员
//void test()
//{
//	Vector<int> v(6, 2);
//	printForVector(v);
//	printVector(v);
//}

////迭代器和只读迭代器测试
//void test()
//{
//	//迭代器
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
//		//*it2 = 'A';		//试图修改内容时报错
//		it2++;
//	}
//	cout << endl;
//}

////构造函数的测试：Vector(size_t n,const T& val=T())
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
////无参构造函数测试
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