//#include<iostream>
//using namespace std;
//
////小堆
//typedef int  HDataType;
//
//struct heap{
//	HDataType* _data;	//数据
//	int _size;			//有效元素个数
//	int _capacity;		//容量
//};
//
//void Print(HDataType* arr,HDataType sz)
//{
//	for (int i = 0; i < sz; ++i)
//	{
//		cout << arr[i] << " ";
//	}
//	cout << endl;
//}
//
////交换
//void Swap(HDataType* x1, HDataType* x2)
//{
//	*x1 = *x1 + *x2;
//	*x2 = *x1 - *x2;
//	*x1 = *x1 - *x2;
//}
//
////向上调整
//void shiftUp(HDataType* arr, int sz, int cur)
//{
//	int parent = (cur - 1) / 2;
//
//	while (cur > 0)
//	{
//		if (arr[parent] > arr[cur])
//		{
//			Swap(&arr[parent], &arr[cur]);
//		}
//
//		//更新
//		cur = parent;
//		parent = (cur - 1) / 2;
//	}
//}
//
////向下调整
//void shiftDown(HDataType* arr,int sz,int cur)
//{
//	//找到孩子节点
//	int child = 2 * cur + 1;
//
//	while (child < sz)
//	{
//		//找出左右孩子中较小的
//		if (child + 1 < sz && arr[child + 1] < arr[child])
//			child++;
//
//		if (arr[child] < arr[cur])
//		{
//			Swap(&arr[cur], &arr[child]);
//
//			//更新
//			cur = child;
//			child = 2 * cur + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//
////初始化
//void heapInit(heap* hp)
//{
//	//判空
//	if (hp == nullptr)
//		return;
//
//	hp->_data = nullptr;
//	hp->_size = hp->_capacity = 0;
//}
//
////检查容量
//void checkCapacity(heap* hp)
//{
//	if (hp->_size == hp->_capacity)
//	{
//		int newC = hp->_capacity == 0 ? 1 : 2 * hp->_capacity;
//		hp->_data = (HDataType*)realloc(hp->_data, sizeof(int)*newC);
//		hp->_capacity = newC;//更新
//	}
//	
//}
//
////插入
//void push(heap* hp,const HDataType& val)
//{
//	//判空
//	if (hp == nullptr)
//		return;
//
//	//检查容量
//	checkCapacity(hp);
//
//	//尾插
//	hp->_data[hp->_size] = val;
//
//	//更新
//	++hp->_size;
//
//	//从最后一个节点向上调整
//	shiftUp(hp->_data, hp->_size, hp->_size - 1);
//}
//
////建堆
//void heapCreate(heap* hp, HDataType* arr, int sz)
//{
//	//初始化
//	heapInit(hp);
//	
//	//插入元素
//	for (int i = 0; i < sz; ++i)
//	{
//		push(hp, arr[i]);
//	}
//}
//
////销毁
//void destroy(heap* hp)
//{
//	if (hp)
//	{
//		hp->_size = hp->_capacity = 0;
//		free(hp->_data);
//		hp->_data = nullptr;
//		//free(hp);//fp不是申请的空间，不需要手动释放
//		hp = nullptr;
//	}
//}
//
////删除
//void pop(heap* hp)
//{
//	//将根节点和最后一个元素交换
//	Swap(&hp->_data[0], &hp->_data[hp->_size - 1]);
//	
//	--hp->_size;//尾删
//
//	//从堆顶位置开始向下调整
//	shiftDown(hp->_data,hp->_size,0);
//}
////取堆顶的数据
//HDataType top(heap* hp)
//{
//	return hp->_data[0];
//}
//
////打印前k小的元素
//void PrintTopK(heap* hp,int k)
//{
//	//判断数据的有效性
//	if (hp == nullptr || k < 0 || k > hp->_size)
//		return;
//
//	int end = hp->_size-1;
//
//	while (k > 0)
//	{
//		//获取堆顶元素
//		cout << hp->_data[0] << " ";
//
//		//将栈顶元素和最后一个元素交换
//		Swap(&hp->_data[0], &hp->_data[end]);
//		
//
//		//从根节点开始向下调整
//		shiftDown(hp->_data,end, 0);
//		--end;
//		--k;
//	}
//	cout << endl;
//}
//
////对数组堆排序:从大到小的一个数组
//void Order(int* arr,int sz)
//{
//	//建一个小堆
//	for (int i = (sz - 2) / 2; i >= 0; --i)
//	{
//		shiftDown(arr,sz,i);
//	}
//
//	int end = sz - 1;
//	while (end > 0)
//	{	
//		//头尾元素交换
//		Swap(&arr[0], &arr[end]);
//		//执行向下调整
//		shiftDown(arr, end, 0);
//		end--;
//	}
//}
//
////判空
//int isEmpty(heap* hp)
//{
//	return hp->_data == nullptr || hp->_size == 0;
//}
//
////求堆元素个数
//int size(heap* hp)
//{
//	return hp->_size;
//}
//
//////Swap测试
////void test01()
////{
////	int a = 10, b = 20;
////	cout << "a:" << a << "b:" << b << endl;
////	Swap(&a, &b);
////	cout << "a:" << a << "b:" << b << endl;
////}
//
//////shiftUp测试
////void test02()
////{
////	int arr[] = { 5, 3, 10, 6, 1, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr,sz);
////	shiftUp( arr, sz, sz- 1);
////	Print(arr, sz);
////}
//
//////shiftDown测试
////void test03()
////{
////	int arr[] = { 5, 3, 10, 6, 1, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr, sz);
////	shiftDown(arr, sz, 0);
////	Print(arr, sz);
////}
//
//////heapCreate测试
////void test04()
////{
////	heap hp;
////	int arr[] = { 5, 12, 4, 38, 8, 9, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr, sz);
////	heapCreate(&hp,arr, sz);
////	Print(hp._data,hp._size);
////}
//
//////pop测试
////void test05()
////{
////	heap hp;
////	int arr[] = { 5, 12, 4, 38, 8, 9, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr, sz);
////	heapCreate(&hp, arr, sz);
////	Print(hp._data, hp._size);
////
////	cout << "pop:" << endl;
////	pop(&hp);
////	Print(hp._data, hp._size);
////	pop(&hp);
////	Print(hp._data, hp._size);
////	pop(&hp);
////	Print(hp._data, hp._size);
////}
//
//////PrintTopK测试
////void test06()
////{
////	heap hp;
////	int arr[] = { 5, 12, 4, 38, 8, 9, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	heapCreate(&hp, arr, sz);
////	Print(hp._data, hp._size);
////
////	PrintTopK(&hp, 4);
////}
//
//////Order 测试
////void test07()
////{
////	int arr[] = { 5, 12, 4, 38, 8, 9, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr, sz);
////	Order(arr, sz);
////	Print(arr, sz);
////}
//
//void test08()
//{
//	heap hp;
//	int arr[] = { 5, 12, 4, 38, 8, 9, 3 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	heapCreate(&hp, arr, sz);
//	Print(hp._data, hp._size);
//
//	destroy(&hp);
//}
//int main()
//{
//	//test01();
//	//test02();
//	//test03();
//	//test04();
//	//test05();
//	//test06();
//	//test07();
//	test08();
//	return 0;
//}