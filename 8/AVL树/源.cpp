#include<iostream>
#include<math.h>
#include"myExceptions.h"
#include"BinaryTree.h"
using namespace std;

template<class T>
class AVLTree :public BinaryTree<T> {
public:
	BinaryTreeNode<T>* Search(int x);//����ֵΪx�Ľڵ�ָ��
	BinaryTreeNode<T>* TreeMax(BinaryTreeNode<T>* t);//�������������ֵ�Ľڵ㣬�����������Ҳ�Ľڵ�
	BinaryTreeNode<T>* TreeMin(BinaryTreeNode<T>* t);//������������С���Ľڵ㣬�������������Ľڵ�

	BinaryTreeNode<T>* LL(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* LR(BinaryTreeNode<T>* t);
	BinaryTreeNode<T>* RL(BinaryTreeNode<T>* t);

	int BalanceFactor(BinaryTreeNode<T>* t);//�õ�ĳ���ڵ��ƽ������
	BinaryTreeNode<T>* Balance(BinaryTreeNode<T>* t);//����ƽ�����ӵĴ�С�ж��������ת

	AVLTree<T>& Insert(const T& t);
	BinaryTreeNode<T>* Insert(BinaryTreeNode<T>* temp, const T& t);
	AVLTree<T>& Delete(const T& t);
	BinaryTreeNode<T>* Delete(BinaryTreeNode<T>* temp, const T& t);

	int GetHeight(BinaryTreeNode<T>* t)const;
	void LeftNear(BinaryTreeNode<T>* t);

};

//����ֵΪx�Ľڵ�ָ��
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Search(int x)
{
	BinaryTreeNode<T>* temp = AVLTree<T>::root;
	while (temp)
	{
		if (temp->data == x)
			break;
		else
		{
			if (temp->data < x)
				temp = temp->RightChild;
			else
				temp = temp->LeftChild;
		}
	}
	return temp;
}

//�������������ֵ�Ľڵ㣬�����������Ҳ�Ľڵ�
template<class T>
BinaryTreeNode<T>* AVLTree<T>::TreeMax(BinaryTreeNode<T>* t)
{
	if (!t)
		return NULL;
	while (t->RightChild)
	{
		t = t->RightChild;
	}
	return t;
}

//������������С���Ľڵ㣬�������������Ľڵ�
template<class T>
BinaryTreeNode<T>* AVLTree<T>::TreeMin(BinaryTreeNode<T>* t)
{
	if (!t)
		return NULL;
	while (t->LeftChild)
	{
		t = t->LeftChild;
	}
	return t;
}

//���Ľڵ����࣬ʹ���������ڵ�t������ת
//ԭ��t�����ӳ�Ϊ�������ĸ���t�����ӵ��Һ��ӳ�Ϊt������
template<class T>
BinaryTreeNode<T>* AVLTree<T>::LL(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->LeftChild;
	t->LeftChild = temp->RightChild;
	temp->RightChild = t;
	t->height = AVLTree<T>::Height(t);
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

//�Ҳ�Ľڵ����࣬�ǲ������ĸ��ڵ�t�����ƶ�
//ԭ��t���Һ��ӳ�Ϊ�������ĸ���t���Һ��ӵ����ӳ�Ϊt���Һ���
template<class T>
BinaryTreeNode<T>* AVLTree<T>::RR(BinaryTreeNode<T>* t)
{
	BinaryTreeNode<T>* temp = t->RightChild;
	t->RightChild = temp->LeftChild;
	temp->LeftChild = t;
	t->height = AVLTree<T>::Height(t);
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

//���������������ڵ���࣬��������������RR���������ò��ָ�����LL����
template<class T>
BinaryTreeNode<T>* AVLTree<T>::LR(BinaryTreeNode<T>* t)
{
	t->LeftChild = RR(t->LeftChild);
	return LL(t);
}

//���������������ڵ���࣬��������������LL���������ò��ָ�����RR����
template<class T>
BinaryTreeNode<T>* AVLTree<T>::RL(BinaryTreeNode<T>* t)
{
	t->RightChild = LL(t->RightChild);
	return RR(t);
}

//����ĳ���ڵ��ƽ������
template<class T>
int AVLTree<T>::BalanceFactor(BinaryTreeNode<T>* t)
{
	return GetHeight(t->LeftChild) - GetHeight(t->RightChild);
}

//����ƽ�����ӵĴ�С�ж��������ת
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Balance(BinaryTreeNode<T>* t)
{
	int bf = BalanceFactor(t);
	if (bf > 1)
	{
		if (BalanceFactor(t->LeftChild) >= 0)
			t = LL(t);
		else
			t = LR(t);
	}
	else
	{
		if (bf < -1)
		{
			if (BalanceFactor(t->RightChild) <= 0)
				t = RR(t);
			else
				t = RL(t);
		}
	}
	return t;
}

//����Ľӿں���
template<class T>
AVLTree<T>& AVLTree<T>::Insert(const T& t)
{
	AVLTree<T>::root = Insert(AVLTree<T>::root, t);
	return *this;
}

//���뺯��
template<class T>
BinaryTreeNode<T>* AVLTree<T>::Insert(BinaryTreeNode<T>* temp, const T& t)
{
	//������ֹ���������ҵ���һ���սڵ㣬Ϊ������ڴ�ռ�
	if (temp == 0)
	{
		temp = new BinaryTreeNode<T>(t);
	}
	else
	{
		if (t > temp->data)
		{
			temp->RightChild = Insert(temp->RightChild, t);
			//������������ڵ���ܵ��²�ƽ�⣬���������������ƽ�����
			//��ƽ��������ܵ����������ڵ㷢���仯��������µ�ǰ���ڵ�
			temp = Balance(temp);
		}
		if (t < temp->data)
		{
			temp->LeftChild = Insert(temp->LeftChild, t);
			//������������ڵ���ܵ��²�ƽ�⣬���������������ƽ�����
			//��ƽ��������ܵ����������ڵ㷢���仯��������µ�ǰ���ڵ�
			temp = Balance(temp);
		}
	}
	temp->height = AVLTree<T>::Height(temp);
	return temp;
}

template<class T>
AVLTree<T>& AVLTree<T>::Delete(const T& t)
{
	AVLTree<T>::root = Delete(AVLTree<T>::root, t);
	return *this;
}

template<class T>
BinaryTreeNode<T>* AVLTree<T>::Delete(BinaryTreeNode<T>* temp, const T& t)
{
	if (!Search(t))
	{
		cout << "�޷�ɾ������Ϊ������ֵΪ" << t << "�Ľڵ㣡" << endl;
	}
	if (!AVLTree<T>::root)
	{
		return AVLTree<T>::root;
	}
	//���һ��Ҫɾ���Ľڵ�λ��������
	if (t < temp->data)
	{
		//���õݹ飬��temp���������Ͻ���ɾ������
		//�������µ����������ڵ������¾ɽڵ�
		temp->LeftChild = Delete(temp->LeftChild, t);
		if (BalanceFactor(temp) < -1)
			temp = Balance(temp);
	}
	else
	{
		//�������Ҫɾ���Ľڵ�λ��������
		if (t > temp->data)
		{
			//���õݹ飬��temp���������Ͻ���ɾ������
			//�������µ����������ڵ������¾ɽڵ�
			temp->RightChild = Delete(temp->RightChild, t);
			if (BalanceFactor(temp) > 1)
				temp = Balance(temp);
		}
		//�������Ҫɾ���Ľڵ���ǵ�ǰ�ĸ��ڵ�
		else
		{
			//�����ڵ���������������ڵ������
			//ʹ��ǰ����̵ĺô���ɾ��ǰ��/���AVL��������ƽ���
			if (temp->LeftChild && temp->RightChild)
			{
				//���������������������ڵ��ֵ�滻Ϊ��ֱ��ǰ����ֵ��ת��Ϊɾ��ֱ��ǰ��
				if (BalanceFactor(temp) > 0)
				{
					//ֱ��ǰ���������������ֵ�Ľڵ�
					BinaryTreeNode<T>* node = TreeMax(temp->LeftChild);
					temp->data = node->data;
					//ɾ���������ϵ�ǰ���ڵ㲢����������
					temp->LeftChild = Delete(temp->LeftChild, temp->data);
				}
				//���������ڻ���������������ڵ��ֵ�滻Ϊ��ֱ�Ӻ�̵�ֵ��ת��Ϊɾ��ֱ�Ӻ��
				else
				{
					//ֱ�Ӻ��������������Сֵ�Ľڵ�
					BinaryTreeNode<T>* node = TreeMin(temp->RightChild);
					temp->data = node->data;
					//ɾ���������ϵĺ�̽ڵ㲢����������
					temp->RightChild = Delete(temp->RightChild, temp->data);
				}
			}
			//���ڵ�ֻ��һ�������򲻴�������
			else
			{
				BinaryTreeNode<T>* node = temp;
				//������������������ֵ�����ڵ�
				temp = (temp->LeftChild) ? (temp->LeftChild) : (temp->RightChild);
				delete node;
				node = NULL;
			}

		}
	}
	return temp;
}

//���ĳ���ڵ�ĸ߶�
template<class T>
int AVLTree<T>::GetHeight(BinaryTreeNode<T>* t)const
{
	if (t == nullptr)
		return 0;
	return t->height;
}

template<class T>
void AVLTree<T>::LeftNear(BinaryTreeNode<T>* t)
{
	if (t == 0)
		return;
	if (t->LeftChild == 0 && t->RightChild == 0)
	{
		cout << t->data << " ";
		return;
	}
	int l = AVLTree<T>::Height(t->LeftChild);
	int r = AVLTree<T>::Height(t->RightChild);
	if (l < r && l != 0)
	{
		LeftNear(t->LeftChild);
	}
	else
	{
		if (l > r && r != 0)
		{
			LeftNear(t->RightChild);
		}
		else
		{
			LeftNear(t->LeftChild);
			LeftNear(t->RightChild);
		}
	}
}

int main()
{
	AVLTree<int> avl;
	srand(time(NULL));
	int tmp;
	cout << endl << "-----���������-----" << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		tmp = rand() % 100;
		cout << tmp << " ";
		avl.Insert(tmp);
	}
	cout << endl;
	cout << endl << "-----���ĸ߶�-----" << endl << endl;
	cout << avl.Height(avl.root) << endl;
	cout << endl << "-----�������ģ��-----" << endl << endl;
	show(avl.root, 1);

	cout << endl << "-----ɾ�����һ������������-----" << endl << endl;
	avl.Delete(tmp);
	show(avl.root, 1);
	cout << endl;

	cout << endl << "-----����������Ҷ�ڵ��ֵ-----" << endl << endl;
	avl.LeftNear(avl.root);
	cout << endl << endl;
	return 0;
}