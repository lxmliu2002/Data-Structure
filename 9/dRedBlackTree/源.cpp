#include<iostream>
#include"BinaryTree.h"
#include"myExceptions.h"
using namespace std;
#define BLACK 1
#define RED 0
template<class T>
class redBlackTree :public BinaryTree<T> {
public:
	BinaryTreeNode<T>* LL(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* LR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RL(BinaryTreeNode<T>* t);
	void Change(BinaryTreeNode<T>* t);
	bool Search(const T& t)const;
	redBlackTree<T>& Insert(const T& t);
	redBlackTree<T>& Delete(const T& t);
	void Delete(const T& t, bool yes);
	void Ascend() { redBlackTree<T>::InOrderOutput(); }
};

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	if (!t->father)
	{
		temp->father = NULL;
	}
	else
	{
		if (t == t->father->LeftChild)
		{
			t->father->LeftChild = temp;
			temp->father = t->father;
		}
		else
		{
			t->father->RightChild = temp;
			temp->father = t->father;
		}
	}
	t->LeftChild = temp->RightChild;
	temp->RightChild->father = t;
	temp->RightChild = t;
	t->father = temp;
	t->color = RED;
	temp->color = BLACK;
	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	if (!t->father)
	{
		temp->father = NULL;
	}
	else
	{
		if (t == t->father->RightChild)
		{
			t->father->RightChild = temp;
			temp->father = t->father;
		}
		else
		{
			t->father->LeftChild = temp;
			temp->father = t->father;
		}
	}
	t->RightChild = temp->LeftChild;
	temp->LeftChild->father = t;
	temp->LeftChild = t;
	t->father = temp;
	t->color = RED;
	temp->color = BLACK;
	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	t->LeftChild = RR(temp);
	return LL(t);
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	t->RightChild = LL(temp);
	return RR(t);
}

template<class T>
void redBlackTree<T>::Change(BinaryTreeNode<T>* t)
{
	if (!t->father || !t->father->father)
		return;
	BinaryTreeNode<T>* p = t->father->father;
	if (!p->LeftChild || !p->RightChild || p->LeftChild->color == 1 || p->RightChild->color == 1)
	{
		if (p->LeftChild && p->LeftChild->color == 0)
		{
			if (t->father == p->LeftChild)
				p = LL(p);
			else
				p = LR(p);
		}
		if (p->RightChild && p->RightChild->color == 0)
		{
			if (t->father == p->LeftChild)
				p = RL(p);
			else
				p = RR(p);
		}
	}
	if (p->LeftChild && p->RightChild)
	{
		if (p->LeftChild->color == 0 && p->RightChild->color == 0)
		{
			p->LeftChild->color = 1;
			p->RightChild->color = 1;
			if (!p->father)
				p->color = 1;
			else
			{
				p->color = 0;
				Change(p);
			}
		}
	}

}

template<class T>
bool redBlackTree<T>::Search(const T& t)const
{

	//����ʹpָ����ڵ�
	BinaryTreeNode<T>* p = redBlackTree<T>::root;
	while (p)
	{
		//����if-else����ѡһ��kС�ڸ��ڵ�ʱָ����������k���ڸ��ڵ�ʱָ�������������ڸ��ڵ�ʱ����true
		if (t < p->data)
			p = p->LeftChild;
		else
		{
			if (t > p->data)
				p = p->RightChild;
			else
				return true;
		}
	}
	//û���ҵ��ؼ�ֵΪk��Ԫ�أ���ʱpΪ�գ�ֱ�ӷ���false
	return false;
}



template<class T>
redBlackTree<T>& redBlackTree<T>::Insert(const T& t)
{
	//pָ����ڵ㣬ppָ����ڵ�ĸ��ڵ㣨�ǳ�ʼʱ��
	BinaryTreeNode<T>* p = redBlackTree<T>::root, * pp = 0;
	while (p)
	{
		//ppָ����һ��whileѭ��������p�ڵ��λ��
		pp = p;
		//����if-else����ѡһ��kС�ڸ��ڵ�ʱָ����������
		//k���ڸ��ڵ�ʱָ�������������ڸ��ڵ�ʱ˵���Ѿ�����e���Ԫ�أ��޷�����
		if (t <= p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//�����Ѿ��ҵ��˺��ʵĲ���λ��
	BinaryTreeNode<T>* r = new BinaryTreeNode<T>(t);
	//�����ڵ����ʱ���жϲ��������������ǲ�����������
	if (redBlackTree<T>::root)
	{
		if (t <= pp->data)
		{

			pp->LeftChild = r;
			r->father = pp;

		}
		else
		{
			pp->RightChild = r;
			r->father = pp;
		}
		Change(r);
	}
	//���ڵ㲻������e���Ǹ��ڵ�
	else
		redBlackTree<T>::root = r;
	return *this;
}

//ɾ��������ɾ���ؼ�ֵΪt��Ԫ��
template<class T>
redBlackTree<T>& redBlackTree<T>::Delete(const T& t)
{
	//pָ����ڵ㣬ppָ����ڵ�ĸ��ڵ㣨�ǳ�ʼʱ��
	BinaryTreeNode<T>* p = redBlackTree<T>::root, * pp = 0;
	while (p && p->data != t)
	{
		pp = p;
		if (t < p->data)
			p = p->LeftChild;
		else
			p = p->RightChild;
	}
	//��p�����ڵ�ʱ��˵���ؼ�ֵΪk��Ԫ�ز����ڣ��׳��쳣����
	if (!p)
		throw BadInput();
	//Ҫɾ���ڵ�����ҽڵ㶼���ڵ������
	if (p->LeftChild && p->RightChild)
	{
		//ʹsָ��p�����ӣ�psָ��p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//�ҵ�������һ���������һ���Һ�����s����ʾ��ps��ʾs�ĸ��ڵ�
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//sΪ���ǰ����psΪ�丸�ڵ�
		//s�����������Ҫɾ���Ľڵ㣬���ˣ��������������ڵ�����´������
		p->data = s->data;

		//���s����ڵ㣬��Ҫ��sɾ������ڵ����������ƶ�p��ppλ��Ϊ����Ĵ����̵�
		//pΪ������һ���������һ���Һ���s
		p = s;
		//ppΪs�ĸ��ڵ�
		pp = ps;
	}
	//��p��������ʱ(��������һ��ifѭ��)����p������������������һ��ʱ��û�����ϸ�ifѭ����
	if (!p->LeftChild && !p->RightChild)
	{
		delete p;
		return *this;
	}
	BinaryTreeNode<T>* c;
	if (p->LeftChild)
	{
		p->LeftChild->color = BLACK;
		c = p->LeftChild;
	}
	else
	{
		p->RightChild->color = BLACK;
		c = p->RightChild;
	}
	//���p�Ǹ��ڵ�ֱ�Ӱ�c��ֵ�����ڵ�
	if (p == redBlackTree<T>::root)
		redBlackTree<T>::root = c;
	//p���Ǹ��ڵ�Ļ�����pp��p�Ĺ�ϵ���Ӷ�����pp��c�Ĺ�ϵ
	else
	{
		if (p == pp->LeftChild)
		{
			pp->LeftChild = c;
			c->father = pp;
		}
		else
		{
			pp->RightChild = c;
			c->father = pp;
		}
		if (c->color == 0 && pp->color == 0)
			Change(c);
	}
	delete p;
	return *this;
}

template<class T>
void redBlackTree<T>::Delete(const T& t, bool yes)
{
	while (Search(t))
	{
		Delete(t);
	}
}

int main()
{
	redBlackTree<int> A;
	int tmp;
	cout << "-----��������-----" << endl << endl;
	for (int i = 19; i > 0; i--)
	{
		tmp = i + 1;
		cout << tmp << " ";
		A.Insert(tmp);
	}
	tmp = 15;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 15;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 5;
	cout << tmp << " ";
	A.Insert(tmp);
	cout << endl << "-----������-----" << endl << endl;
	A.Ascend();
	cout << endl << "-----ɾ��3��8��12-----" << endl << endl;
	A.Delete(3);
	A.Delete(8);
	A.Delete(12);
	A.Ascend();
	return 0;
}