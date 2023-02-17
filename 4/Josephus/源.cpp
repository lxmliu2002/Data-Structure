#include<iostream>
using namespace std;

//��ʽ��
template<class T>
class Josephus {
public:
	int n;
	int m;
	T* array;
	Josephus(int x, int y)//���캯������n��m����ʼ���鸳ֵ
	{
		n = x;
		m = y;
		array = new T[n + 1];
		for (int i = 1; i <= n; i++)
			array[i] = i;
	}
	T Delete(int x)//�����������Ϊx��Ԫ�ط��ز���x���������Ԫ����ǰ��
	{
		T y = array[x];
		for (int i = x; i < n; i++)
			array[i] = array[i + 1];
		return y;

	}
	void Output()//���
	{
		int num;//����ѭ����Ҫɾ������Ԫ�����
		int temp = 0;//�м�������¼��һ��ɾ��Ԫ��ǰ���Ԫ�ظ���
		for (int i = 0; i < n - 1; i++)
		{
			if (!((m + temp) % (n - i)))
			{
				num = n - i;
			}
			else
			{
				num = (m + temp) % (n - i);
			}
			//temp���۱���ɾ����Ԫ��ǰ���Ԫ�ظ����������´�ѭ��ʹ��
			temp = num - 1;
			cout << Delete(num) << " ";
		}
		//ɾ����ǰn-1��Ԫ�غ�ֻʣ���һ��Ԫ�أ�ֱ���������
		cout << array[1] << endl;
	}
};


//����
template<class T>
class ChainNode {
public:
	T data;
	ChainNode<T>* link;
};

template<class T>
class Chain {

public:
	Chain() { first = 0; last = 0; }
	Chain<T>& Delete(int k, T& x);//ɾ��Ԫ��
	Chain<T>& Insert(int k, const T& x);//����Ԫ��
	Chain<T>& Sort(int n, int m);//ɸѡ
	Chain<T>& Append(const T& x);//��չ
	void output(ostream& out)const;

public:
	ChainNode<T>* first, * last;
};

template<class T>
Chain<T>& Chain<T>::Delete(int k, T& x)
{
	ChainNode<T>* current = first;
	if (k == 1)
		first = first->link;
	else
	{
		ChainNode<T>* q = first;
		for (int index = 1; index < k - 1 && q; index++)
		{
			q = q->link;
		}
		current = q->link;
		q->link = current->link;
	}
	x = current->data;
	delete current;
	return *this;
}

template<class T>//����
Chain<T>& Chain<T>::Insert(int k, const T& x)
{
	ChainNode<T>* q = first;
	for (int i = 1; i < k && q; i++)
	{
		q = q->link;
	}
	ChainNode<T>* p = new ChainNode<T>;
	p->data = x;
	if (k)
	{
		p->link = q->link;
		q->link = p;
	}
	else
	{
		p->link = first;
		first = p;
	}
	return *this;
}

template<class T>//��չ
Chain<T>& Chain<T>::Append(const T& x)
{
	ChainNode<T>* y = new ChainNode<T>;
	y->data = x;
	y->link = 0;
	if (first)
	{
		last->link = y;
		last = y;
	}
	else
		first = last = y;
	return *this;
}

template<class T>//ɸѡ
Chain<T>& Chain<T>::Sort(int n, int m)
{
	int num;
	int temp = 0;
	for (int i = 0; i < n - 1; i++)
	{
		if (!((m + temp) % (n - i)))
		{
			num = n - i;
		}
		else
		{
			num = (m + temp) % (n - i);
		}
		temp = num - 1;
		T x;
		Delete(num + i, x);
		Insert(i, x);
	}
	return *this;
}

template<class T>
void Chain<T>::output(ostream& out)const
{
	ChainNode<T>* current;
	for (current = first; current; current = current->link)
	{
		out << current->data;
		if (current->link)
			cout << " ";
	}
}

template<class T>
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.output(out);
	return out;
}

int main()
{
	//cout << "����������n������m��";
	//
	int n, m;
	cin >> n >> m;
	Josephus<int>array1(n, m);
	array1.Output();

	Chain<int>array2;
	for (int i = 1; i <= n; i++)
	{
		array2.Append(i);
	}
	array2.Sort(n, m);
	cout << array2 << endl;
	return 0;
}
