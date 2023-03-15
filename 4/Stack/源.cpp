#include<iostream>
using namespace std;

template<class T>
class Node {
public:
	T data;
	Node<T>* link;
};

template<class T>
class LinkedStack {
public:
	template<class T>//������������
	friend ostream& operator<<(ostream& out, LinkedStack<T>&);
	template<class T>//�������������
	friend istream& operator>>(istream& in, LinkedStack<T>&);
	LinkedStack() { top = 0; }
	bool IsEmpty()const { return top == 0; }
	T Top()const;//ջ��Ԫ��
	LinkedStack<T>& Push(const T& x);//��ջ
	LinkedStack<T>& Pop(T& x);//��ջ
	LinkedStack<T>& Delete(const T& x);//ɾ��Ԫ��
	bool Find(const T& x)const;//����Ԫ��
	Node<T>* top;
};
template<class T>//������������
ostream& operator<<(ostream& out, LinkedStack<T>& x)
{
	while (!x.IsEmpty())
	{
		T temp;
		x.Pop(temp);
		out << temp;
		if (!x.IsEmpty())
			out << " ";
	}
	return out;
}

template<class T>
istream& operator>>(istream& in, LinkedStack<T>& x)
{
	cout << "�����뽫Ҫ�����ջ��Ԫ�ظ�����";
	int num;
	in >> num;
	for (int i = 0; i < num; i++)
	{
		T temp;
		in >> temp;
		x.Push(temp);
	}
	return in;
}

template<class T>//��ȡջ��Ԫ��
T LinkedStack<T>::Top()const
{
	return top->data;
}

template<class T>//��ջ
LinkedStack<T>& LinkedStack<T>::Push(const T& x)
{
	Node<T>* p = new Node<T>;
	p->data = x;
	p->link = top;
	top = p;
	return *this;
}

template<class T>//��ջ
LinkedStack<T>& LinkedStack<T>::Pop(T& x)
{
	x = top->data;
	Node<T>* p = top;
	top = top->link;
	delete p;
	return *this;
}

template<class T>//ɾ��Ԫ��
LinkedStack<T>& LinkedStack<T>::Delete(const T& x)
{
	Node<T>* current = top;
	if (current->data == x)
	{
		top = top->link;
		delete current;
	}
	else
	{
		Node<T>* temp = current;
		current = current->link;
		while (current)
		{
			if (current->data == x)
			{
				temp->link = current->link;
				delete current;
				return *this;
			}
			current = current->link;
			temp = temp->link;
		}
	}
	return *this;
}

template<class T>//����Ԫ��
bool LinkedStack<T>::Find(const T& x)const
{
	Node<T>* temp = top;
	while (temp)
	{
		if (temp->data == x)
			return 1;
		temp = temp->link;
	}
	return 0;
}

template<class T>
void delete_all(LinkedStack<T>& s, const T& x)
{
	while (s.Find(x))
	{
		s.Delete(x);
	}
}

int main()
{
	char x;
	cin >> x;
	LinkedStack<char>zqzy;
	cin >> zqzy;
	if (zqzy.IsEmpty())
	{
		cout << "��ջ";
		return 0;
	}
	delete_all(zqzy, x);
	cout << zqzy;
	return 0;
}