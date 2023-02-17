#include<iostream>
using namespace std;

//����ڵ���
template<class T>
class ChainNode {
public:
	T data;
	ChainNode<T>* link;
};

//�����࣬������Ҫʹ�õ��������Insert��Append����
template<class T>
class Chain {

public:
	Chain() { first = 0; last = 0; }//���캯��
	bool Isempty()const { return first == 0; }//�ж������Ƿ�Ϊ��
	int Len()const;//��������ĳ���
	bool Find(int k, T& x)const;//�����������Ƿ�����Ӧ��ֵ
	int Search(const T& x)const;//����������ֵ��λ��
	Chain<T>& Delete(int k, T& x);//ɾ��������Ԫ��
	Chain<T>& Insert(int k, const T& x);//����Ԫ��
	Chain<T>& Append(const T& x);//��չ����
	void output(ostream& out)const;//�������
	void Erase();//ɾ��Ԫ��

public:
	ChainNode<T>* first, * last;
};

template<class T>//ɾ��Ԫ��
void Chain<T>::Erase()
{
	ChainNode<T>* current;
	while (first)
	{
		current = first->link;
		delete first;
		first = current;
	}
}

template<class T>//��������ĳ���
int Chain<T>::Len()const
{
	ChainNode<T>* current = first;
	int index = 0;
	while (current)
	{
		index++;
		current = current->link;
	}
	return index;
}

template<class T>//�����������Ƿ�����Ӧ��ֵ
bool Chain<T>::Find(int k, T& x)const
{
	if (k < 1)return false;
	ChainNode<T>* current = first;
	int index = 1;
	while (index < k && current)
	{
		current = current->link;
		index++;
	}
	if (current)
	{
		x = current->data;
		return true;
	}
	return false;
}

template<class T>//����������ֵ��λ��
int Chain<T>::Search(const T& x)const
{
	ChainNode<T>* current = first;
	int index = 1;
	while (current && current->data != x)
	{
		current = current->link;
		index++;
	}
	if (current)
		return index;
	return 0;
}

template<class T>//ɾ��������Ԫ��
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

template<class T>//����Ԫ��
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

template<class T>//�������
void Chain<T>::output(ostream& out)const
{
	ChainNode<T>* current;
	for (current = first; current; current = current->link)
	{
		out << current->data << " ";
	}
}

template<class T>//������������
ostream& operator<<(ostream& out, const Chain<T>& x)
{
	x.output(out);
	return out;
}

template<class T>//��չ����
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

//�ڵ��࣬ʹ�õ�����<<��>>�����졢Ĭ�Ϲ��졢col��value�Ⱥ�����Ա�����ݳ�Ա
template<class T>
class CNode {
public:
	template<class T>
	friend ostream& operator<<(ostream& out, const CNode<T>&);
	template<class T>
	friend istream& operator>>(istream& in, CNode<T>&);
	CNode<T>() = default;
	CNode<T>(int x, T y)
	{
		col = x;
		value = y;
	}
	CNode<T>& operator=(const CNode<T>& x);
	int operator!=(const CNode<T>& y)
	{
		return (value != y.value);
	}
	void Output(ostream& out)const
	{
		out << "  column:" << col << "  value:" << value;
	}
public:
	int col;
	T value;
};

template<class T>//������������
ostream& operator<<(ostream& out, const CNode<T>& x)
{
	x.Output(out);
	out << endl;
	return out;
}

template<class T>//�������������
istream& operator>>(istream& in, CNode<T>& x)
{
	cout << "Please input colume:";
	in >> x.col;
	cout << "Please input value:";
	in >> x.value;
	return in;
}

template<class T>//����=�����
CNode<T>& CNode<T>:: operator=(const CNode<T>& x)
{
	col = x.col;
	value = x.value;
	return *this;
}

//��ͷ�ڵ��࣬ʹ�õ�����<<��>>��row��Chain<CNode<T>>b�Ⱥ�����Ա�����ݳ�Ա
template<class T>
class HeadNode {
	template<class T>
	friend ostream& operator<<(ostream&, const HeadNode<T>&);
	template<class T>
	friend istream& operator>>(istream&, HeadNode<T>&);

public:
	int operator!=(const HeadNode<T>& y)
	{
		return (row != y.row);
	}
	void Output(ostream& out)const
	{
		out << "row:" << row;
	}
public:
	int row;
	Chain<CNode<T>>b;
};

template<class T>
ostream& operator<<(ostream& out, const HeadNode<T>& x)
{
	x.Output(out);
	out << endl;
	return out;
}

template<class T>
istream& operator>>(istream& in, HeadNode<T>& x)
{
	cout << "Please input row:";
	in >> x.row;
	return in;
}

//���нڵ���������������Ҳ��������ϡ�����������кź��к�
//��Ҫ���Ӵ�����ȡ�����ӡ������˲���
template<class T>
class LinkedMatrix {
public:
	template<class T>
	friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);//���˫��������ȫ��Ԫ��
	template<class T>
	friend istream& operator>>(istream&, LinkedMatrix<T>& b);//����˫��������ȫ��Ԫ��
	LinkedMatrix<T>& Store(const T& x, int r, int c);//��������
	T Retrieve(int i, int j)const;//ȡ������
	LinkedMatrix(int r, int c);//���캯��
	void Transpose(LinkedMatrix<T>& b)const;//ת�ú���
	LinkedMatrix<T>operator+(const LinkedMatrix<T>& x)const;//���ؾ���ӷ�
	LinkedMatrix<T>operator-(const LinkedMatrix<T>& x)const;//���ؾ������
	LinkedMatrix<T>operator*(const LinkedMatrix<T>& x)const;//���ؾ���˷�
private:
	int rows;
	int cols;
	Chain<HeadNode<T>>a;
};

template<class T>//������������
ostream& operator<<(ostream& out, const LinkedMatrix<T>& x)
{
	//��ʼʱpָ��ͷ�ڵ������ͷָ�룬֮��p����ͷ�ڵ�����
	ChainNode<HeadNode<T>>* p = x.a.first;
	while (p)
	{
		//tempָ��p��������
		HeadNode<T>temp = p->data;
		//�жϵ�ǰ�������Ƿ�Ϊ�գ��ǵĻ��Ƶ���һ���������Դ�����
		if (temp.b.first)
		{
			//temp2ָ��ǰ�������ͷ�ڵ�
			ChainNode<CNode<T>>* temp2 = temp.b.first;
			//����к�
			out << temp;
			//������������Ԫ��ʱ��temp2���ƶ���Ԫ���������
			while (temp2)
			{
				CNode<T>b = temp2->data;
				out << b;
				temp2 = temp2->link;
			}
			cout << endl;
		}
		p = p->link;
	}
	return out;
}

template<class T>//�������������
istream& operator>>(istream& in, LinkedMatrix<T>& b)
{
	cout << "������ϡ������з�0Ԫ�ظ�����";
	int count, r, c;
	T x;
	in >> count;
	//ͨ������Store����������Ԫ������
	for (int i = 1; i <= count; i++)
	{
		cout << "�������" << i << "��Ԫ�ص�value��row��col��";
		in >> x >> r >> c;
		b.Store(x, r, c);
	}
	return in;
}


template<class T>//��������
LinkedMatrix<T>& LinkedMatrix<T>::Store(const T& x, int r, int c)
{
	//��x������������������1������������ͷ����2�����м䣻3����β��

	//pָ��ͷ�ڵ������ͷָ��
	ChainNode<HeadNode<T>>* p = a.first;
	//ʹp�ƶ���r������λ��
	while (p->data.row != r)
	{
		p = p->link;
	}
	//qָ���r�е��������ͷ�ڵ�
	ChainNode<CNode<T>>* q = p->data.b.first;
	//�������Ϊ����ֱ����Append����
	if (!q)
	{
		q = new ChainNode<CNode<T>>;
		q->data.col = c;
		q->data.value = x;
		p->data.b.Append(q->data);
		return *this;
	}
	//num����ͳ�Ʋ��뵽�����м�ľ���λ������
	int num = 0;
	//���в�Ϊ�������α�������λ��
	while (q)
	{
		if (q->data.col == c)
		{
			cout << "��λ���Ѵ������ݣ��޷�����";
			return *this;
		}
		//�������кű�c���Ԫ��ʱ��c���뵽numλ��
		if (q->data.col > c)
		{
			ChainNode<CNode<T>>* q3 = new ChainNode<CNode<T>>;
			q3->data.col = c;
			q3->data.value = x;
			p->data.b.Insert(num, q3->data);
			return *this;
		}
		q = q->link;
		num++;
	}
	//�������û�к���λ����ֱ�Ӳ����β
	ChainNode<CNode<T>>* q1 = new ChainNode<CNode<T>>;
	q1->data.col = c;
	q1->data.value = x;
	p->data.b.Append(q1->data);
	return *this;
}

template<class T>//ȡ������
T LinkedMatrix<T>::Retrieve(int r, int c)const
{
	ChainNode<HeadNode<T>>* p1 = a.first;
	HeadNode<T>temp1 = p1->data;
	while (temp1.row != r)
	{
		p1 = p1->link;
		temp1 = p1->data;
	}
	ChainNode<CNode<T>>* p2 = temp1.b.first;
	CNode<T>temp2 = p2->data;
	while (temp2.col < c && p2)
	{
		p2 = p2->link;
		temp2 = p2->data;
	}
	T val = temp2.value;
	return T;
}


template<class T>//���캯��
LinkedMatrix<T>::LinkedMatrix(int r, int c)
{
	//�ڹ��캯���н�ͷ�ڵ�����ͨ��Append����ȫ����ʼ���������к�row
	rows = r;
	cols = c;
	ChainNode<HeadNode<T>>* p = new ChainNode<HeadNode<T>>;
	for (int i = 1; i <= rows; i++)
	{
		p->data.row = i;
		a.Append(p->data);
	}
}


template<class T>//ת�þ���
void LinkedMatrix<T>::Transpose(LinkedMatrix<T>& x)const
{
	//���α���˫������������Ԫ�أ�ͨ��Store�����������н����������µ�˫������x��
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<CNode<T>>* temp2 = temp1->data.b.first;
	while (temp1)
	{
		ChainNode<CNode<T>>* next = temp2;
		while (next)
		{
			x.Store(next->data.value, next->data.col, temp1->data.row);
			next = next->link;
		}
		temp1 = temp1->link;
		if (!temp1)
			break;
		temp2 = temp1->data.b.first;
	}
}

template<class T>//���ؾ���ӷ�
LinkedMatrix<T> LinkedMatrix<T>::operator+(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(rows, cols);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = x.a.first;
	ChainNode<HeadNode<T>>* temp3 = y.a.first;
	//ͬʱ�������������ÿһ��
	while (temp1 && temp2)
	{
		ChainNode<CNode<T>>* temp4 = temp1->data.b.first;
		ChainNode<CNode<T>>* temp5 = temp2->data.b.first;
		//��������������Ϊ��ʱ
		while (temp4 && temp5)
		{
			//�к��������мӷ�
			if (temp4->data.col == temp5->data.col)
			{
				//�����Ӻ��value��Ϊ0��Append������������
				if (temp4->data.value + temp5->data.value)
				{
					CNode<T>a(temp4->data.col, temp4->data.value + temp5->data.value);
					temp3->data.b.Append(a);
				}
				temp4 = temp4->link;
				temp5 = temp5->link;
				if (!(temp4 && temp5))
					break;
			}
			//һ�����к�С����һ���кţ���ǰһ��Append������������ǰһ��������ָ������
			if (temp4->data.col < temp5->data.col)
			{
				CNode<T>a(temp4->data.col, temp4->data.value);
				temp3->data.b.Append(a);
				temp4 = temp4->link;
				if (!temp4)
					break;
			}
			//һ�����кŴ�����һ���кţ��򽫺�һ��Append��������������һ��������ָ������
			if (temp4->data.col > temp5->data.col)
			{
				CNode<T>a(temp5->data.col, temp5->data.value);
				temp3->data.b.Append(a);
				temp5 = temp5->link;
				if (!temp5)
					break;
			}
		}
		//��һ���������Ѿ������꣬���ǰһ����������ʣ��Ԫ��Append��������
		while (temp4 && !temp5)
		{
			CNode<T>a(temp4->data.col, temp4->data.value);
			temp3->data.b.Append(a);
			temp4 = temp4->link;
		}
		//ǰһ���������Ѿ������꣬��Ѻ�һ����������ʣ��Ԫ��Append��������
		while (!temp4 && temp5)
		{
			CNode<T>a(temp5->data.col, temp5->data.value);
			temp3->data.b.Append(a);
			temp5 = temp5->link;
		}
		temp1 = temp1->link;
		temp2 = temp2->link;
		temp3 = temp3->link;
	}
	return y;
}

template<class T>//���ؾ������
LinkedMatrix<T> LinkedMatrix<T>::operator-(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(rows, cols);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = x.a.first;
	ChainNode<HeadNode<T>>* temp3 = y.a.first;
	while (temp1 && temp2)
	{
		ChainNode<CNode<T>>* temp4 = temp1->data.b.first;
		ChainNode<CNode<T>>* temp5 = temp2->data.b.first;
		while (temp4 && temp5)
		{

			if (temp4->data.col == temp5->data.col)
			{
				if (temp4->data.value - temp5->data.value)
				{
					CNode<T>a(temp4->data.col, temp4->data.value - temp5->data.value);
					temp3->data.b.Append(a);
				}
				temp4 = temp4->link;
				temp5 = temp5->link;
				if (!(temp4 && temp5))
					break;
			}
			if (temp4->data.col < temp5->data.col)
			{
				CNode<T>a(temp4->data.col, temp4->data.value);
				temp3->data.b.Append(a);
				temp4 = temp4->link;
				if (!temp4)
					break;
			}
			if (temp4->data.col > temp5->data.col)
			{
				CNode<T>a(temp5->data.col, -(temp5->data.value));
				temp3->data.b.Append(a);
				temp5 = temp5->link;
				if (!temp5)
					break;
			}
		}
		while (temp4 && !temp5)
		{
			CNode<T>a(temp4->data.col, temp4->data.value);
			temp3->data.b.Append(a);
			temp4 = temp4->link;
		}
		while (!temp4 && temp5)
		{
			CNode<T>a(temp5->data.col, -(temp5->data.value));
			temp3->data.b.Append(a);
			temp5 = temp5->link;
		}
		temp1 = temp1->link;
		temp2 = temp2->link;
		temp3 = temp3->link;
	}
	return y;
}

template<class T>//���ؾ���˷�
LinkedMatrix<T> LinkedMatrix<T>::operator*(const LinkedMatrix<T>& x)const
{
	LinkedMatrix<T>y(x.cols, x.rows);
	LinkedMatrix<T>z(rows, x.cols);
	//ͨ��ת�ã�ʹ�˷���Ϊ����˫������������ˣ��Ӷ�������һ�г�һ�еĸ������
	x.Transpose(y);
	ChainNode<HeadNode<T>>* temp1 = a.first;
	ChainNode<HeadNode<T>>* temp2 = y.a.first;
	ChainNode<CNode<T>>* zqzy1 = temp1->data.b.first;
	ChainNode<CNode<T>>* zqzy2 = temp2->data.b.first;
	//sum������¼������˺����ֵ
	T sum = 0;
	//��һ��ѭ�����α���������ÿһ��
	while (temp1)
	{
		//�жϵ�һ������Ϊ�յ�������
		if (zqzy1)
		{
			//�ڶ���ѭ�����α����Ҿ����ÿһ��
			while (temp2)
			{
				//���ڶ��������������Ϊ��ʱ���ƶ�����һ��
				while (!zqzy2)
				{
					temp2 = temp2->link;
					if (!temp2)
						return z;;
					zqzy2 = temp2->data.b.first;
				}
				//������������Ϊ�����ж��кţ����ڻ�С�������ƣ����������
				while (zqzy1 && zqzy2)
				{
					while (zqzy1->data.col > zqzy2->data.col)
					{
						zqzy2 = zqzy2->link;
						if (!zqzy2)
							goto L;
					}
					while (zqzy1->data.col < zqzy2->data.col)
					{
						zqzy1 = zqzy1->link;
						if (!zqzy1)
							goto L;
					}
					if (zqzy1->data.col == zqzy2->data.col)
					{
						sum += zqzy1->data.value * zqzy2->data.value;
						zqzy1 = zqzy1->link;
						zqzy2 = zqzy2->link;
					}
				L:;
				}
				//��sum��Ϊ0��Append��������
				if (sum)
				{
					z.Store(sum, temp1->data.row, temp2->data.row);
					sum = 0;
				}
				zqzy1 = temp1->data.b.first;
				temp2 = temp2->link;
				if (!temp2)
					break;
				zqzy2 = temp2->data.b.first;
			}
		}
		temp1 = temp1->link;
		if (!temp1)
			break;
		zqzy1 = temp1->data.b.first;
		temp2 = y.a.first;
		zqzy2 = temp2->data.b.first;
	}
	return z;
}

int main()
{
	int row1, col1, row2, col2;
	cout << "�������һ�������������������";
	cin >> row1 >> col1;
	cout << "������ڶ��������������������";
	cin >> row2 >> col2;
	LinkedMatrix<int>x1(row1, col1);
	LinkedMatrix<int>x2(row2, col2);
	LinkedMatrix<int>x3(row1, col1);
	LinkedMatrix<int>x4(row1, col1);
	LinkedMatrix<int>x5(row1, col2);
	cout << endl << "�������һ������" << endl;
	cin >> x1;
	cout << endl << "������ڶ�������" << endl;
	cin >> x2;
	x3 = x1 + x2;
	cout << endl << "����������ӵĽ��Ϊ��" << endl << x3 << endl;
	x4 = x1 - x2;
	cout << "������������Ľ��Ϊ��" << endl << x4 << endl;
	x5 = x1 * x2;
	cout << "����������˵Ľ��Ϊ��" << endl << x5 << endl;
	return 0;
}