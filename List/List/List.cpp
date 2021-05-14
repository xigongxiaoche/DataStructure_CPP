#include<iostream>

using namespace std;

//����ڵ�
template <class T>
struct ListNode
{
	T _data;	//�ڵ�����
	ListNode<T>* _next;		//��һ��λ��
	ListNode<T>* _prev;		//ǰһ��λ��
	ListNode(const T& val = T())
		:_data(val)
		, _next(nullptr)
		, _prev(nullptr)
	{}
};

//����List��������
//T:��������   Ref:����   Ptr:ָ��
template<class T,class Ref,class Ptr>
struct ListIterator{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	//��װһ���ڵ�
	Node* _node;

	ListIterator(Node* node)
		:_node(node)
	{}

	//�õ�����֧�ֽ����ò��� ----����*�����
	Ref operator*()
	{
		return _node->_data;
	}

	//ǰ��++
	Self& operator++()
	{
		//�ƶ�����һ��Ԫ�ص�λ��
		_node = _node->_next;

		return *this;
	}

	//����++
	Self& operator++(int)
	{
		Self res(*this);
		//�ƶ�����һ��Ԫ�ص�λ��
		_node = _node->_next;
		//����δ�޸�֮ǰ�ĵ�����
		return res;
	}

	//ǰ��--
	Self& operator--()
	{
		//�ƶ�����һ��Ԫ�ص�λ��
		_node = _node->_prev;

		return *this;
	}

	//����--
	Self& operator--(int)
	{
		Self res(*this);
		//�ƶ�����һ��Ԫ�ص�λ��
		_node = _node->_prev;
		//����δ�޸�֮ǰ�ĵ�����
		return res;
	}  

	//����!=
	bool operator!=(Self& lst)
	{
		//�ж��������ݵ�λ���Ƿ���ͬ
		return _node != lst._node;
	}

	//����->�����
	Ptr operator->()
	{
		return &_node->_data;
	}

};

//list��-----�� ͷ��� �� ˫�� ѭ�� ����
template <class T>
class List{
public:
	typedef ListNode<T> Node;
	typedef ListIterator<T,T&,T*> iterator;
	typedef ListIterator<T,const T&,const T*> const_iterator;

	iterator begin()
	{
		//��װ��һ���ڵ�
		//����һ������������
		return iterator(_header->_next);
	}

	iterator end()
	{
		//��װͷ�ڵ�
		//����һ������������
		return iterator(_header);
	}

	const_iterator begin()const 
	{
		//��װ��һ���ڵ�
		//����һ������������
		return const_iterator(_header->_next);
	}
	
	const_iterator end()const
	{
		//��װ��һ���ڵ�
		//����һ������������
		return const_iterator(_header);
	}

	//β��
	void pushBack(const T& val)
	{
		////����һ���µĽڵ�
		//Node* newNode = new Node(val);
		////�ҵ�β�ڵ�
		//Node* tail = _header->_prev;

		////����ڵ�
		//tail->_next = newNode;
		//newNode->_prev = tail;
		//newNode->_next = _header;
		//_header->_prev = newNode;

		insert(end(), val);
	}

	//ͷ��
	void pushFront(const T& val)
	{
		/*
		//����һ���µĽڵ�
		Node* newNode = new Node(val);
		�ҵ�ͷ�ڵ����ĵ�һ���ڵ�
		Node* first = _header->_next;

		//����ڵ�
		newNode->_next = first;
		first->_prev = newNode;
		_header->_next = newNode;
		newNode->_prev = _header;
		*/
		insert(begin(), val);
	}

	//βɾ
	void popBack()
	{
		//Node* tail = _header->_prev;	//β�ڵ�
		//Node* tail_prev = tail->_prev;	//β�ڵ��ǰһ���ڵ�

		////�ͷ�β��Ԫ��
		//delete tail;

		////����
		//tail_prev->_next = _header;
		//_header->_prev = tail_prev;
		erase(--end());
	}

	//ͷɾ
	void popFront()
	{
		////�ҵ���һ���ڵ�͵ڶ����ڵ�
		//Node* first = _header->_next;
		//Node* second = first->_next;

		////�ͷŵ�һ���ڵ�
		//delete first;

		////����
		//_header->_next = second;
		//second->_prev = _header;
		erase(begin());
	}

	//����
	void insert(iterator pos, const T& val)
	{
		//����һ���µĽڵ�
		Node* newNode = new Node(val);
		Node* cur = pos._node;
		Node* prev =cur->_prev;

		prev->_next = newNode;		//���λ�ó����ڴ����Խ��
		newNode->_prev = prev;
		newNode->_next = cur;
		cur->_prev = newNode;
	}

	//����ɾ�������һ��λ��
	iterator erase(iterator& pos)
	{
		//����ɾ��ͷ�ڵ㣬Ҳ����end������ִ�е�λ��
		if (pos != end())
		{
			Node* cur = pos._node;
			Node* front = cur->_prev;
			Node* rear = cur->_next;

			front->_next = rear;
			rear->_prev = front;

			delete cur;		//�ͷŵ�ǰ�ռ�

			//����ָ��ɾ���Ľڵ����һ���ڵ�ĵ�����
			return iterator(rear);
		}

		return pos;
	}

	//��ӡ
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

	//�յĴ�ͷ˫��ѭ������
	List()
	{
		_header = new Node;
		_header->_next = _header->_prev = _header;
	}

	//ǳ����ֻ�Ǹ�����ָ�룬�����ͷſռ�����ݣ�
	//���
	List(const List<T>& lst)
		:_header(new Node())
	{
		_header->_prev = _header->_next=_header;	//������Ϊ�����û�м�����_header

		////�ӵ�һ����Ч�ڵ㿪ʼ����
		//Node* cur = lst._header->_next;
		//while (cur != lst._header)
		//{
		//	pushBack(cur->_data);
		//	cur = cur->_next;
		//}
		
		//����lst�е�ÿ������
		for (const auto& e : lst)
			pushBack(e);
	}

	//�������
	void Clear()
	{
		Node* cur = _header->_next;
		while (cur != _header)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		//�ָ�ѭ���ṹ
		_header->_next = _header->_prev = _header;
	}

	////��ֵ���������,��ͳд��
	//List<T>& operator=(const List<T>& lst)
	//{
	//	if (this != &lst)
	//	{
	//		//�������
	//		Clear();

	//		//����lst�е�ÿ������
	//		for (const auto& e : lst)
	//			pushBack(e);

	//		return *this;
	//	}
	//}


	//��ֵ���������,�ִ�д��
	List<T>& operator=(List<T> lst)
	{
		if (this != &lst)
		{
			swap(_header, lst._header);
			return *this;
		}
	}

	//��������
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

//��Χfor��ӡ
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

////ͷ�壬β�����
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
//	cout << "ǰ��++: " << *it2 << endl;
//	cout << "����++: " << *it3 << endl;
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
//		//����->�����ʹ�õ�������ʽ���������ʽ�Ǳ�����Ϊ���������Ż�
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

////���Թ��캯����ͷ�壬β�壬ͷɾ��βɾ����ӡ
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