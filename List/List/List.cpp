#include<iostream>

using namespace std;

//定义节点
template <class T>
struct ListNode
{
	T _data;	//节点数据
	ListNode<T>* _next;		//后一个位置
	ListNode<T>* _prev;		//前一个位置
	ListNode(const T& val = T())
		:_data(val)
		, _next(nullptr)
		, _prev(nullptr)
	{}
};

//定义List迭代器类
//T:变量类型   Ref:引用   Ptr:指针
template<class T,class Ref,class Ptr>
struct ListIterator{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	//封装一个节点
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//让迭代器支持解引用操作 ----重载*运算符
	Ref operator*()
	{
		return _node->_data;
	}

	//前置++
	Self& operator++()
	{
		//移动到下一个元素的位置
		_node = _node->_next;

		return *this;
	}

	//后置++
	Self& operator++(int)
	{
		Self res(*this);
		//移动到下一个元素的位置
		_node = _node->_next;
		//返回未修改之前的迭代器
		return res;
	}

	//前置--
	Self& operator--()
	{
		//移动到下一个元素的位置
		_node = _node->_prev;

		return *this;
	}

	//后置--
	Self& operator--(int)
	{
		Self res(*this);
		//移动到下一个元素的位置
		_node = _node->_prev;
		//返回未修改之前的迭代器
		return res;
	}  

	//重载!=
	bool operator!=(Self& lst)
	{
		//判断两个数据的位置是否相同
		return _node != lst._node;
	}

	//重载->运算符
	Ptr operator->()
	{
		return &_node->_data;
	}

};

//list类-----带 头结点 的 双向 循环 链表
template <class T>
class List{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> iterator;
	typedef ListIterator<T,const T&,const T*> const_iterator;

	iterator begin()
	{
		//封装第一个节点
		//创建一个迭代器对象
		return iterator(_header->_next);
	}

	iterator end()
	{
		//封装头节点
		//创建一个迭代器对象
		return iterator(_header);
	}

	const_iterator begin()const 
	{
		//封装第一个节点
		//创建一个迭代器对象
		return const_iterator(_header->_next);
	}
	
	const_iterator end()const
	{
		//封装第一个节点
		//创建一个迭代器对象
		return const_iterator(_header);
	}

	//尾插
	void pushBack(const T& val)
	{
		//创建一个新的节点
		Node* newNode = new Node(val);
		//找到尾节点
		Node* tail = _header->_prev;

		//插入节点
		tail->_next = newNode;
		newNode->_prev = tail;
		newNode->_next = _header;
		_header->_prev = newNode;

		//这种调用其它接口的操作是可行的，但是最好降低接口间的耦合度
		//insert(end(), val);
	}

	//头插
	void pushFront(const T& val)
	{
		
		//创建一个新的节点
		Node* newNode = new Node(val);
		找到头节点后面的第一个节点
		Node* first = _header->_next;

		//插入节点
		newNode->_next = first;
		first->_prev = newNode;
		_header->_next = newNode;
		newNode->_prev = _header;
		
		//这种调用其它接口的操作是可行的，但是最好降低接口间的耦合度
		insert(begin(), val);
	}

	//尾删
	void popBack()
	{
		Node* tail = _header->_prev;	//尾节点
		Node* tail_prev = tail->_prev;	//尾节点的前一个节点

		//释放尾部元素
		delete tail;

		//更新
		tail_prev->_next = _header;
		header->_prev = tail_prev;
		
		//这种调用其它接口的操作是可行的，但是最好降低接口间的耦合度
		//erase(--end());
	}

	//头删
	void popFront()
	{
		//找到第一个节点和第二个节点
		Node* first = _header->_next;
		Node* second = first->_next;

		//释放第一个节点
		delete first;

		//更新
		_header->_next = second;
		second->_prev = _header;
		
		//这种调用其它接口的操作是可行的，但是最好降低接口间的耦合度
		//erase(begin());
	}

	//插入
	void insert(iterator pos, const T& val)
	{
		//创建一个新的节点
		Node* newNode = new Node(val);
		Node* cur = pos._node;
		Node* prev =cur->_prev;

		prev->_next = newNode;		//这个位置出现内存访问越界
		newNode->_prev = prev;
		newNode->_next = cur;
		cur->_prev = newNode;
	}

	//返回删除后的下一个位置
	iterator erase(iterator& pos)
	{
		//不能删除头节点，也就是end迭代器执行的位置
		if (pos != end())
		{
			Node* cur = pos._node;
			Node* front = cur->_prev;
			Node* rear = cur->_next;

			front->_next = rear;
			rear->_prev = front;

			delete cur;		//释放当前空间

			//创建指向删除的节点的下一个节点的迭代器
			return iterator(rear);
		}

		return pos;
	}

	//打印
	void Print()
	{
		Node* it = _header->_next;
		while (it != _header)
		{
			cout << it->_data << " ";
			it=it->_next;
		}
		cout << endl;
	}

	//空的带头双向循环链表
	List()
	{
		_header = new Node;
		_header->_next = _header->_prev = _header;
	}

	//浅拷贝只是复制了指针，会多次释放空间的内容，
	//深拷贝
	List(const List<T>& lst)
		:_header(new Node())
	{
		_header->_prev = _header->_next=_header;	//这里因为疏忽，没有加最后的_header

		////从第一个有效节点开始插入
		//Node* cur = lst._header->_next;
		//while (cur != lst._header)
		//{
		//	pushBack(cur->_data);
		//	cur = cur->_next;
		//}
		
		//插入lst中的每个数据
		for (const auto& e : lst)
			pushBack(e);
	}

	//清空数据
	void Clear()
	{
		Node* cur = _header->_next;
		while (cur != _header)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//恢复循环结构
		_header->_next = _header->_prev = _header;
	}

	////赋值运算符重载,传统写法
	//List<T>& operator=(const List<T>& lst)
	//{
	//	if (this != &lst)
	//	{
	//		//清空数据
	//		Clear();

	//		//插入lst中的每个数据
	//		for (const auto& e : lst)
	//			pushBack(e);

	//		return *this;
	//	}
	//}


	//赋值运算符重载,现代写法
	List<T>& operator=(List<T> lst)
	{
		if (this != &lst)
		{
			swap(_header, lst._header);
			return *this;
		}
	}

	//析构函数
	~List()
	{
		Clear();
		delete _header;
	}
	
private:
	Node* _header;
};

template<class T>
void const_Print(const List<T>& lst)
{
	List<T>::const_iterator it = lst.begin();
	while (it != lst.end())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}

//范围for打印
template<class T>
void printFor(const List<T>& lst)
{
	for (auto& e : lst)
		cout << e << " ";
		cout << endl;
}


void test()
{
	List<int> lst;
	lst.pushBack(1024);
	lst.pushBack(512);
	lst.pushBack(256);
	lst.pushBack(2048);
	lst.pushBack(4096);
	lst.pushBack(8192);
	printFor(lst);

	List<int> lst2(lst);
	printFor(lst2);

	/*List<int> lst3;
	printFor(lst3);

	lst3 = lst;
	printFor(lst3);*/

}

//void test()
//{
//	List<int> lst;
//	lst.pushBack(1024);
//	lst.pushBack(512);
//	lst.pushBack(256);
//	lst.pushBack(2048);
//	lst.pushBack(4096);
//	lst.pushBack(8192);
//	printFor(lst);
//	lst.popBack();
//	lst.popFront();
//	printFor(lst);
//}

////头插，尾插测试
//void test()
//{
//	List<int> lst;
//	lst.pushBack(1024);
//	lst.pushBack(512);
//	lst.pushBack(256);
//	printFor(lst);
//	lst.pushFront(1024);
//	lst.pushFront(512);
//	lst.pushFront(256);
//	printFor(lst);
//	
//}

//void test()
//{
//	List<int> lst;
//	lst.pushBack(1);
//	lst.pushBack(2);
//	lst.pushBack(3);
//	lst.pushBack(4);
//	lst.pushBack(5);
//	printFor(lst);
//
//
//	lst.insert(++lst.begin(), 1024);
//	lst.insert(--lst.end(), 1024);
//	printFor(lst);
//
//}

//void test()
//{
//	List<int> lst;
//	lst.pushBack(1);
//	lst.pushBack(2);
//	lst.pushBack(3);
//	lst.pushBack(4);
//	lst.pushBack(5);
//	const_Print(lst);
//}

//void test()
//{
//	List<int> lst;
//	lst.pushBack(2);
//	lst.pushBack(4);
//	lst.pushBack(8);
//	lst.pushBack(16);
//	lst.pushBack(32);
//	lst.Print();
//	List<int>::iterator it = lst.begin();
//	List<int>::iterator it2 = ++lst.begin();
//	List<int>::iterator it3 = lst.begin()++;
//	cout << "*it: " << *it << endl;
//	cout << "前置++: " << *it2 << endl;
//	cout << "后置++: " << *it3 << endl;
//}

//struct Date{
//
//	Date(int year = 2021, int month = 4, int day = 6)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{}
//
//	int _year = 2021;
//	int _month = 4;
//	int _day = 6;
//};
//void test()
//{
//	List<Date> lst;
//	
//	lst.pushBack(Date(2020, 1, 1));
//	lst.pushBack(Date(2020, 1, 2));
//	lst.pushBack(Date(2020, 1, 3));
//	lst.pushBack(Date(2020, 1, 4));
//
//	List<Date>::iterator it = lst.begin();
//	while (it != lst.end())
//	{
//		//cout << (*it)._year << " " << (*it)._month << " " << (*it)._day << endl;
//		cout <<it->_year << " " << it->_month << " " << it->_day << endl;
//
//		//这是->运算符使用的完整形式，上面的形式是编译器为我们做的优化
//		//cout <<"test  "<< it.operator->()->_year << endl;   
//		it++;
//	}
//	cout << endl;
//}

//void test()
//{
//	List<int> lst;
//	lst.pushBack(2);
//	lst.pushBack(4);
//	lst.pushBack(8);
//	lst.pushBack(16);
//	lst.pushBack(32);
//
//	List<int>::iterator it = lst.begin();
//	while (it != lst.end())
//	{
//		cout << *it << " ";
//		it++;
//	}
//
//	cout << endl;
//}

////测试构造函数，头插，尾插，头删，尾删，打印
//void test()
//{
//	List<int> lst;
//	lst.pushBack(1);
//	lst.pushBack(2);
//	lst.pushBack(3);
//	lst.pushBack(4);
//	lst.pushBack(5);
//	lst.pushBack(6);
//	lst.pushBack(7);
//	lst.pushBack(8);
//	lst.pushFront(0);
//	lst.pushFront(-1);
//	lst.pushFront(-2);
//	lst.pushFront(-3);
//	lst.pushFront(-4);
//	lst.Print();
//
//	lst.popBack();
//	lst.popBack();
//	lst.popBack();
//	lst.Print();
//
//	lst.popFront();
//	lst.popFront();
//	lst.popFront();
//	lst.popFront();
//	lst.Print();
//}

int main()
{
	test();
	return 0;
}
