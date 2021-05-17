#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
/*
	ƽ���������ƽ�����ӵľ���ֵС�ڵ���1
*/
//�ڵ�
template<class T>
struct AVLNode{
	T _val;//�ڵ�洢������
	int _bf;//ƽ�����ӣ��������߶ȼ�ȥ�������߶�
	AVLNode<T>* _parent;//���ڵ�
	AVLNode<T>* _left;//����
	AVLNode<T>* _right;//�Һ���

	AVLNode(const T& val)
		:_val(val)
		, _bf(0)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

//AVL��
template<class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;
	bool insert(const T& val)
	{
		//1.����
		if (_root == nullptr)
		{
			//�������ڵ�
			_root = new Node(val);
			return true;
		}

		Node* parent = nullptr;//���ڵ�ĸ��ڵ��ʼ��Ϊ��
		Node* cur = _root;
		//���Ҳ���λ��
		while (cur)
		{
			parent = cur;
			if (cur->_val == val)
			{
				//ƽ��������ڵ�ֵΨһ������false
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
		//�����½ڵ㣬���ı�ָ��ָ��
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

		//2.����,��parent�ڵ㿪ʼ
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			if (parent->_bf == 0)     //parent�Ƚ϶̵������ĸ߶ȼ�1
			{
				//��������
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)//����ǰƽ������Ϊ0
			{
				//�������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				//��ߵ���߸�
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					//����
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					//�ұߵ��ұ߸ߣ�����
					RotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					//��ߵ��ұ߸�
					//cur subLR parent 
					Node* subLR = cur->_right;
					int bf = subLR->_bf;

					RotateL(cur);
					RotateR(parent);

					//����ƽ������
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
					//����subRL��bf
					Node* subRL = cur->_left;
					int bf = subRL->_bf;

					//�ұߵ���߸�
					RotateR(cur);
					RotateL(parent);

					//����ƽ������
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
	//����:��ߵ���߸�
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
		//�ж�parent�Ƿ�Ϊ���ڵ�
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
		subL->_bf = parent->_bf = 0;//����ƽ������
	}
	//parent
	//    subR
	//            subRL
	//��ת��
	//    subR
	//parent
	//        subRL
	//����������
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

		//�鿴ƽ�������Ƿ�����������ĸ߶Ȳ���һ��
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