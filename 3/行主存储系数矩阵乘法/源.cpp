#include<iostream>
using namespace std;

template<class T>
class Term {
public:
	//Ԫ������ԭ������к�row���к�col��Ԫ����ֵvalue
	int row;
	int col;
	T value;
};

template<class T>
class SparseMatrix {
	template<class T>
	friend ostream& operator<<(ostream& out, const SparseMatrix<T>& m);//�������
	template<class T>
	friend istream& operator>>(istream& in, SparseMatrix<T>& m);//��������

public:
	SparseMatrix(int maxTerms = 10);//���캯������ֵMaxTerms���������ݳ�Ա��ֵΪ0
	void Transpose(SparseMatrix<T>& b)const;//��ԭ����ת�ô洢��b��
	void Add(const SparseMatrix<T>& b, SparseMatrix<T>& c)const;//ԭ�����b������Ӵ洢��c��
	void Append(const Term<T>& t);//�������ĩβ����Ԫ��
	void no_same();//ȥ���������кź��к���ȵ�Ԫ�صĺ��ߣ����Ұ�������Ӻ��ֵ����ǰ��
	void no_zero();//ȥ��������ֵΪ���Ԫ��
	SparseMatrix<T>operator*(const SparseMatrix<T>x)const;//�ض�������˷�

	//ϡ���������rows������cols������Ԫ����terms���ܹ����ص�������Ԫ����MaxTerms
	int rows, cols;
	int terms;
	int MaxTerms;
	Term<T>* a;//һά�������洢��Ԫ��
};

template<class T>//���캯������ֵMaxTerms���������ݳ�Ա��ֵΪ0
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
	MaxTerms = maxTerms;
	a = new Term<T>[MaxTerms];
	terms = rows = cols = 0;
}

template<class T>//�������
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{
	out << "rows=" << x.rows << " columns=" << x.cols << endl;
	out << "nonzero terms=" << x.terms << endl;
	for (int i = 0; i < x.terms; i++)
	{
		out << "a(" << x.a[i].row << "," << x.a[i].col << ")=" << x.a[i].value << endl;
	}
	cout << endl;
	return out;
}

template<class T>//��������
istream& operator>>(istream& in, SparseMatrix<T>& x)
{
	cout << "Enter number of rows,columns,and terms" << endl;
	in >> x.rows >> x.cols >> x.terms;
	for (int i = 0; i < x.terms; i++)
	{
		cout << "Enter row,column,and value of term" << (i + 1) << endl;
		in >> x.a[i].row >> x.a[i].col >> x.a[i].value;
	}
	cout << endl;
	return in;
}

template<class T>//��ԭ����ת�ô洢��b��
void SparseMatrix<T>::Transpose(SparseMatrix<T>& b)const
{
	b.cols = rows;
	b.rows = cols;
	b.terms = terms;
	int* ColSize, * RowNext;
	ColSize = new int[cols + 1];
	RowNext = new int[cols + 1];
	for (int i = 1; i <= cols; i++)
		ColSize[i] = 0;
	for (int i = 0; i < terms; i++)
		ColSize[a[i].col]++;
	RowNext[1] = 0;
	for (int i = 2; i <= cols; i++)
		RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
	for (int i = 0; i < terms; i++)
	{
		int j = RowNext[a[i].col]++;
		b.a[j].row = a[i].col;
		b.a[j].col = a[i].row;
		b.a[j].value = a[i].value;
	}
}

template<class T>//ԭ�����b������Ӵ洢��c��
void SparseMatrix<T>::Add(const SparseMatrix<T>& b, SparseMatrix<T>& c)const
{
	c.rows = rows;
	c.cols = cols;
	c.terms = 0;
	int ct = 0, cb = 0;
	while (ct < terms && cb < b.terms)
	{
		int indt = a[ct].row * cols + a[ct].col;
		int indb = b.a[cb].row * cols + b.a[cb].col;
		if (indt < indb)
		{
			c.Append(a[ct]);
			ct++;
		}
		if (indt > indb)
		{
			c.Append(b.a[cb]);
			cb++;
		}
		if (indt == indb)
		{
			if (a[ct].value + b.a[cb].value)
			{
				Term<T>t;
				t.row = a[ct].row;
				t.col = a[ct].col;
				t.value = a[ct].value + b.a[cb].value;
				c.Append(t);
			}
			ct++;
			cb++;
		}
	}
	for (; ct < terms; ct++)
		c.Append(a[ct]);
	for (; cb < b.terms; cb++)
		c.Append(b.a[cb]);
}

template<class T>//�������ĩβ����Ԫ��
void SparseMatrix<T>::Append(const Term<T>& t)
{
	a[terms] = t;
	terms++;
}

template<class T>//ȥ���������кź��к���ȵ�Ԫ�صĺ��ߣ����Ұ�������Ӻ��ֵ����ǰ��
void SparseMatrix<T>::no_same()
{
	for (int i = 0; i < terms - 1; i++)
	{
		for (int j = i + 1; j < terms; j++)
		{
			if (a[i].row == a[j].row && a[i].col == a[j].col)
			{
				a[i].value += a[j].value;
				terms--;
				for (int k = j; k < terms; k++)
				{
					a[k].row = a[k + 1].row;
					a[k].col = a[k + 1].col;
					a[k].value = a[k + 1].value;
				}
				j--;
			}
		}
	}
}

template<class T>//ȥ��������ֵΪ���Ԫ��
void SparseMatrix<T>::no_zero()
{
	for (int i = 0; i < terms; i++)
	{
		if (a[i].value == 0)
		{
			terms--;
			for (int j = i; j < terms; j++)
			{
				a[j].row = a[j + 1].row;
				a[j].col = a[j + 1].col;
				a[j].value = a[j + 1].value;
			}
			i--;
		}
	}
}

template<class T>//�ض�������˷�
SparseMatrix<T> SparseMatrix<T>::operator*(const SparseMatrix<T>v)const
{
	//�˷���ǰһ��������г��Ժ�һ��������У�����һ������ת�ú�����ǰһ��������г��Ժ�һ���������
	//��Ϊ��������˳��洢�ģ����ԾͿ��Զ���ѭ�����������������е�����Ԫ����
	SparseMatrix<T>m, x;
	v.Transpose(x);
	m.rows = rows;
	m.cols = x.rows;
	//sum�ǳ˺�����������д洢λ�õ�����
	int sum = 0;
	for (int i = 0; i < terms; i++)
	{
		for (int j = 0; j < x.terms; j++)
		{
			if (a[i].col == x.a[j].col)
			{
				m.terms++;
				m.a[sum].row = a[i].row;
				m.a[sum].col = x.a[j].row;
				m.a[sum].value = a[i].value * x.a[j].value;
				sum++;
			}
		}
	}
	//����кź��к���ͬԪ�صĺ����Լ�ֵΪ���Ԫ��
	m.no_same();
	m.no_zero();
	return m;
}

int main()
{
	SparseMatrix<int>x, y;
	cout << "�������һ������" << endl;
	cin >> x;
	cout << "������ڶ�������" << endl;
	cin >> y;
	cout << "��˺�ľ���Ϊ��" << endl;
	cout << x * y;
	return 0;
}