//#include<iostream>
//#include<vector>
//#include<math.h>
//
//using namespace std;
//
//void test()
//{
//	//at��operator������
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
//	//erase�ķ���ֵΪɾ����Ԫ�غ����һ��Ԫ�ص�λ��
//	it = v1.erase(++v1.begin(),--v1.end());
//	cout << *it << endl;
//}

//void test()
//{
//	//�����������
//	int numRows;
//	cout << "������Ҫ���ɵ�������ǵ�����:";
//	cin >> numRows;
//
//	//������numRows��Ԫ�ص�vector
//	vector<vector<int>> A(numRows);
//
//	//Ϊvector�ڵ�ÿһ��Ԫ�ؿ��ٿռ�,����ʼ�����е�Ԫ��Ϊ1
//	int i, j;
//	for (i = 1; i <= numRows; ++i)
//	{
//		//ʹ��resize
//		A[i - 1].resize(i,1);
//	}
//
//
//	//�ӵ����п�ʼ�����м��ֵ
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
//	//������ʧЧ���������
//	//���1.����ʱ��Ϊԭ����ָ�ռ䱻�ͷ�
//	//���2.ɾ��Ԫ��ʱ��ɾ��֮ǰ��������ָ�Ŀռ䲻����
//
//	vector<int> v1(5, 6);
//
//	////���1��
//	//vector<int>::iterator it = v1.begin();
//	//v1.reserve(10);
//	////�������ٴ�ʹ��֮ǰ����ĵ�����ʱ����Ϊ֮ǰ��������ָ�Ŀռ��Ѿ����ͷţ�
//	////���ڶԵ�������ָ�ռ�Ľ��в���ʱ�����Ƕ�һ��Ƿ��Ŀռ���в���������assertion failed
//	//while (it != v1.end())
//	//{
//	//	cout << *it << endl;
//	//	it++;
//	//}
//
//
//	//���2��
//	//����assertion failed
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
//	//��vector����һ���������洢9*9�˷��ھ���
//
//	//����һ����9��Ԫ�ص�vector,ÿ��Ԫ������һ����9��Ԫ����ɵ�vector
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
//	//����һ�������Ԫ�ص�vector,ÿ��Ԫ������һ�������Ԫ����ɵ�vector
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
//	//vector�ǳ�Ա����swap
//	vector<int> v1{ 1, 1, 1, 1, 1 };
//	vector<int> v2(9, 1024);
//	v1.swap(v2);
//}

//void test()
//{
//	//vector�ǳ�Ա��������ϵ���������  
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
//	//��size��Ϊ0�����֮ǰ������
//	//capacity���ֲ���
//	vector<int> v1 = { 1, 2, 3, 45 };
//	v1.clear();
//}
//void test()
//{
//	//void swap (vector& x)
//	//��������vetcor�е�����
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
//	v1.erase(++v1.begin());		//ɾ���ڶ���Ԫ��
//	v1.erase(--v1.end());		//ɾ�����һ��λ�õ�Ԫ��
//
//	//iterator erase (iterator first, iterator last);
//	v1.erase(++v1.begin(), v1.end());	//ɾ���ڶ���Ԫ�ؼ���������е�Ԫ��
//}

//void test()
//{
//	vector<int> v1 = { 1, 2, 3, 4, 5, 6, 7 };
//
//	int arr[] = { 8, 9, 10, 11, 12, 13, 14 };
//	v1.emplace(v1.begin(), 0);    //��ʼλ�ò��룬�൱��push_front
//	v1.emplace(v1.end(),1024);    //����λ�ò��룬�൱��push_back
//	v1.emplace(++v1.begin(), 512);		//�ӵ�һ��Ԫ�ص���һ��λ�ò���512
//
//	////emplace�ڶ�����������Ҫ�����ֵ��ֻ����һ��ֵ
//	//v1.emplace(v1.begin(), arr);
//
//	//emplace_back�� β��
//	vector<int> v2 = { 0, 1, 2 };
//	v2.emplace_back(3);
//	v2.emplace_back(4);
//	v2.emplace_back(5);
//}

//void test()
//{
//	//assign��Ϊ�������������ݣ��滻�䵱ǰ���ݣ�����Ӧ���޸����С
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
//	//assign�Ὣ֮ǰ��������գ�ֻ������ǰ��ֵ�����ݣ�����size��С�Ǳ���Ǳ�С
//	//assign�����size��С��capacity���ᷢ���仯
//	//��10��6��v1��ֵ
//	v1.assign(10, 6);
//	//������1024��v2��ֵ
//	v2.assign(2, 1024);
//
//	////��v2�±��[begin,end)��������Ԫ�ظ�ֵ��v1
//	//v1.assign(v2.begin(), v2.end());
//
//	//��v1�±��[begin,end)��������Ԫ�ظ�ֵ��v2
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
//	//push_backβ��
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//	v1.push_back(6);
//
//	//pop_back��βɾ
//	v1.pop_back();
//	v1.pop_back();
//
//
//	/*
//
//	insert�Ĳ���λ�ö��ǵ���������Ҫ�����λ�ÿ�ʼ����Ԫ������ƶ�
//	iterator insert (iterator position, const value_type& val);
//
//    void insert (iterator position, size_type n, const value_type& val);
//
//	template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator last);
//	*/
//
//	//����ʼλ�õ���һ��λ�ò���1024
//	v1.insert(++v1.begin(), 1024);
//
//	//�����һ��Ԫ�ص���һ��λ�ô�����4��512
//	v1.insert(v1.end(), 4, 512);
//	int* pos = v1.data();
//
//	//v2:6  7 8 9 10 11
//	//��v1����ʼλ�õ���һ��λ�ò���v2�ĵڶ���λ�õ������ڶ���λ�õ�����Ԫ��
//	//ע��C++�Ĳ�������������ҿ�
//	v1.insert(++v1.begin(), ++v2.begin(), --v2.end());
//}

//void test()
//{
//	vector<int> v1(5, 1);
//
//	//vector����ͨ����[]������ֵ���޸�
//	v1[0] = 1024;
//	v1[4] = pow(2,5);
//	cout << v1.front() << endl;
//	cout << v1.back() << endl;
//
//	const vector<char> v2(3, 'a');
//
//	//v2[0] = 'b';    error:���ܶ�const���͵ı������¸�ֵ
//	for (auto& e : v2)
//		cout << e << " ";
//	cout << endl;
//
//	vector<char>::const_iterator it = v2.begin();
//	while (it != v2.end())
//	{
//		cout << *it << " ";
//		//*it = 'x';    error��const���͵ı��������޸�ֵ
//		it++;
//	}
//	cout << endl;
//
//
//	//atҲ���Խ��и�ֵ����
//	v1.at(1) = 199;
//
//	//ͨ��data�������Եõ�vector��Ԫ�صĵ�ַ��ͨ���Ե�ַ���в�����ʹ�����vector�ڵ�Ԫ��
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
//	////reserveֻ���������������ܼ�С����
//	//v1.reserve(5);
//
//	////resize�����ڻ������ͣ��������������ֵ���ͻ��Զ�Ӧ���͵�0ֵ�����
//	//v1.resize(15);
//
//	//v2.resize(10);
//
//	//v3.resize(5);
//
//	////�Զ��������ڸı���ЧԪ�صĸ���ʱ���ص�������Ĺ��캯�����µĳ�Ա���г�ʼ��
//	//v4.resize(12);
//
//
//	//resize���Լ�����ЧԪ�صĸ���
//	v1.resize(1);
//
//
//	//resize����ָ�����ֵ
//	v1.resize(5, 99);
//
//	v1.reserve(20);
//
//	//shrink_to_fit�����õ�ǰ������������ƥ��size�Ĵ�С
//	v1.shrink_to_fit();
//
//}

//void test()
//{
//	//max_size:   32λ������: 2^32���ֽ�
//	//int:�ĸ��ֽ�   max_size:2^30
//	//char:һ���ֽ�  max_size:2^32
//	//double:�˸��ֽ�  max_size:2^29
//	//float:�ĸ��ֽ�  max_size:2^30
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
//	//empty���յĻ�����1���ǿշ���0
//	cout << " Is v1 empty?" << v1.empty() << endl;
//	cout << " Is v2 empty?" << v2.empty() << endl;
//	cout << " Is v3 empty?" << v3.empty() << endl;
//}

//void test()
//{
//	//��������ʹ��
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
//	//ֻ��������
//	const vector<int> v2(12, 0);
//
//	vector<int>::const_iterator it3 = v2.begin();
//	while (it3 != v2.end())
//	{
//		cout << *it3 << " ";
//		//*it3 = 521;    const���Ͳ����޸�
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
//	//vector��ֵ�������ʹ��
//	vector<char> ch1(1,'A');
//	vector<char> ch2(1,'a');
//
//	ch1 = ch2;
//
//}

//void test()
//{
//	//����һ���յ�vector��û���κ���ЧԪ��
//	vector<int> v1;
//	for (auto& e : v1)
//	{
//		cout << e << " ";
//	}
//	cout << "end" << endl;
//
//	//����һ����10����ЧԪ�ص�vector,Ĭ�ϳ�ʼֵ���Ƕ�Ӧ���͵���ֵ
//	vector<int> v5(10);
//
//	//����һ��ָ�������ͳ�ʼֵ��vector
//	vector<int> v2(4, 5);
//	for (auto& e : v2)
//	{
//		cout << e << " ";
//		e += 10;
//	}
//	cout << "end" << endl;
//
//	//ʹ�õ�������������
//	vector<int> v3(++v2.begin(), v2.end());
//	for (auto& e : v3)
//	{
//		cout << e << " ";
//	}
//	cout << "end" << endl;
//
//	//��һ���Ѿ����ڵ�vector����������
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