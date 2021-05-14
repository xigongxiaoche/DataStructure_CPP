#include<iostream>
using namespace std;

//���
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

//����
void Swap(HDataType* data1, HDataType* data2)
{
	int tmp = *data1;
	*data1 = *data2;
	*data2 = tmp;
}

//��ӡ
void Print(HDataType* arr,int sz)
{
	for (int i = 0; i < sz; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
//�ѵ����ϵ���
void shiftUp(HDataType* arr,int cur)
{
	//�ҵ����׽ڵ�
	int parent = (cur - 1) / 2;

	while (cur > 0)
	{
		//�жϸ��׽ڵ�͵�ǰ�ڵ�֮��Ĵ�С��ϵ
		if (arr[parent] < arr[cur])
		{
			Swap(&arr[parent], &arr[cur]);
		}

		//����
		cur = parent;
		parent = (cur - 1) / 2;
	}
}
//�ѵ����µ���
void shiftDown(HDataType* arr,int sz,int cur)
{
	//�ҵ����ӽڵ�
	int child = 2 * cur + 1;

	while (child < sz)
	{
		//�ҵ����Һ����нϴ��
		if (child + 1 < sz && arr[child + 1] > arr[child])
		{
			++child;
		}

		//���ڵ�С���ӽڵ㣬����
		if (arr[cur] < arr[child])
		{
			Swap(&arr[cur], &arr[child]);
		}

		//����
		cur = child;
		child = 2 * cur + 1;
	}
}


//�������
void checkCapacity(Heap& hp)
{
	if (hp._size == hp._capacity)
	{
		int newC = hp._capacity == 0 ? 1 : 2 * hp._capacity;
		hp._data = (HDataType*)realloc(hp._data, sizeof(HDataType)*newC);
		hp._capacity = newC;
	}
}
//����
void insert(Heap& hp, const HDataType& val)
{
	//�������
	checkCapacity(hp);

	//β��
	hp._data[hp._size] = val;

	//����
	++hp._size;

	//ִ�����ϵ���
	shiftUp(hp._data, hp._size - 1);
}
//����
void heapCreate(Heap& hp, int* arr,int sz)
{
	for (int i = 0; i < sz; ++i)
	{
		insert(hp, arr[i]);
	}
}
//ɾ��
void pop(Heap& hp)
{
	//����ͷβԪ��
	Swap(&hp._data[0], &hp._data[hp._size - 1]);

	--hp._size;

	//ִ�����µ���
	shiftDown(hp._data, hp._size, 0);
}
//�п�
bool isEmpty(const Heap& hp)
{
	return hp._data == nullptr || hp._size == 0;
}
//����ЧԪ�ظ���
int size(const Heap& hp)
{
	return hp._size;
}
//��ȡ�Ѷ�Ԫ��
HDataType& top(const Heap& hp)
{
	return hp._data[0];
}
//��ӡǰk���Ԫ��
void PrintTopK(Heap& hp,int k)
{
	if (k<0 || k>hp._size)
		return;

	for (int i = 0; i < k; ++i)
	{
		//����Ѷ�Ԫ��
		cout << top(hp)<<" ";

		pop(hp);
	}
	cout << endl;
}
//�����򣺴�С����
void heapSort(Heap& hp)
{
	int end = hp._size - 1;

	while (end > 0)
	{
		//����
		Swap(&hp._data[0], &hp._data[end]);


		//�ӶѶ����µ���
		shiftDown(hp._data, end, 0);
		end--;
	}
}

////shiftUp����
//void test01()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//
//	shiftUp(arr, sizeof(arr) / sizeof(arr[0]) - 1);
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//}

////shiftDown����
//void test02()
//{
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//
//	shiftDown(arr, sizeof(arr) / sizeof(arr[0]),0);
//	Print(arr, sizeof(arr) / sizeof(arr[0]));
//}

////insert����
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

////heapCreate����
//void test04()
//{
//	Heap hp;
//	int arr[] = { 1, 2, 3, 4, 5, 6 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	heapCreate(hp, arr, sz);
//	Print(hp._data, hp._size);
//}

////pop����
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

//printTopK����
void test06()
{
	Heap hp;
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	heapCreate(hp, arr, sz);

	PrintTopK(hp,12);
}

//heapSort����
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