#include<iostream>
#include<deque>

using namespace std;
namespace cxp
{
	template<class T,class container=deque<T>>
	class Stack
	{
	public:
		Stack(){}

		bool empty()
		{
			return _st.empty();
		}

		size_t size()
		{
			return _st.size();
		}

		const T& top()
		{
			return _st.front();
		}

		void push_back(const T& val)
		{
			_st.push_front(val);
		}

		void pop_back()
		{
			_st.pop_front();
		}
	private:
		container _st;
	};
}



void test()
{
	cxp::Stack<int> st;
	st.push_back(2);
	st.push_back(4);
	st.push_back(8);
	st.push_back(16);
	st.push_back(32);
	for (int i = 0; i < 5; ++i)
	{
		cout << "current size:"<<st.size() << endl;
		cout << "current top:"<<st.top() << endl;
		cout << "Is empty? " << st.empty() << endl;
		st.pop_back();
	}
	cout << "Is empty? " << st.empty() << endl;
	cout << endl;
}

int main(int argc, const char* argv, const char* env)
{
	test();
	return 0;
}