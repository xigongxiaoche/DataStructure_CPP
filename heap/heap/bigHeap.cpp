#include<iostream>
using namespace std;

//大堆
typedef int HDataType;
struct Heap{
	Heap()
		:_data(nullptr)
		, _size(0)
		, _capacity(0)
	{}

	~Heap()
	{
		free(_data);
		_size = _capacity = 0;
		_data = nullptr;
	}

	HDataType* _data;
	int _size;
	int _capacity;
};

//交换
void Swap(HDataType* data1, HDataType* data2)
{
	int tmp = *data1;
	*data1 = *data2;
	*data2 = tmp;
}

//打印
void Print(HDataType* arr,int sz)
{
	for (int i = 0; i < sz; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
//堆的向上调整
void shiftUp(HDataType* arr,int cur)
{
	//找到父亲节点
	int parent = (cur - 1) / 2;

	while (cur > 0)
	{
		//判断父亲节点和当前节点之间的大小关系
		if (arr[parent] < arr[cur])
		{
			Swap(&arr[parent], &arr[cur]);
		}

		//更新
		cur = parent;
		parent = (cur - 1) / 2;
	}
}
//堆的向下调整
void shiftDown(HDataType* arr,int sz,int cur)
{
	//找到孩子节点
	int child = 2 * cur + 1;

	while (child < sz)
	{
		//找到左右孩子中较大的
		if (child + 1 < sz && arr[child + 1] > arr[child])
		{
			++child;
		}

		//父节点小于子节点，交换
		if (arr[cur] < arr[child])
		{
			Swap(&arr[cur], &arr[child]);
		}

		//更新
		cur = child;
		child = 2 * cur + 1;
	}
}


//检查容量
void checkCapacity(Heap& hp)
{
	if (hp._size == hp._capacity)
	{
		int newC = hp._capacity == 0 ? 1 : 2 * hp._capacity;
		hp._data = (HDataType*)realloc(hp._data, sizeof(HDataType)*newC);
		hp._capacity = newC;
	}
}
//插入
void insert(Heap& hp, const HDataType& val)
{
	//检查容量
	checkCapacity(hp);

	//尾插
	hp._data[hp._size] = val;

	//更新
	++hp._size;

	//执行向上调整
	shiftUp(hp._data, hp._size - 1);
}
//建堆
void heapCreate(Heap& hp, int* arr,int sz)
{
	for (int i = 0; i < sz; ++i)
	{
		insert(hp, arr[i]);
	}
}
//删除
void pop(Heap& hp)
{
	//交换头尾元素
	Swap(&hp._data[0], &hp._data[hp._size - 1]);

	--hp._size;

	//执行向下调整
	shiftDown(hp._data, hp._size, 0);
}
//判空
bool isEmpty(const Heap& hp)
{
	return hp._data == nullptr || hp._size == 0;
}
//求有效元素个数
int size(const Heap& hp)
{
	return hp._size;
}
//获取堆顶元素
HDataType& top(const Heap& hp)
{
	return hp._data[0];
}
//打印前k大的元素
void PrintTopK(Heap& hp,int k)
{
	if (k<0 || k>hp._size)
		return;

	for (int i = 0; i < k; ++i)
	{
		//输出堆顶元素
		cout << top(hp)<<" ";

		pop(hp);
	}
	cout << endl;
}
//堆排序：从小到大
void heapSort(Heap& hp)
{
	int end = hp._size - 1;

	while (end > 0)
	{
		//交换
		Swap(&hp._data[0], &hp._data[end]);


		//从堆顶向下调整
		shiftDown(hp._data, end, 0);
		end--;
	}
}

////shiftUp测试
//void test01()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//
//	shiftUp(arr, sizeof(arr) / sizeof(arr[0]) - 1);
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//}

////shiftDown测试
//void test02()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//
//	shiftDown(arr, sizeof(arr) / sizeof(arr[0]),0);
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//}

////insert测试
//void test03()
//{
//	Heap hp;
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	for (int i = 0; i < sz; ++i)
//	{
//		insert(hp, arr[i]);
//	}
//
//	Print(hp._data, hp._size);
//}

////heapCreate测试
//void test04()
//{
//	Heap hp;
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	heapCreate(hp, arr, sz);
//	Print(hp._data, hp._size);
//}

////pop测试
//void test05()
//{
//	Heap hp;
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	heapCreate(hp, arr, sz);
//	
//
//	while (!isEmpty(hp))
//	{
//		Print(hp._data, hp._size);
//		cout << "size: " << size(hp) << endl;
//		cout << "top: " << top(hp) << endl;
//		cout << "*****************************************************" << endl;
//		pop(hp);
//	}
//}

//printTopK测试
void test06()
{
	Heap hp;
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	heapCreate(hp, arr, sz);

	PrintTopK(hp,12);
}

//heapSort测试
void test07()
{
	Heap hp;
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	heapCreate(hp, arr, sz);
	Print(hp._data, sz);
	heapSort(hp);
	Print(hp._data, sz);
}

int main()
{
	//test01();
	//test02();
	//test03();
	//test04();
	//test05();
	//test06();
	test07();
	return 0;
}