//#include<iostream>
//#include<time.h>
//#include<algorithm>
//#include<string>
//using namespace std;
//
////键值对节点
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
////搜索二叉树:节点中的数据值唯一
////当前的二叉树，左子树的值小于根结点的值，根结点的值小于右子树的值
////不支持修改，修改会改变树的结构
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
//	//拷贝树的数据和结构
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
//	//查找
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
//	//插入
//	bool insert(const K& key,const V& value)
//	{
//		if (_root == nullptr)
//		{
//			_root = new Node(key,value);
//			return true;
//		}
//
//		Node* cur = _root;
//		Node* parent = nullptr;//记录父亲节点
//
//		//找到合适的插入位置
//		while (cur)
//		{
//			//更新父亲节点
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
//		//判断插入节点的位置是在父节点的左边还是右边
//		if (parent->_key >key)
//			parent->_left = cur;
//		else
//			parent->_right = cur;
//
//		return true;
//	}
//
//	//中序遍历
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
//	//删除
//	bool erase(const K& val)
//	{
//		//查找
//		Node* cur = _root;
//		Node* parent = nullptr;
//
//		while (cur)
//		{
//			if (cur->_key == val)
//				break;
//
//			parent = cur;//更新父亲节点
//			if (cur->_key > val)
//				cur = cur->_left;
//			else
//				cur = cur->_right;
//		}
//
//		//判断是否找到了要删除的节点
//		if (cur == nullptr)
//			return false;
//
//		//删除
//		//1.删除的是叶子节点
//		if (cur->_left == nullptr && cur->_right == nullptr)
//		{
//			//判断是否为根节点
//			if (cur == _root)
//			{
//				_root = nullptr;
//			}
//			else
//			{
//				//判断需要删除的节点在父节点的哪一边
//				if (parent->_left == cur)
//					parent->_left = nullptr;
//				else
//					parent->_right = nullptr;
//			}
//
//			//删除节点
//			delete cur;
//		}
//		else if (cur->_left == nullptr)//非叶子节点，左子树为空
//		{
//			//删除的是根节点
//			if (cur == _root)
//			{
//				_root = cur->_right;
//			}
//			else
//			{
//				//判断需要删除的节点在父节点的哪一边
//				//并让父亲节点和当前节点的右子树相连
//				if (parent->_left == cur)
//					parent->_left = cur->_right;
//				else
//					parent->_right = cur->_right;
//			}
//
//
//			delete cur;
//		}
//		else if (cur->_right == nullptr)  //非叶子节点，右子树为空
//		{
//			//删除的是根节点
//			if (cur == _root)
//			{
//				_root = cur->_left;
//			}
//			else
//			{
//				//判断需要删除的节点在父节点的哪一边
//				//并让父亲节点和当前节点的右子树相连
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
//			//左右子树都存在
//			//假设找左子树的最右节点(也可以找右子树的最左节点)
//			Node* leftRightMost = cur->_left;//左子树的根节点
//			parent = cur;
//
//			//1.查找左子树的最右节点
//			while (leftRightMost->_right)
//			{
//				parent = leftRightMost;
//				leftRightMost = leftRightMost->_right;
//			}
//
//			//2.交换
//			swap(cur->_key, leftRightMost->_key);
//			swap(cur->_value, leftRightMost->_value);
//
//			//3.删除最右节点
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
//	string strs[] = { "苹果", "西瓜", "苹果", "樱桃", "苹果", "樱桃", "苹果", "樱桃", "苹果" };
//	// 统计水果出现的次数
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
//	cout << "水果出现次数统计：" << endl;
//	countTree.inOrder();
//
//	BTree<string, string> dict;
//	dict.insert("preOrder", "先序");
//	dict.insert("inOrder", "中序");
//	dict.insert("postOrder", "后序");
//	dict.insert("seqlist", "顺序表");
//	dict.insert("linkedList", "链表");
//	dict.insert("stack", "栈");
//	dict.insert("queue", "队列");
//	dict.insert("binaryTree", "二叉树");
//	cout << "\n\n\n\n\n\n\n";
//	cout << "--------------计算机专业名词字典-------------" << endl;
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
//			cout << "您要查找的单词不存在" << endl;
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