#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstddef>
using namespace std;
//template<class K>
//class SortedChainNode {
//public:
//	K data;
//	SortedChainNode<K>* link;
//};
//
//template<class K>
//class SortedChain {
//public:
//	SortedChain() { first = 0; }
//	bool IsEmpty()const
//	{
//		return first == 0;
//	}
//	bool Search(const K& k)const;
//	SortedChain<K>& Delete(const K& k);
//	SortedChain<K>& DistinctInsert(const K& k);
//	void Output(ostream& out)const;
//public:
//	SortedChainNode<K>* first;
//};
//
//template<class K>
//bool SortedChain<K>::Search(const K& k)const
//{
//	SortedChainNode<K>* p = first;
//	while (p && p->data < k)
//	{
//		p = p->link;
//	}
//	//�ж��Ƿ�ƥ��
//	if (p && p->data == k)
//	{
//		k = p->data;
//		return true;
//	}
//	//�����Ѿ�Ϊ�ջ��ߵ�ǰ���ݴ���k
//	return false;
//}
//
//template<class K>
//SortedChain<K>& SortedChain<K>::Delete(const K& k)
//{
//	/*p�����ƶ���tp���ڼ�¼p��ǰһ��λ��*/
//	SortedChainNode<K>* p = first, * tp = 0;
//	while (p && p->data < k)
//	{
//		tp = p;
//		p = p->link;
//	}
//	/*�ҵ���Ҫɾ���Ľڵ�*/
//	if (p && p->data == k)
//	{
//		k = p->data;
//		if (tp)
//			tp->link = p->link;
//		//p���׽ڵ�
//		else
//			first = p->link;
//		delete p;
//		return *this;
//	}
//	/*û�п�ɾ�Ľڵ�*/
//	//throw BadInput();
//	return *this;
//}
//
//template<class K>
//SortedChain<K>& SortedChain<K>::DistinctInsert(const K& k)
//{
//	SortedChainNode<K>* p = first, * tp = 0;
//	while (p && p->data < k)
//	{
//		tp = p;
//		p = p->link;
//	}
//	/*�������ظ��ؼ��ֵĲ���*/
//	if (p && p->data == k)
//	{
//		//cout << k << "�ظ�����" << " ";
//		return *this;
//	}
//	SortedChainNode<K>* q = new SortedChainNode<K>;
//	q->data = k;
//	q->link = p;
//	if (tp)
//		tp->link = q;
//	else
//		first = q;
//	return *this;
//}
//
////��ν����ֻ�����������������ҵ���Ӧ����һ������Ȼ�����ֵ�ĺ������������
//template<class K>
//class ChainHashTable {
//public:
//	ChainHashTable(int divisor = 11)
//	{
//		m = divisor;
//		ht = new SortedChain<K>[m];//����m�����������������
//	}
//	~ChainHashTable()
//	{
//		delete[]ht;
//	}
//	bool Search(const K& k)const
//	{
//		return ht[k % m].Search(k);
//	}
//	ChainHashTable<K>& Insert(const  K& k)
//	{
//		ht[k % m].DistinctInsert(k);
//		return *this;
//	}
//	ChainHashTable<K>& Delete(const K& k)
//	{
//		ht[k % m].Delete(k);
//		return *this;
//	}
//	void Output()const;
//public:
//	int m;//m�ǳ���
//	SortedChain<K>* ht;//ht����������
//};
//
//template<class K>
//void ChainHashTable<K>::Output()const
//{
//	for(int i=0;i<m;i++)
//	{
//		SortedChainNode<K>* p = ht[i].first;
//		if (p)
//		{
//			cout << "( " << i << " ) ";
//			while (p)
//			{
//				cout << p->data << " ";
//				p = p->link;
//			}
//			cout << endl;
//		}
//	}
//}
//
//int main()
//{
//	clock_t t1, t2;
//	ChainHashTable<int>zqzy(300000);
//	cout << endl << "-----���Խ��-----" << endl << endl;
//	t1 = clock();
//	for (int i = 0; i < 10000000; i++)
//		zqzy.Insert(rand() % 1000000);
//	//zqzy.Output();
//	t2 = clock();
//	cout << endl << "����һ��ʱ�� " << (t2 - t1) << " CLOCKS_PER_SEC" << endl << endl;
//}

template<class K>
class SortedChainNode {
public:
	K data;
	SortedChainNode<K>* link;
};

template<class K>
class SortedChain {
public:
	SortedChain()
	{
		first = new SortedChainNode<K>;
	}
	bool Search(const K& k)const;//�����������Ƿ�����ӦԪ��
	SortedChain<K>& Delete(const K& k);//ɾ���ڵ�
	SortedChain<K>& DistinctInsert(const K& k);//����ڵ�
public:
	SortedChainNode<K>* first;
};


template<class K>//�����������Ƿ�����ӦԪ��
bool SortedChain<K>::Search(const K& k)const
{
	SortedChainNode<K>* p = first;
	while (p->data < k)
	{
		p = p->link;
	}
	//�ж��Ƿ�ƥ��
	if (p->data == k)
	{
		return true;
	}
	//�����Ѿ�Ϊ�ջ��ߵ�ǰ���ݴ���k
	return false;
}

template<class K>//ɾ���ڵ�
SortedChain<K>& SortedChain<K>::Delete(const K& k)
{
	//p�����ƶ���tp���ڼ�¼p��ǰһ��λ��
	SortedChainNode<K>* p = first, * tp = first;
	while (p->data < k)
	{
		tp = p;
		p = p->link;
	}
	//�ҵ���Ҫɾ���Ľڵ�
	if (p->data == k)
	{
		tp->link = p->link;
		delete p;
		return *this;
	}
	//û�п�ɾ�Ľڵ�
	/*throw BadInput();*/
	return *this;
}

template<class K>//����ڵ�
SortedChain<K>& SortedChain<K>::DistinctInsert(const K& k)
{
	SortedChainNode<K>* p = first, * tp = first;
	while (p->data < k)
	{
		tp = p;
		p = p->link;
	}
	//�������ظ��ؼ��ֵĲ���
	if (p->data == k)
	{
		//cout << k << "�ظ�����" << " ";
		return *this;
	}
	SortedChainNode<K>* q = new SortedChainNode<K>;
	q->data = k;
	q->link = p;
	tp->link = q;
	return *this;
}

//��ν����ֻ�����������������ҵ���Ӧ����һ������Ȼ�����ֵ�ĺ������������
template<class K>
class ChainHashTable {
public:
	ChainHashTable(int divisor = 11)
	{
		m = divisor;
		tail = new SortedChainNode<K>;
		tail->data = 1001;
		tail->link = NULL;
		ht = new SortedChain<K>[m];//����m�����������������
		for (int i = 0; i < m; i++)
		{
			ht[i].first->link = tail;
		}
	}
	bool Search(const K& k)const//���ձ�ǩ����
	{
		return ht[k % m].Search(k);
	}
	ChainHashTable<K>& Insert(const K& k)//����Ԫ��
	{
		ht[k % m].DistinctInsert(k);
		return *this;
	}
	ChainHashTable<K>& Delete(const K& k)//ɾ��Ԫ��
	{
		ht[k % m].Delete(k);
		return *this;
	}
	void Output()const;
public:
	int m;//m�ǳ���
	SortedChain<K>* ht;//ht����������
	SortedChainNode<K>* tail;
};

template<class K>
void ChainHashTable<K>::Output()const
{
	for (int i = 0; i < m; i++)
	{
		SortedChainNode<K>* p = ht[i].first->link;
		if (p->data < tail->data)
		{
			cout << "( " << i << " ) ";
			while (p->data < tail->data)
			{
				cout << p->data << " ";
				p = p->link;
			}
			cout << endl;
		}
	}
}

int main()
{
	clock_t t1, t2;
	ChainHashTable<int>zqzy(30);
	for (int i = 0; i < 100; i++)
		zqzy.Insert(rand() % 100);
	cout << endl;
	zqzy.Output();
}