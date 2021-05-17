#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
/*
	平衡二叉树的平衡因子的绝对值小于等于1
*/
//节点
template<class T>
struct AVLNode{
	T _val;//节点存储的数据
	int _bf;//平衡因子：右子树高度减去左子树高度
	AVLNode<T>* _parent;//父节点
	AVLNode<T>* _left;//左孩子
	AVLNode<T>* _right;//右孩子

	AVLNode(const T& val)
		:_val(val)
		, _bf(0)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

//AVL树
template<class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;
	bool insert(const T& val)
	{
		//1.插入
		if (_root == nullptr)
		{
			//创建根节点
			_root = new Node(val);
			return true;
		}

		Node* parent = nullptr;//根节点的父节点初始化为空
		Node* cur = _root;
		//查找插入位置
		while (cur)
		{
			parent = cur;
			if (cur->_val == val)
			{
				//平衡二叉树节点值唯一，返回false
				return false;
			}
			else if (cur->_val > val)
			{
				cur = cur->_left;
			}
			else
			{
				cur = cur->_right;
			}
		}
		//创建新节点，并改变指针指向
		cur = new Node(val);
		if (parent->_val > val)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//2.调整,从parent节点开始
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			if (parent->_bf == 0)     //parent比较短的子树的高度加1
			{
				//结束更新
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)//插入前平衡因子为0
			{
				//继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				//左边的左边高
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//右旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//右边的右边高，左旋
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//左边的右边高
					//cur subLR parent 
					Node* subLR = cur->_right;
					int bf = subLR->_bf;

					RotateL(cur);
					RotateR(parent);

					//修正平衡因子
					if (bf == 1)
					{
						parent->_bf = 0;
						cur->_bf = -1;
					}
					else if (bf == -1)
					{
						parent->_bf = 1;
						cur->_bf = 0;
					}
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					//保存subRL的bf
					Node* subRL = cur->_left;
					int bf = subRL->_bf;

					//右边的左边高
					RotateR(cur);
					RotateL(parent);

					//修正平衡因子
					if (bf == 1)
					{
						cur->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1)
					{
						cur->_bf = 1;
						parent->_bf = 0;
					}
				}
				break;
			}
		}
		return true;
	}
	
	//        parent
	//subL 
	//      subLR
	//右旋:左边的左边高
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR)
		{
			subLR->_parent = parent;
		}
		//判断parent是否为根节点
		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (pparent->_left == parent)
			{
				pparent->_left = subL;
			}
			else
			{
				pparent->_right = subL;
			}
			subL->_parent = pparent;
		}
		parent->_parent = subL;
		subL->_bf = parent->_bf = 0;//更新平衡因子
	}
	//parent
	//    subR
	//            subRL
	//旋转后
	//    subR
	//parent
	//        subRL
	//左旋：右右
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
		{
			subRL->_parent = parent;
		}

		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			Node* pparent = parent->_parent;

			if (pparent->_left == parent)
			{
				pparent->_left = subR;
			}
			else
			{
				pparent->_right = subR;
			}
			subR->_parent = pparent;

		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}

	void order()
	{
		_inorder(_root);
		cout << endl;
	}

	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}

	int height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int left = height(root->_left);
		int right = height(root->_right);

		return left > right ? left + 1 : right + 1;
	}

	bool _isBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		//查看平衡因子是否和左右子树的高度差相一致
		int left = height(root->_left);
		int right = height(root->_right);
		if (right - left != root->_bf)
		{
			cout << "Not balance!  Node: " << root->_val << "bf: "
				<< root->_bf << " height gap: " << right - left << endl;
			return false;
		}

		return abs(root->_bf) < 2
			&& _isBalance(root->_left)
			&& _isBalance(root->_right);
	}

	bool isBalance()
	{
		return _isBalance(_root);
	}
private:
	Node* _root = nullptr;
};


void test01()
{
	AVLTree<int> p;
	srand(time(nullptr));

	int num;
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		p.insert(rand() % 10000);
	}
	p.order();
	if (p.isBalance())
		cout << "balance" << endl;
	else
		cout << "not balance" << endl;
}
int main()
{
	test01();

	return 0;
}