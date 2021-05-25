#include<iostream>
#include<stack>
#include<utility>
using namespace std;

//�����
enum COLOR{
	BLACK,
	RED
};

//�ڵ�
template<class K,class V>
struct RBNode
{
	RBNode<K, V>*  _parent;
	RBNode<K, V>*  _left;
	RBNode<K, V>* _right;
	pair<K, V> _kv;//����Ϊ��ֵ��
	COLOR _color;
	//bool _color;//STL��ʵ��
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
		//��ͷ�Ŀյĺ����
		_header->_left = _header->_right = _header;
	}
	/*
		parent  
		         subR
			  subRL
		������
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
		//�жϸ�
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
		������
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
		//1.�������Ĳ���
		//a.����
		if (_header->_parent == nullptr)
		{
			//�������ڵ�
			Node* root = new Node(kv);
			//���ڵ���ɫΪ��ɫ
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = _header->_right = root;
			return true;
		}

		//b.�ǿ���
		Node* parent = nullptr;
		//�Ӹ��ڵ㿪ʼ����
		Node* cur = _header->_parent;
		while (cur)
		{
			parent = cur;
			if (cur->_kv.first == kv.first)
				return false;//��ֵ�ظ�������ʧ��
			else if (cur->_kv.first > kv.first)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		//�²��������ɫΪ��ɫ
		cur = new Node(kv);
		if (parent->_kv.first > cur->_kv.first)
			parent->_left = cur;
		else
			parent->_right = cur;
		cur->_parent = parent;

		//2.�޸���ɫ���ߵ����ṹ���ж��Ƿ��к�ɫ�����Ľڵ�
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			//��ǰ�ڵ㲻Ϊ�������ҵ�ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ
			parent = cur->_parent;
			Node* gfather = parent->_parent;//���ڵ���ɫΪ��ɫ��˵�����ڵ㲻�Ǹ��ڵ㣬�����游�ڵ�
			if (gfather->_left == parent)
			{
				Node* uncle = gfather->_right;
				//uncle�ڵ���ڣ�������ɫ�Ǻ�ɫ��
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//��������
					cur = gfather;
				}
				else
				{
					//cout << "Rotate---------" << endl;
					//�ж��Ƿ���˫���ĳ���
					if (parent->_right == cur)
					{
						RotateL(parent);//����
						swap(parent, cur);//����parent��cur��ָ���˻�Ϊ�����ĳ���
					}
					//uncle�ڵ㲻���ڻ���uncle�ڵ���ڣ�������ɫΪ��ɫ
					RotateR(gfather);//����----��ߵ�����������ĺ�ɫ
					//�޸���ɫ
					parent->_color = BLACK;
					gfather->_color = RED;
					break;//��������
				}

			}
			else
			{
				Node* uncle = gfather->_left;
				//uncle�ڵ���ڣ�������ɫ�Ǻ�ɫ��
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					gfather->_color = RED;
					//��������
					cur = gfather;
				}
				else
				{
					//cout << "Rotate---------" << endl;
					//�ж��Ƿ���˫���ĳ���
					if (parent->_left == cur)
					{
						RotateR(parent);//����
						swap(parent, cur);//����parent��cur��ָ���˻�Ϊ�����ĳ���
					}
					//uncle�ڵ㲻���ڻ���uncle�ڵ���ڣ�������ɫΪ��ɫ
					RotateL(gfather);//����----�ұߵ��ұ��������ĺ�ɫ
					//�޸���ɫ
					parent->_color = BLACK;
					gfather->_color = RED;
					break;//��������
				}
			}
		}

		//3.�����ڵ���ɫ��Ϊ��ɫ
		_header->_parent->_color = BLACK;
		//4.����_header������ָ��
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
		��������������ʣ�
		1.���Ǻ�ɫ��
		2.ÿ��·����ɫ������ͬ��
		3.��ɫ����������
	*/
	bool isValidTree()
	{
		if (_header->_parent == nullptr)
			return true;//����ҲĬ��Ϊ�����

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

		//����ÿһ��·���ĺ�ɫ�ڵ���,������Ƿ��к�ɫ�ڵ����������
		int curCount = 0;
		return isBalance(root, bCount, curCount);
	}

	bool isBalance(Node* root,int& bCount,int curCount)
	{
		//���ڵ��ߵ��մ���˵��һ��·����������
		if (root == nullptr)
		{
			//�жϺ�ɫ�ڵ�����Ƿ���ͬ
			if (bCount == curCount)
				return true;
			else
				return false;
		}

		if (root->_color == BLACK)
			curCount++;//�ۼӺ�ɫ�ڵ����

		//���ں�ɫ����������false
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