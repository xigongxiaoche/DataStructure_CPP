#include<iostream>
#include<stack>
#include<utility>
using namespace std;

//红黑树
enum COLOR{
	BLACK,
	RED
};

//节点
template<class K,class V>
struct RBNode
{
	RBNode<K, V>*  _parent;
	RBNode<K, V>*  _left;
	RBNode<K, V>* _right;
	pair<K, V> _kv;//数据为键值对
	COLOR _color;
	//bool _color;//STL的实现
	RBNode(const pair<K, V> kv=pair<K,V>())
		:_parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
		, _kv(kv)
		, _color(RED)
	{}
};

template<class K,class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;
	RBTree()
		:_header(new Node)
	{
		//带头的空的红黑树
		_header->_left = _header->_right = _header;
	}
	/*
		parent  
		         subR
			  subRL
		左旋后：
		         subR
	   parent
	        subRL
	*/
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		//判断根
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (parent == pparent->_left)
				pparent->_left = subR;
			else
				pparent->_right = subR;
			subR->_parent = pparent;
		}
		parent->_parent = subR;
	}
	/*
			   parent 
		subL
		   subLR
		右旋后：
		   subL
		       parent
			 subLR
	*/
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (parent == pparent->_left)
				pparent->_left = subL;
			else
				pparent->_right = subL;
			subL->_parent = pparent;
		}
		parent->_parent = subL;
	}

	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;

		return cur;
	}

	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;

		return cur;
	}

	bool insert(const pair<K,V>& kv)
	{
		//1.搜索树的插入
		//a.空树
		if (_header->_parent == nullptr)
		{
			//创建根节点
			Node* root = new Node(kv);
			//根节点颜色为黑色
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = _header->_right = root;
			return true;
		}

		//b.非空树
		Node* parent = nullptr;
		//从根节点开始搜索
		Node* cur = _header->_parent;
		while (cur)
		{
			parent = cur;
			if (cur->_kv.first == kv.first)
				return false;//键值重复，插入失败
			else if (cur->_kv.first > kv.first)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//新插入结点的颜色为红色
		cur = new Node(kv);
		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//2.修改颜色或者调整结构，判断是否有红色连续的节点
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			//当前节点不为根，并且当前节点的父节点是红色
			parent = cur->_parent;
			Node* gfather = parent->_parent;//父节点颜色为红色，说明父节点不是根节点，存在祖父节点
			if (gfather->_left == parent)
			{
				Node* uncle = gfather->_right;
				//uncle节点存在，并且颜色是红色的
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//继续更新
					cur = gfather;
				}
				else
				{
					//cout << "Rotate---------" << endl;
					//判断是否是双旋的场景
					if (parent->_right == cur)
					{
						RotateL(parent);//左旋
						swap(parent, cur);//交换parent和cur的指向，退化为右旋的场景
					}
					//uncle节点不存在或者uncle节点存在，但是颜色为黑色
					RotateR(gfather);//右旋----左边的左边是连续的红色
					//修改颜色
					parent->_color = BLACK;
					gfather->_color = RED;
					break;//调整结束
				}

			}
			else
			{
				Node* uncle = gfather->_left;
				//uncle节点存在，并且颜色是红色的
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//继续更新
					cur = gfather;
				}
				else
				{
					//cout << "Rotate---------" << endl;
					//判断是否是双旋的场景
					if (parent->_left == cur)
					{
						RotateR(parent);//右旋
						swap(parent, cur);//交换parent和cur的指向，退化为左旋的场景
					}
					//uncle节点不存在或者uncle节点存在，但是颜色为黑色
					RotateL(gfather);//左旋----右边的右边是连续的红色
					//修改颜色
					parent->_color = BLACK;
					gfather->_color = RED;
					break;//调整结束
				}
			}
		}

		//3.将根节点颜色置为黑色
		_header->_parent->_color = BLACK;
		//4.更新_header的左右指向
		_header->_left = leftMost();
		_header->_right = rightMost();

		return true;
	}


	void inorder()
	{
		Node* cur = _header->_parent;
		stack<Node*> st;
		while (cur || !st.empty())
		{
			while (cur)
			{
				st.push(cur);
				cur = cur->_left;
			}

			Node* top = st.top();
			cout << top->_kv.first << " ";

			st.pop();
			cur = top->_right;
		}
		cout << endl;
	}

	/*
		红黑树的三个性质：
		1.根是黑色；
		2.每条路径黑色个数相同；
		3.红色不能连续；
	*/
	bool isValidTree()
	{
		if (_header->_parent == nullptr)
			return true;//空树也默认为红黑树

		Node* root = _header->_parent;
		if (root->_color == RED)
			return false;

		int bCount = 0;
		Node* cur = root;
		while (cur)
		{
			if (cur->_color == BLACK)
				bCount++;
			cur = cur->_left;
		}

		//遍历每一条路径的黑色节点数,并检查是否有红色节点连续的情况
		int curCount = 0;
		return isBalance(root, bCount, curCount);
	}

	bool isBalance(Node* root,int& bCount,int curCount)
	{
		//当节点走到空处，说明一条路径遍历结束
		if (root == nullptr)
		{
			//判断黑色节点个数是否相同
			if (bCount == curCount)
				return true;
			else
				return false;
		}

		if (root->_color == BLACK)
			curCount++;//累加黑色节点个数

		//存在红色连续，返回false
		if (root->_parent && root->_color == RED
			&& root->_parent->_color == RED)
		{
			cout << "false data:" << root->_kv.first << endl;
			return false;
		}

		return isBalance(root->_left, bCount, curCount)
			&& isBalance(root->_right, bCount, curCount);
	}
private:
	Node* _header;
};

//void test()
//{
//	RBTree<int, int> tree;
//	tree.insert(make_pair(10, 2));
//	tree.insert(make_pair(15, 2));
//	tree.insert(make_pair(5, 2));
//	tree.insert(make_pair(2, 2));
//	tree.inorder();
//}

void test()
{
	RBTree<int, int> tree;
	int n;
	cin >> n;
	for (int i = n; i > 0; --i)
		tree.insert(make_pair(i, i));
	tree.inorder();
	cout << "Is it a valid RBTree ? "<< tree.isValidTree() << endl;
}
int main()
{
	test();
	return 0;
}