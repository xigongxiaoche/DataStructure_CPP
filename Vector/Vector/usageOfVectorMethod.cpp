//#include<iostream>
//#include<vector>
//#include<math.h>
//
//using namespace std;
//
//void test()
//{
//	//at和operator的区别
//	vector<int> v1 = { 0, 1, 2, 3, 4, 5 };
//	v1[10] = 1024;
//	//v1.at(10) = 1024;
//}

//void test()
//{
//	int a = 1, b = 2;
//	printf("a|b=%d\n", a | b);
//}

//void test()
//{
//	vector<int> v1{ 0, 1, 2, 3, 4, 5, 6 };
//	vector<int>::iterator it = v1.begin();
//
//	//erase的返回值为删除的元素后面第一个元素的位置
//	it = v1.erase(++v1.begin(),--v1.end());
//	cout << *it << endl;
//}

//void test()
//{
//	//生成杨辉三角
//	int numRows;
//	cout << "请输入要生成的杨辉三角的行数:";
//	cin >> numRows;
//
//	//开辟有numRows个元素的vector
//	vector<vector<int>> A(numRows);
//
//	//为vector内的每一个元素开辟空间,并初始化所有的元素为1
//	int i, j;
//	for (i = 1; i <= numRows; ++i)
//	{
//		//使用resize
//		A[i - 1].resize(i,1);
//	}
//
//
//	//从第三行开始计算中间的值
//	for (i = 2; i<numRows; ++i)
//	{
//		for (j = 1; j<i; ++j)
//		{
//			A[i][j] = A[i - 1][j - 1] + A[i - 1][j];
//		}
//	}
//	for (i = 0; i < numRows; ++i)
//	{
//		for (j = 0; j <= i; ++j)
//		{
//			cout << A[i][j] << "\t";
//		}
//		cout << endl;
//	}
//}


//void test()
//{
//	//迭代器失效的两种情况
//	//情况1.增容时因为原来所指空间被释放
//	//情况2.删除元素时，删除之前迭代器所指的空间不可用
//
//	vector<int> v1(5, 6);
//
//	////情况1：
//	//vector<int>::iterator it = v1.begin();
//	//v1.reserve(10);
//	////当我们再次使用之前定义的迭代器时，因为之前迭代器所指的空间已经被释放，
//	////现在对迭代器所指空间的进行操作时，就是对一块非法的空间进行操作，报出assertion failed
//	//while (it != v1.end())
//	//{
//	//	cout << *it << endl;
//	//	it++;
//	//}
//
//
//	//情况2：
//	//报出assertion failed
//	vector<int>::iterator it = ++v1.begin();
//	v1.erase(++v1.begin(), --v1.end());
//
//	while (it != v1.end())
//	{
//		cout << *it << endl;
//		it++;
//	}
//
//
//}

//void test()
//{
//	//用vector定义一个矩阵来存储9*9乘法口诀表
//
//	//定义一个有9个元素的vector,每个元素又是一个由9个元素组成的vector
//	vector<vector<int>> v1(9, vector<int>(9));
//
//	for (int i = 1; i <= 9; ++i)
//	{
//		for (int j = i; j <= 9; ++j)
//		{
//			v1[i-1][j-1] = i*j;
//		}
//	}
//	for (int i = 1; i <= 9; ++i)
//	{
//		for (int j = i; j <= 9; ++j)
//		{
//			cout << i << "*" << j << "=" << v1[i - 1][j - 1] << "\t" ;
//		}
//		cout << endl;
//	}
//}

//void test()
//{
//	//定义一个有五个元素的vector,每个元素又是一个由五个元素组成的vector
//	vector<vector<int>> v1(5,vector<int>(5));
//
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//		{
//			v1[i][j] = (i + 1)*(j + 1);
//		}
//	}
//	for (int i = 0; i < 5; ++i)
//	{
//		for (int j = 0; j < 5; ++j)
//		{
//			cout << v1[i][j] << "\t";
//		}
//		cout << endl;
//	}
//}

//void test()
//{
//	//vector非成员函数swap
//	vector<int> v1{ 1, 1, 1, 1, 1 };
//	vector<int> v2(9, 1024);
//	v1.swap(v2);
//}

//void test()
//{
//	//vector非成员函数：关系运算符函数  
//	vector<int> v1{ 1,2,1 };
//	vector<int> v2{ 1, 2, 3, 4, 5, 6, 7 };
//	vector<int> v3(v1);
//	vector<int> v4{ 1024, 111, 222, 3, 4, 566, 6 };
//
//
//
//	if (v1 == v2)
//		cout << "v1==v2" << endl;
//	else
//		cout << "v1!=v2" << endl;
//
//	if (v1 != v3)
//		cout << "v1!=v3" << endl;
//	else
//		cout << "v1==v3" << endl;
//
//	if (v1 < v2)
//		cout << "v1<v2" << endl;
//	else
//		cout << "v1>=v2" << endl;
//
//	if (v2 <= v4)
//		cout << "v2<=v4" << endl;
//	else
//		cout << "v2>v4" << endl;
//
//	if (v4>v2)
//		cout << "v4> v2" << endl;
//	else
//		cout << "v4<=v2" << endl;
//
//	if (v4>=v1)
//		cout << "v4>= v1" << endl;
//	else
//		cout << "v4<v1" << endl;
//}

//void test()
//{
//	//void clear();
//	//将size置为0，清空之前的内容
//	//capacity保持不变
//	vector<int> v1 = { 1, 2, 3, 45 };
//	v1.clear();
//}
//void test()
//{
//	//void swap (vector& x)
//	//交换两个vetcor中的内容
//	vector<int> v1 = { 1, 2, 3, 4 };
//	vector<int> v2(10,1024);
//
//	v1.swap(v2);
//}

//void test()
//{
//	/*
//		iterator erase (iterator position);
//
//		iterator erase (iterator first, iterator last);
//	*/
//
//	//iterator erase (iterator position);
//	vector<int> v1 = { 0,1, 2, 3, 4, 5, 6, 7 };
//	v1.erase(++v1.begin());		//删除第二个元素
//	v1.erase(--v1.end());		//删除最后一个位置的元素
//
//	//iterator erase (iterator first, iterator last);
//	v1.erase(++v1.begin(), v1.end());	//删除第二个元素及其后面所有的元素
//}

//void test()
//{
//	vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7 };
//
//	int arr[] = { 8, 9, 10, 11, 12, 13, 14 };
//	v1.emplace(v1.begin(), 0);    //起始位置插入，相当于push_front
//	v1.emplace(v1.end(),1024);    //结束位置插入，相当于push_back
//	v1.emplace(++v1.begin(), 512);		//从第一个元素的下一个位置插入512
//
//	////emplace第二个参数就是要插入的值，只能是一个值
//	//v1.emplace(v1.begin(), arr);
//
//	//emplace_back： 尾插
//	vector<int> v2 = { 0, 1, 2 };
//	v2.emplace_back(3);
//	v2.emplace_back(4);
//	v2.emplace_back(5);
//}

//void test()
//{
//	//assign：为向量分配新内容，替换其当前内容，并相应地修改其大小
//	/*
//		template <class InputIterator>
//			void assign (InputIterator first, InputIterator last);
//
//		void assign (size_type n, const value_type& val);
//	*/
//
//	vector<int> v1(5, 3);
//	vector<int> v2(3, 5);
//
//	//assign会将之前的数据清空，只保留当前赋值的数据，无论size大小是变大还是变小
//	//assign如果让size变小，capacity不会发生变化
//	//用10个6给v1赋值
//	v1.assign(10, 6);
//	//用两个1024给v2赋值
//	v2.assign(2, 1024);
//
//	////将v2下标从[begin,end)处的所有元素赋值给v1
//	//v1.assign(v2.begin(), v2.end());
//
//	//将v1下标从[begin,end)处的所有元素赋值给v2
//	v2.assign(v1.begin(), v1.end());
//}

//void test()
//{
//	vector<int> v1;
//	cout << v1.size() << endl;
//	cout << v1.capacity() << endl;
//
//	vector<int> v2(6, 6);
//	for (int i = 0; i < v2.size(); ++i)
//		v2[i] += i;
//
//	
//
//	//push_back尾插
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//	v1.push_back(6);
//
//	//pop_back：尾删
//	v1.pop_back();
//	v1.pop_back();
//
//
//	/*
//
//	insert的插入位置都是迭代器，从要插入的位置开始所有元素向后移动
//	iterator insert (iterator position, const value_type& val);
//
//    void insert (iterator position, size_type n, const value_type& val);
//
//	template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last);
//	*/
//
//	//从起始位置的下一个位置插入1024
//	v1.insert(++v1.begin(), 1024);
//
//	//从最后一个元素的下一个位置处插入4个512
//	v1.insert(v1.end(), 4, 512);
//	int* pos = v1.data();
//
//	//v2:6  7 8 9 10 11
//	//从v1的起始位置的下一个位置插入v2的第二个位置到倒数第二个位置的所有元素
//	//注意C++的操作区间是左闭右开
//	v1.insert(++v1.begin(), ++v2.begin(), --v2.end());
//}

//void test()
//{
//	vector<int> v1(5, 1);
//
//	//vector可以通过用[]来进行值的修改
//	v1[0] = 1024;
//	v1[4] = pow(2,5);
//	cout << v1.front() << endl;
//	cout << v1.back() << endl;
//
//	const vector<char> v2(3, 'a');
//
//	//v2[0] = 'b';    error:不能对const类型的变量重新赋值
//	for (auto& e : v2)
//		cout << e << " ";
//	cout << endl;
//
//	vector<char>::const_iterator it = v2.begin();
//	while (it != v2.end())
//	{
//		cout << *it << " ";
//		//*it = 'x';    error：const类型的变量不能修改值
//		it++;
//	}
//	cout << endl;
//
//
//	//at也可以进行赋值操作
//	v1.at(1) = 199;
//
//	//通过data方法可以得到vector首元素的地址，通过对地址进行操作，使用这个vector内的元素
//	int* p_v1 = v1.data();
//
//	p_v1[0] = 1111;
//	p_v1[1] = 2222;
//	p_v1[2] = 3333;
//	p_v1[3] = 4444;
//	p_v1[4] = 6666;
//
//	cout << p_v1[0] << endl;
//	cout << p_v1[1] << endl;
//	cout << p_v1[2] << endl;
//	cout << p_v1[3] << endl;
//	cout << p_v1[4] << endl;
//
//
//}

//struct A{
//public:
//	A(int a = 1, int b = 2)
//		:_a(a)
//		, _b(b)
//	{
//
//	}
//private:
//	int _a;
//	int _b;
//};
//void test()
//{
//	vector<int> v1(4, 66);
//
//	vector<char> v2(5, 'a');
//
//	vector<double> v3(3, 1.021);
//
//	vector<A> v4(5,A(6,6));
//
//	//v1.reserve(10);
//
//	////reserve只能增加容量，不能减小容量
//	//v1.reserve(5);
//
//	////resize：对于基本类型，如果不给定填充的值，就会以对应类型的0值来填充
//	//v1.resize(15);
//
//	//v2.resize(10);
//
//	//v3.resize(5);
//
//	////自定义类型在改变有效元素的个数时，回调用自身的构造函数对新的成员进行初始化
//	//v4.resize(12);
//
//
//	//resize可以减少有效元素的个数
//	v1.resize(1);
//
//
//	//resize可以指定填充值
//	v1.resize(5, 99);
//
//	v1.reserve(20);
//
//	//shrink_to_fit可以让当前的容量调整到匹配size的大小
//	v1.shrink_to_fit();
//
//}

//void test()
//{
//	//max_size:   32位环境下: 2^32个字节
//	//int:四个字节   max_size:2^30
//	//char:一个字节  max_size:2^32
//	//double:八个字节  max_size:2^29
//	//float:四个字节  max_size:2^30
//	vector<double> v1(5, 2.121);
//
//	vector<int> v2(10, 2);
//
//	vector<float> v3;
//
//	cout << "size:" << v1.size() << endl;
//	cout << "capacity:" << v1.capacity() << endl;
//	cout << "max_size:" << v1.max_size()<< endl;    //why?
//	cout << "max_size:" << v2.max_size() << endl;    //why?
//
//	//empty：空的话返回1，非空返回0
//	cout << " Is v1 empty?" << v1.empty() << endl;
//	cout << " Is v2 empty?" << v2.empty() << endl;
//	cout << " Is v3 empty?" << v3.empty() << endl;
//}

//void test()
//{
//	//迭代器的使用
//	vector<int> v1(10, 6);
//	vector<int>::iterator it = v1.begin();
//	int i = 0;
// 	while (it != v1.end())
//	{
//		cout << *it << " ";
//		*it += i;
//		it++;
//		i++;
//	}
//	cout << endl;
//	vector<int>::reverse_iterator it2 = v1.rbegin();
//	while (it2 != v1.rend())
//	{
//		cout << *it2 << " ";
//		it2++;
//	}
//
//	cout << endl;
//
//	//只读迭代器
//	const vector<int> v2(12, 0);
//
//	vector<int>::const_iterator it3 = v2.begin();
//	while (it3 != v2.end())
//	{
//		cout << *it3 << " ";
//		//*it3 = 521;    const类型不能修改
//		it3++;
//	}
//	cout << endl;
//
//	const vector<int> v3(10, 1);
//
//	vector<int>::const_reverse_iterator it4 = v3.rbegin();
//	while (it4 != v3.rend())
//	{
//		cout << *it4 << " ";
//		//*it4 = 121;    error 
//		it4++;
//	}
//	cout << endl;
//
//}

//void test()
//{
//	//vector赋值运算符的使用
//	vector<char> ch1(1,'A');
//	vector<char> ch2(1,'a');
//
//	ch1 = ch2;
//
//}

//void test()
//{
//	//声明一个空的vector，没有任何有效元素
//	vector<int> v1;
//	for (auto& e : v1)
//	{
//		cout << e << " ";
//	}
//	cout << "end" << endl;
//
//	//声明一个有10个有效元素的vector,默认初始值都是对应类型的零值
//	vector<int> v5(10);
//
//	//声明一个指定数量和初始值的vector
//	vector<int> v2(4, 5);
//	for (auto& e : v2)
//	{
//		cout << e << " ";
//		e += 10;
//	}
//	cout << "end" << endl;
//
//	//使用迭代器进行声明
//	vector<int> v3(++v2.begin(), v2.end());
//	for (auto& e : v3)
//	{
//		cout << e << " ";
//	}
//	cout << "end" << endl;
//
//	//用一个已经存在的vector对象来声明
//	vector<int> v4(v3);
//	for (auto& e : v4)
//	{
//		cout << e << " ";
//	}
//	cout << "end" << endl;
//}

//int main()
//{
//	test();
//	return 0;
//}