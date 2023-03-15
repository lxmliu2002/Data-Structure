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
	void IChange(BinaryTreeNode<T>* t);
	void DChange(BinaryTreeNode<T>* t);
	bool Search(const T& t)const;
	redBlackTree<T>& Insert(const T& t);
	redBlackTree<T>& Delete(const T& t);
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

	if (temp->RightChild)
	{
		t->LeftChild = temp->RightChild;
		temp->RightChild->father = t;
	}
	else
	{
		t->LeftChild = NULL;
	}

	temp->RightChild = t;
	t->father = temp;

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

	if (temp->LeftChild)
	{
		t->RightChild = temp->LeftChild;
		temp->LeftChild->father = t;
	}
	else
	{
		t->RightChild = NULL;
	}

	temp->LeftChild = t;
	t->father = temp;

	return temp;
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::LR(BinaryTreeNode<T>* t)
{
	t->LeftChild = RR(t->LeftChild);
	return LL(t);
}

template<class T>
BinaryTreeNode<T>* redBlackTree<T>::RL(BinaryTreeNode<T>* t)
{
	t->RightChild = LL(t->RightChild);
	return RR(t);
}

template<class T>
void redBlackTree<T>::IChange(BinaryTreeNode<T>* t)
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
			p->color = BLACK;
			p->RightChild->color = RED;
			return;
		}
		if (p->RightChild && p->RightChild->color == 0)
		{
			if (t->father == p->LeftChild)
				p = RL(p);
			else
				p = RR(p);
			p->color = BLACK;
			p->LeftChild->color = RED;
			return;
		}
	}
	if (p->LeftChild && p->RightChild)
	{
		if (p->LeftChild->color == 0 && p->RightChild->color == 0)
		{
			p->LeftChild->color = 1;
			p->RightChild->color = 1;
			if (p->father)
			{
				p->color = 0;
				IChange(p);
			}
		}
	}
}

template<class T>
void redBlackTree<T>::DChange(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* f = t->father;
	BinaryTreeNode<T>* s;
	if (t == f->LeftChild)
		s = f->RightChild;
	else
		s = f->LeftChild;
	//���� 2 t���ֵ�Ϊ��
	if (s && s->color == RED)
	{
		s->color = BLACK;
		f->color = RED;
		if (t == f->LeftChild)
			f = RR(f);
		else
			f = LL(f);
		DChange(t);
	}
	else //s->color==BLACK
	{
		//���� 3 ���׺ڡ��ֵܺڡ��ֵܵ��������Ӻ�
		if (f->color == BLACK && s->LeftChild->color == BLACK && s->RightChild->color == BLACK)
		{
			s->color = RED;
			DChange(t->father);
		}
		//���� 4 ���׺졢�ֵܺڡ��ֵܵ��������Ӻ�
		if (s && f->color == RED && s->LeftChild->color == BLACK && s->RightChild->color == BLACK)
		{
			f->color = BLACK;
			s->color = RED;
		}
		//���� 5 t�����ӣ��ֵ����Ӻ죬�Һ��Ӻ�  �Լ�t���Һ��ӣ��ֵ��Һ��Ӻ����Ӻ�
		if (s && t == t->father->LeftChild && s->LeftChild->color == RED && s->RightChild->color == BLACK)
		{
			s->color = RED;
			s->LeftChild->color = BLACK;
			s = LL(s);
		}
		if (s && t == t->father->RightChild && s->RightChild->color == RED && s->LeftChild->color == BLACK)
		{
			s->color = RED;
			s->RightChild->color = BLACK;
			s = RR(s);
		}
		//���� 6 t�����ӣ��ֵ��Һ��Ӻ�  �Լ�t�����ӣ��ֵ��Һ��Ӻ�
		if (s && t == t->father->LeftChild && s->RightChild->color == RED)
		{
			s->RightChild->color = BLACK;
			int temp = s->color;
			s->color = f->color;
			f->color = temp;
			f = RR(f);
		}
		if (t == t->father->RightChild && s->LeftChild->color == RED)
		{
			s->LeftChild->color = BLACK;
			int temp = s->color;
			s->color = f->color;
			f->color = temp;
			f = LL(f);
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
			{
				//t = p->data;
				return true;
			}
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
	if(redBlackTree<T>::Search(t))
	{
		return *this;
	}
	else {
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
			DChange(r);
		}
		//���ڵ㲻������e���Ǹ��ڵ�
		else
			redBlackTree<T>::root = r;
		return *this;
	}
}

//ɾ��������ɾ���ؼ�ֵΪk��Ԫ�ز��ҽ��䷵�ص�e��
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
	if (p && p->LeftChild && p->RightChild)
	{
		//ʹsָ��p�����ӣ�psָ��p
		BinaryTreeNode<T>* s = p->LeftChild, * ps = p;
		//�ҵ�������һ���������һ���Һ�����s����ʾ��ps��ʾs�ĸ��ڵ�
		while (s->RightChild)
		{
			ps = s;
			s = s->RightChild;
		}
		//s�����������Ҫɾ���Ľڵ㣬���ˣ��������������ڵ�����´������
		p->data = s->data;

		//���s����ڵ㣬��Ҫ��sɾ������ڵ����������ƶ�p��ppλ��Ϊ����Ĵ����̵�
		//pΪ������һ���������һ���Һ���s
		p = s;
		//ppΪs�ĸ��ڵ�
		pp = ps;
	}

	//Ҫɾ���Ľڵ�û���ӽڵ�
	if (!p->LeftChild && !p->RightChild)
	{
		if (p == redBlackTree<T>::root)
		{
			delete p;
			return *this;
		}
		else
		{
			if (p == pp->LeftChild)
			{
				pp->LeftChild = NULL;
			}
			else
			{
				pp->RightChild = NULL;
			}
			DChange(pp);
		}
		delete p;
		return *this;
	}

	BinaryTreeNode<T>* c;
	//p������������������һ��ʱ
	if (p->LeftChild)
		c = p->LeftChild;
	else
		c = p->RightChild;
	//���p�Ǹ��ڵ�ֱ�Ӱ�c��ֵ�����ڵ�
	if (p == redBlackTree<T>::root)
	{
		c->color = BLACK;
		redBlackTree<T>::root = c;
	}
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
		if (p->color == 1 && c->color == 0)
			c->color = BLACK;
		else
		{
			if (p->color == 1 && c->color == 1)
				DChange(c);
		}
	}
	delete p;
	return *this;
}

int main()
{
	redBlackTree<int> A;
	int tmp;
	cout << "-----��������-----" << endl << endl;
	for (int i = 20; i > 1; i--) 
	{
		tmp = i + 1;
		cout << tmp << " ";
		A.Insert(tmp);
	}
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 9;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 13;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 7;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 5;
	cout << tmp << " ";
	A.Insert(tmp);
	tmp = 9;
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