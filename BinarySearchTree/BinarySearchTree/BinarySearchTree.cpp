#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;

//�ڵ�
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

//����������:�ڵ��е�����ֵΨһ
//��ǰ�Ķ���������������ֵС�ڸ�����ֵ��������ֵС����������ֵ
//��֧���޸ģ��޸Ļ�ı����Ľṹ
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
	
	//�����������ݺͽṹ
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

	//����
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

	//����
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;//��¼���׽ڵ�

		//�ҵ����ʵĲ���λ��
		while (cur)
		{
			//���¸��׽ڵ�
			parent = cur;
			//�����������нڵ�Ψһ
			if (cur->_data == val)
				return false;
			else if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		cur = new Node(val);
		//�жϲ���ڵ��λ�����ڸ��ڵ����߻����ұ�
		if (parent->_data > val)
			parent->_left = cur;
		else
			parent->_right = cur;

		return true;
	}

	//�������
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

	//ɾ��
	bool erase(const T& val)
	{
		//����
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (cur->_data == val)
				break;

			parent = cur;//���¸��׽ڵ�
			if (cur->_data > val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}

		//�ж��Ƿ��ҵ���Ҫɾ���Ľڵ�
		if (cur == nullptr)
			return false;

		//ɾ��
		//1.ɾ������Ҷ�ӽڵ�
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			//�ж��Ƿ�Ϊ���ڵ�
			if (cur == _root)
			{
				_root = nullptr;
			}
			else
			{
				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}

			//ɾ���ڵ�
			delete cur;
		}
		else if(cur->_left == nullptr)//��Ҷ�ӽڵ㣬������Ϊ��
		{
			//ɾ�����Ǹ��ڵ�
			if (cur == _root)
			{
				_root = cur->_right;
			}
			else
			{
				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
				//���ø��׽ڵ�͵�ǰ�ڵ������������
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			

			delete cur;
		}
		else if (cur->_right == nullptr)  //��Ҷ�ӽڵ㣬������Ϊ��
		{
			//ɾ�����Ǹ��ڵ�
			if (cur == _root)
			{
				_root = cur->_left;
			}
			else
			{
				//�ж���Ҫɾ���Ľڵ��ڸ��ڵ����һ��
				//���ø��׽ڵ�͵�ǰ�ڵ������������
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else 
					parent->_right = cur->_left;
			}

			delete cur;
		}
		else  
		{
			//��������������
			//�����������������ҽڵ�(Ҳ������������������ڵ�)
			Node* leftRightMost = cur->_left;//�������ĸ��ڵ�
			parent = cur;

			//1.���������������ҽڵ�
			while (leftRightMost->_right)
			{
				parent = leftRightMost;
				leftRightMost = leftRightMost->_right;
			}

			//2.����
			swap(cur->_data, leftRightMost->_data);

			//3.ɾ�����ҽڵ�
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

////�����������������������
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

////���������룬����,�����������
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
//		cout << "�ҵ���,��ַΪ"<<&ret->_data << endl;
//	else
//		cout << "����û�����ֵ��Ӧ�Ľڵ�" << endl;
//
//	tree.inOrder();
//}



int main()
{
	test();
	return 0;
}