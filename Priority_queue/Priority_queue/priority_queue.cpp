#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>

using namespace std;
namespace cxp
{
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class Priority_queue{
	public:
		void shiftup(size_t pos)
		{
			size_t child = pos;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (v[child] > v[parent])
				if (_cmp(v[parent], v[child]))
				{
					swap(v[child], v[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
					break;
			}
		}

		void shiftdown()
		{
			size_t parent = 0;
			size_t child = 2 * parent + 1;
			while (child < v.size())
			{
				//if (child + 1 < v.size() && v[child + 1] > v[child])
				if (child + 1 < v.size() && _cmp(v[child], v[child + 1]))
					child++;
				//if (v[child] > v[parent])
				if (_cmp(v[parent], v[child]))
				{
					swap(v[parent], v[child]);
					parent = child;
					child = 2 * parent + 1;
				}
				else
					break;
			}
		}

		void push(const T& val)
		{
			v.push_back(val);
			shiftup(v.size() - 1);
		}

		void pop()
		{
			swap(v[0], v[v.size() - 1]);
			v.pop_back();
			shiftdown();
		}

		T& top()
		{
			return v[0];
			//return v.front();
		}
		size_t size()const
		{
			return v.size();
		}

		bool empty() const
		{
			return v.empty();
		}
		
	private:
		Container v;
		Compare _cmp;
	};
}
//仿函数类模板
template<class T>
struct Greater
{
	bool operator()(const T& val1, const T& val2)
	{
		return val1 > val2;
	}
};

//仿函数类模板
template<class T>
struct Less
{
	bool operator()(const T& val1, const T& val2)
	{
		return val1 < val2;
	}
};

bool fun(int i,int j)
{
	return i < j;
}
void test()
{
	cxp::Priority_queue<int,vector<int>,Less<int>> pq;
	pq.push(2);
	pq.push(4);
	pq.push(8);
	pq.push(16);
	pq.push(32);
	//sort(pq.begin(), pq.end(), fun);
	cout << "size:" << pq.size() << endl;
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

int main()
{
	test();
	return 0;
}
