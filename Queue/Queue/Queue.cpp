#include<iostream>
#include<deque>
using namespace std;
namespace cxp
{
	template<class T,class Container=deque<T>>
	class Queue
	{
	public:
		Queue(){}

		bool empty()
		{
			return _q.empty();
		}
		size_t size()
		{
			return _q.size();
		}
		const T& front()
		{
			return _q.front();
		}
		const T& back()
		{
			return _q.back();
		}
		void push_back(const T& val)
		{
			_q.push_back(val);
		}
		void pop_front()
		{
			_q.pop_front();
		}
	private:
		Container _q;
	};
}

void test()
{
	cxp::Queue<char> q;
	q.push_back('I');
	q.push_back('*');
	q.push_back('a');
	q.push_back('m');
	q.push_back('*');
	q.push_back('s');
	q.push_back('o');
	q.push_back('*');
	q.push_back('l');
	q.push_back('a');
	q.push_back('c');
	q.push_back('k');
	q.push_back('*');
	q.push_back('o');
	q.push_back('f');
	q.push_back('*');
	q.push_back('f');
	q.push_back('a');
	q.push_back('c');
	q.push_back('u');
	q.push_back('l');
	q.push_back('t');
	q.push_back('y');
	q.push_back('!');
	cout << "size of q:"<<q.size() << endl;
	cout << "back of q:" << q.back() << endl;
	while (!q.empty())
	{
		cout<<q.front();
		q.pop_front();
	}
	cout << endl;

}

int main()
{
	test();
	return 0;
}