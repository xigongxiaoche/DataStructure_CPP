//#include<iostream>
//using namespace std;
//
////С��
//typedef int  HDataType;
//
//struct heap{
//	HDataType* _data;	//����
//	int _size;			//��ЧԪ�ظ���
//	int _capacity;		//����
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
////����
//void Swap(HDataType* x1, HDataType* x2)
//{
//	*x1 = *x1 + *x2;
//	*x2 = *x1 - *x2;
//	*x1 = *x1 - *x2;
//}
//
////���ϵ���
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
//		//����
//		cur = parent;
//		parent = (cur - 1) / 2;
//	}
//}
//
////���µ���
//void shiftDown(HDataType* arr,int sz,int cur)
//{
//	//�ҵ����ӽڵ�
//	int child = 2 * cur + 1;
//
//	while (child < sz)
//	{
//		//�ҳ����Һ����н�С��
//		if (child + 1 < sz && arr[child + 1] < arr[child])
//			child++;
//
//		if (arr[child] < arr[cur])
//		{
//			Swap(&arr[cur], &arr[child]);
//
//			//����
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
////��ʼ��
//void heapInit(heap* hp)
//{
//	//�п�
//	if (hp == nullptr)
//		return;
//
//	hp->_data = nullptr;
//	hp->_size = hp->_capacity = 0;
//}
//
////�������
//void checkCapacity(heap* hp)
//{
//	if (hp->_size == hp->_capacity)
//	{
//		int newC = hp->_capacity == 0 ? 1 : 2 * hp->_capacity;
//		hp->_data = (HDataType*)realloc(hp->_data, sizeof(int)*newC);
//		hp->_capacity = newC;//����
//	}
//	
//}
//
////����
//void push(heap* hp,const HDataType& val)
//{
//	//�п�
//	if (hp == nullptr)
//		return;
//
//	//�������
//	checkCapacity(hp);
//
//	//β��
//	hp->_data[hp->_size] = val;
//
//	//����
//	++hp->_size;
//
//	//�����һ���ڵ����ϵ���
//	shiftUp(hp->_data, hp->_size, hp->_size - 1);
//}
//
////����
//void heapCreate(heap* hp, HDataType* arr, int sz)
//{
//	//��ʼ��
//	heapInit(hp);
//	
//	//����Ԫ��
//	for (int i = 0; i < sz; ++i)
//	{
//		push(hp, arr[i]);
//	}
//}
//
////����
//void destroy(heap* hp)
//{
//	if (hp)
//	{
//		hp->_size = hp->_capacity = 0;
//		free(hp->_data);
//		hp->_data = nullptr;
//		//free(hp);//fp��������Ŀռ䣬����Ҫ�ֶ��ͷ�
//		hp = nullptr;
//	}
//}
//
////ɾ��
//void pop(heap* hp)
//{
//	//�����ڵ�����һ��Ԫ�ؽ���
//	Swap(&hp->_data[0], &hp->_data[hp->_size - 1]);
//	
//	--hp->_size;//βɾ
//
//	//�ӶѶ�λ�ÿ�ʼ���µ���
//	shiftDown(hp->_data,hp->_size,0);
//}
////ȡ�Ѷ�������
//HDataType top(heap* hp)
//{
//	return hp->_data[0];
//}
//
////��ӡǰkС��Ԫ��
//void PrintTopK(heap* hp,int k)
//{
//	//�ж����ݵ���Ч��
//	if (hp == nullptr || k < 0 || k > hp->_size)
//		return;
//
//	int end = hp->_size-1;
//
//	while (k > 0)
//	{
//		//��ȡ�Ѷ�Ԫ��
//		cout << hp->_data[0] << " ";
//
//		//��ջ��Ԫ�غ����һ��Ԫ�ؽ���
//		Swap(&hp->_data[0], &hp->_data[end]);
//		
//
//		//�Ӹ��ڵ㿪ʼ���µ���
//		shiftDown(hp->_data,end, 0);
//		--end;
//		--k;
//	}
//	cout << endl;
//}
//
////�����������:�Ӵ�С��һ������
//void Order(int* arr,int sz)
//{
//	//��һ��С��
//	for (int i = (sz - 2) / 2; i >= 0; --i)
//	{
//		shiftDown(arr,sz,i);
//	}
//
//	int end = sz - 1;
//	while (end > 0)
//	{	
//		//ͷβԪ�ؽ���
//		Swap(&arr[0], &arr[end]);
//		//ִ�����µ���
//		shiftDown(arr, end, 0);
//		end--;
//	}
//}
//
////�п�
//int isEmpty(heap* hp)
//{
//	return hp->_data == nullptr || hp->_size == 0;
//}
//
////���Ԫ�ظ���
//int size(heap* hp)
//{
//	return hp->_size;
//}
//
//////Swap����
////void test01()
////{
////	int a = 10, b = 20;
////	cout << "a:" << a << "b:" << b << endl;
////	Swap(&a, &b);
////	cout << "a:" << a << "b:" << b << endl;
////}
//
//////shiftUp����
////void test02()
////{
////	int arr[] = { 5, 3, 10, 6, 1, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr,sz);
////	shiftUp( arr, sz, sz- 1);
////	Print(arr, sz);
////}
//
//////shiftDown����
////void test03()
////{
////	int arr[] = { 5, 3, 10, 6, 1, 3 };
////	int sz = sizeof(arr) / sizeof(arr[0]);
////	Print(arr, sz);
////	shiftDown(arr, sz, 0);
////	Print(arr, sz);
////}
//
//////heapCreate����
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
//////pop����
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
//////PrintTopK����
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
//////Order ����
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