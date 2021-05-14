//#include<iostream>
//#include<time.h>
//#include<algorithm>
//#include<string>
//using namespace std;
//
////��ֵ�Խڵ�
//template<class K,class V>
//struct BNode{
//	K _key;
//	V _value;
//	typedef BNode<K,V> Node;
//	Node* _left;
//	Node* _right;
//	BNode(K key,V value)
//		:_key(key)
//		, _value(value)
//		, _left(nullptr)
//		, _right(nullptr)
//	{}
//};
//
////����������:�ڵ��е�����ֵΨһ
////��ǰ�Ķ���������������ֵС�ڸ�����ֵ��������ֵС����������ֵ
////��֧���޸ģ��޸Ļ�ı����Ľṹ
//template<class K,class V>
//class BTree{
//public:
//	typedef BNode<K,V> Node;
//	BTree()
//		:_root(nullptr)
//	{}
//
//	void destroy(Node* root)
//	{
//		if (root)
//		{
//			destroy(root->_left);
//			destroy(root->_right);
//			//cout << "destroy " << root->_data << endl;
//			delete root;
//		}
//	}
//
//	~BTree()
//	{
//		if (_root)
//		{
//			destroy(_root);
//			_root = nullptr;
//		}
//	}
//
//	//�����������ݺͽṹ
//	Node* copy(Node* root)
//	{
//		if (root == nullptr)
//			return nullptr;
//
//		Node* newNode = new Node(root->_data);
//		newNode->_left = copy(root->_left);
//		newNode->_right = copy(root->_right);
//
//		return newNode;
//	}
//
//	BTree(const BTree<K,V>& tree)
//		:_root(copy(tree._root))
//	{}
//
//	//����
//	Node* find(const K& val)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur->_key == val)
//				return cur;
//			else if (cur->_key > val)
//				cur = cur->_left;
//			else
//				cur = cur->_right;
//		}
//
//		return cur;
//	}
//
//	//����
//	bool insert(const K& key,const V& value)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(key,value);
//			return true;
//		}
//
//		Node* cur = _root;
//		Node* parent = nullptr;//��¼���׽ڵ�
//
//		//�ҵ����ʵĲ���λ��
//		while (cur)
//		{
//			//���¸��׽ڵ�
//			parent = cur;
//			if (cur->_key == key)
//				return false;
//			else if (cur->_key > key)
//				cur = cur->_left;
//			else
//				cur = cur->_right;
//		}
//
//		cur = new Node(key,value);
//		//�жϲ���ڵ��λ�����ڸ��ڵ����߻����ұ�
//		if (parent->_key >key)
//			parent->_left = cur;
//		else
//			parent->_right = cur;
//
//		return true;
//	}
//
//	//�������
//	void inOrder()
//	{
//		_inOrder(_root);
//		cout << endl;
//	}
//
//	void _inOrder(Node* root)
//	{
//		if (root)
//		{
//			_inOrder(root->_left);
//			cout << root->_key << "---->"<<root->_value;
//			_inOrder(root->_right);
//		}
//	}
//
//	//ɾ��
//	bool erase(const K& val)
//	{
//		//����
//		Node* cur = _root;
//		Node* parent = nullptr;
//
//		while (cur)
//		{
//			if (cur->_key == val)
//				break;
//
//			parent = cur;//���¸��׽ڵ�
//			if (cur->_key > val)
//				cur = cur->_left;
//			else
//				cur = cur->_right;
//		}
//
//		//�ж��Ƿ��ҵ���Ҫɾ���Ľڵ�
//		if (cur == nullptr)
//			return false;
//
//		//ɾ��
//		//1.ɾ������Ҷ�ӽڵ�
//		if (cur->_left == nullptr && cur->_right == nullptr)
//		{
//			//�ж��Ƿ�Ϊ���ڵ�
//			if (cur == _root)
//			{
//				_root = nullptr;
//			}
//			else
//			{
//				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
//				if (parent->_left == cur)
//					parent->_left = nullptr;
//				else
//					parent->_right = nullptr;
//			}
//
//			//ɾ���ڵ�
//			delete cur;
//		}
//		else if (cur->_left == nullptr)//��Ҷ�ӽڵ㣬������Ϊ��
//		{
//			//ɾ�����Ǹ��ڵ�
//			if (cur == _root)
//			{
//				_root = cur->_right;
//			}
//			else
//			{
//				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
//				//���ø��׽ڵ�͵�ǰ�ڵ������������
//				if (parent->_left == cur)
//					parent->_left = cur->_right;
//				else
//					parent->_right = cur->_right;
//			}
//
//
//			delete cur;
//		}
//		else if (cur->_right == nullptr)  //��Ҷ�ӽڵ㣬������Ϊ��
//		{
//			//ɾ�����Ǹ��ڵ�
//			if (cur == _root)
//			{
//				_root = cur->_left;
//			}
//			else
//			{
//				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
//				//���ø��׽ڵ�͵�ǰ�ڵ������������
//				if (parent->_left == cur)
//					parent->_left = cur->_left;
//				else
//					parent->_right = cur->_left;
//			}
//
//			delete cur;
//		}
//		else
//		{
//			//��������������
//			//�����������������ҽڵ�(Ҳ������������������ڵ�)
//			Node* leftRightMost = cur->_left;//�������ĸ��ڵ�
//			parent = cur;
//
//			//1.���������������ҽڵ�
//			while (leftRightMost->_right)
//			{
//				parent = leftRightMost;
//				leftRightMost = leftRightMost->_right;
//			}
//
//			//2.����
//			swap(cur->_key, leftRightMost->_key);
//			swap(cur->_value, leftRightMost->_value);
//
//			//3.ɾ�����ҽڵ�
//			if (parent->_left == leftRightMost)
//			{
//				parent->_left = leftRightMost->_left;
//			}
//			else
//			{
//				parent->_right = leftRightMost->_left;
//			}
//
//			delete leftRightMost;
//		}
//
//		return true;
//	}
//private:
//	Node* _root;
//};
//
//void test()
//{
//	string strs[] = { "ƻ��", "����", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��", "ӣ��", "ƻ��" };
//	// ͳ��ˮ�����ֵĴ���
//	BTree<string, int> countTree;
//	for (auto str : strs)
//	{
//		auto ret = countTree.find(str);
//		if (ret == NULL)
//		{
//			countTree.insert(str, 1);
//		}
//		else
//		{
//			ret->_value++;
//		}
//	}
//	cout << "ˮ�����ִ���ͳ�ƣ�" << endl;
//	countTree.inOrder();
//
//	BTree<string, string> dict;
//	dict.insert("preOrder", "����");
//	dict.insert("inOrder", "����");
//	dict.insert("postOrder", "����");
//	dict.insert("seqlist", "˳���");
//	dict.insert("linkedList", "����");
//	dict.insert("stack", "ջ");
//	dict.insert("queue", "����");
//	dict.insert("binaryTree", "������");
//	cout << "\n\n\n\n\n\n\n";
//	cout << "--------------�����רҵ�����ֵ�-------------" << endl;
//	string str;
//	while (cin >> str )
//	{
//		auto ret = dict.find(str);
//		if (ret)
//		{
//			cout << str << ":" << ret->_value << endl;
//		}
//		else
//		{
//			cout << "��Ҫ���ҵĵ��ʲ�����" << endl;
//		}
//	}
//
//	
//}
//
//
//int main()
//{
//	test();
//	return 0;
//}