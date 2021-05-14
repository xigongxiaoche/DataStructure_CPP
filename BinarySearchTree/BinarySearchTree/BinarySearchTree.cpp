#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;

//节点
template<class T>
struct BNode{
	T _data;
	typedef BNode<T> Node;
	Node* _left;
	Node* _right;
	BNode(T data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

//搜索二叉树:节点中的数据值唯一
//当前的二叉树，左子树的值小于根结点的值，根结点的值小于右子树的值
//不支持修改，修改会改变树的结构
template<class T>
class BTree{
public:
	typedef BNode<T> Node;
	BTree()
		:_root(nullptr)
	{}

	void destroy(Node* root)
	{
		if (root)
		{
			destroy(root->_left);
			destroy(root->_right);
			//cout << "destroy " << root->_data << endl;
			delete root;
		}
	}

	~BTree()
	{
		if (_root)
		{
			destroy(_root);
			_root = nullptr;
		}
	}
	
	//拷贝树的数据和结构
	Node* copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;

		Node* newNode = new Node(root->_data);
		newNode->_left = copy(root->_left);
		newNode->_right = copy(root->_right);

		return newNode;
	}

	BTree(const BTree<T>& tree)
		:_root(copy(tree._root))
	{}

	//查找
	Node* find(const T& val)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_data == val)
				return cur;
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		return cur;
	}

	//插入
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;//记录父亲节点

		//找到合适的插入位置
		while (cur)
		{
			//更新父亲节点
			parent = cur;
			//二叉搜索树中节点唯一
			if (cur->_data == val)
				return false;
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		cur = new Node(val);
		//判断插入节点的位置是在父节点的左边还是右边
		if (parent->_data > val)
			parent->_left = cur;
		else
			parent->_right = cur;

		return true;
	}

	//中序遍历
	void inOrder()
	{
		_inOrder(_root);
		cout << endl;
	}

	void _inOrder(Node* root)
	{
		if (root)
		{
			_inOrder(root->_left);
			cout << root->_data << " ";
			_inOrder(root->_right);
		}
	}

	//删除
	bool erase(const T& val)
	{
		//查找
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (cur->_data == val)
				break;

			parent = cur;//更新父亲节点
			if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//判断是否找到了要删除的节点
		if (cur == nullptr)
			return false;

		//删除
		//1.删除的是叶子节点
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			//判断是否为根节点
			if (cur == _root)
			{
				_root = nullptr;
			}
			else
			{
				//判断需要删除的节点在父节点的哪一边
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}

			//删除节点
			delete cur;
		}
		else if(cur->_left == nullptr)//非叶子节点，左子树为空
		{
			//删除的是根节点
			if (cur == _root)
			{
				_root = cur->_right;
			}
			else
			{
				//判断需要删除的节点在父节点的哪一边
				//并让父亲节点和当前节点的右子树相连
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			

			delete cur;
		}
		else if (cur->_right == nullptr)  //非叶子节点，右子树为空
		{
			//删除的是根节点
			if (cur == _root)
			{
				_root = cur->_left;
			}
			else
			{
				//判断需要删除的节点在父节点的哪一边
				//并让父亲节点和当前节点的右子树相连
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else 
					parent->_right = cur->_left;
			}

			delete cur;
		}
		else  
		{
			//左右子树都存在
			//假设找左子树的最右节点(也可以找右子树的最左节点)
			Node* leftRightMost = cur->_left;//左子树的根节点
			parent = cur;

			//1.查找左子树的最右节点
			while (leftRightMost->_right)
			{
				parent = leftRightMost;
				leftRightMost = leftRightMost->_right;
			}

			//2.交换
			swap(cur->_data, leftRightMost->_data);

			//3.删除最右节点
			if (parent->_left == leftRightMost)
			{
				parent->_left = leftRightMost->_left;
			}
			else
			{
				parent->_right = leftRightMost->_left;
			}

			delete leftRightMost;
		}

		return true;
	}
private:
	Node* _root;
};

void test()
{
	BTree<int> tree;

	tree.insert(45);
	tree.insert(23);
	tree.insert(56);
	tree.insert(12);
	tree.insert(34);
	tree.insert(50);
	tree.insert(58);
	tree.insert(1); 
	tree.insert(54);
	tree.insert(123);
	
	tree.inOrder();
	cout << "********** delete 1(leaf) ****************" << endl;
	tree.erase(1);
	tree.inOrder();

	cout << "************ delete 50(mid) ********************" << endl;
	tree.erase(50);
	tree.inOrder();
	cout << "************* delete 45(root) *****************" << endl;
	tree.erase(45);
	tree.inOrder();

	
}

////二叉树析构，拷贝构造测试
//void test()
//{
//	srand(time(NULL));
//	BTree<int> tree;
//	
//	for (int i = 0; i < 10; ++i)
//	{
//		int num = rand() % 100 + 1;
//		tree.insert(num);
//	}
//	tree.inOrder();
//
//	BTree<int> copy(tree);
//	copy.inOrder();
//	
//}

////二叉树插入，查找,中序遍历测试
//void test()
//{
//	srand(time(NULL));
//	BTree<int> tree;
//	for (int i = 0; i < 10; ++i)
//	{
//		int num = rand() % 100 + 1;
//		tree.insert(num);
//	}
//
//	BNode<int>* ret = tree.find(1);
//	if (ret)
//		cout << "找到了,地址为"<<&ret->_data << endl;
//	else
//		cout << "树中没有这个值对应的节点" << endl;
//
//	tree.inOrder();
//}



int main()
{
	test();
	return 0;
}