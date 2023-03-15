#include<iostream>
using namespace std;

template <typename T>
class lowerTriangularMatrix
{
public:
	template<typename T>
	friend ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x);//�������������
	template<typename T>
	friend istream& operator>>(istream& in, lowerTriangularMatrix<T>& x);//������������
	lowerTriangularMatrix(int size);//���캯�������ɴ�СΪsize��n�׷��󣬲����ɱ��������ǵ�ֵ��һά����
	lowerTriangularMatrix();//���캯�������ɴ�СΪsize��n�׷��󣬲����ɱ��������ǵ�ֵ��һά����
	~lowerTriangularMatrix();//�����������ͷ�һά����Ŀռ�
	void Outpuut1(ostream& out)const;//������ӡ����þ���
	void Outpuut2(ostream& out)const;//������ӡ����þ���
	void transpose(lowerTriangularMatrix<T>& x)const;//������xת��
	lowerTriangularMatrix<T>operator+(const lowerTriangularMatrix<T>& x)const;//����+�����
	lowerTriangularMatrix<T>operator-(const lowerTriangularMatrix<T>& x)const;//����-�����
	lowerTriangularMatrix<T>& Store(const T& x, int i, int j);//�޸ľ���ֵ
	T Retrieve(int i, int j)const;//��ȡ�����ֵ
private:
	int n;
	T* t;
};

template<typename T>//�������������
istream& operator>>(istream& in, lowerTriangularMatrix<T>& x)
{
	for (int i = 0; i < x.n * (x.n + 1) / 2; i++)
	{
		in >> x.t[i];
	}
	return in;
}

template<typename T>//������������
ostream& operator<<(ostream& out, const lowerTriangularMatrix<T>& x)
{
	x.Outpuut1(out);
	return out;
}

template <typename T>//���캯�������ɴ�СΪsize��n�׷��󣬲����ɱ��������ǵ�ֵ��һά����
lowerTriangularMatrix<T>::lowerTriangularMatrix(int size)
{
	n = size;
	t = new T[n * (n + 1) / 2];
}

template <typename T>//���캯�������ɴ�СΪsize��n�׷��󣬲����ɱ��������ǵ�ֵ��һά����
lowerTriangularMatrix<T>::lowerTriangularMatrix()
{

}

template<typename T>//�����������ͷ�һά����Ŀռ�
lowerTriangularMatrix<T>::~lowerTriangularMatrix()
{
	delete[]t;
}

template<typename T>//������ӡ����þ���
void lowerTriangularMatrix<T>::Outpuut1(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			cout << t[i * (i - 1) / 2 + j] << " ";
		}
		for (int j = 0; j < n - i; j++)
		{
			cout << 0 << " ";
		}
		cout << endl;
	}
}

template<typename T>//������ӡ����þ���
void lowerTriangularMatrix<T>::Outpuut2(ostream& out)const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j < i; j++)
		{
			cout << 0 << " ";
		}
		for (int j = 0; j <= n - i; j++)
		{
			cout << t[(2 * n - i + 2) * (i - 1) / 2 + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template<typename T>//������xת��
void lowerTriangularMatrix<T>::transpose(lowerTriangularMatrix<T>& x)const
{
	int count1 = 0, count2 = 0, position = 0, temp = 0;
	for (int i = 1; i <= n; i++)
	{
		temp = i;//temp��һ���м�������ʾԭ����ͬ��Ԫ���������е�λ�ò�ֵ
		count1 = i * (i + 1) / 2;//count��ʾԭ����ǰi�е�Ԫ�ظ���
		position = count1;
		for (int j = 0; j <= n - i; j++)
		{
			//ij��ʾԭ�����i�е�j��Ԫ���������е�λ��
			x.t[count2 + j] = t[position - 1];
			position += temp;
			temp++;
		}
		count2 += (n - i + 1);//temp2���¾���ǰn-1��Ԫ�ظ���
	}
}

template<typename T>//����+�����
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator+(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] + x.t[i];
	}
	return y;
}

template<typename T>//����-�����
lowerTriangularMatrix<T>lowerTriangularMatrix<T>::operator-(const lowerTriangularMatrix<T>& x)const
{
	lowerTriangularMatrix<T>y;
	for (int i = 0; i < n * (n + 1) / 2; i++)
	{
		y.t[i] = t[i] - x.t[i];
	}
	return y;
}

template<typename T>//�޸ľ���ֵ
lowerTriangularMatrix<T>& lowerTriangularMatrix<T>::Store(const T& x, int i, int j)
{
	t[i * (i - 1) / 2 + j - 1] = x;
	return *this;
}

template<typename T>//��ȡ�����ֵ
T lowerTriangularMatrix<T>::Retrieve(int i, int j)const
{
	if (i >= j)
	{
		return t[i * (i - 1) / 2 + j - 1];
	}
	else
	{
		return 0;
	}
}

int main()
{
	cout << "��ѡ��ʵ���������ͣ�" << endl;
	cout << "A.����   B.С��   C.�ַ�" << endl;
	char m;
L:cin >> m;
	if (m == 'A')
	{
		int size;
		cout << endl << "������ԭ�����Ǿ����������";
		cin >> size;
		lowerTriangularMatrix<int>x(size), y(size);
		cout << endl << "������ԭʼ���飺" << endl;
		cin >> x;
		cout << endl << "ת��ǰ�������Ǿ���Ϊ��" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "ת�ú�������Ǿ���Ϊ��" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'B')
	{
		int size;
		cout << endl << "������ԭ�����Ǿ����������";
		cin >> size;
		lowerTriangularMatrix<float>x(size), y(size);
		cout << endl << "������ԭʼ���飺" << endl;
		cin >> x;
		cout << endl << "ת��ǰ�������Ǿ���Ϊ��" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "ת�ú�������Ǿ���Ϊ��" << endl;
		y.Outpuut2(cout);
	}
	if (m == 'C')
	{
		int size;
		cout << endl << "������ԭ�����Ǿ����������";
		cin >> size;
		lowerTriangularMatrix<char>x(size), y(size);
		cout << endl << "������ԭʼ���飺" << endl;
		cin >> x;
		cout << endl << "ת��ǰ�������Ǿ���Ϊ��" << endl;
		x.Outpuut1(cout);
		x.transpose(y);
		cout << "ת�ú�������Ǿ���Ϊ��" << endl;
		y.Outpuut2(cout);
	}
	if (m != 'A' && m != 'B' && m != 'C')
	{
		cout << "����������������룺" << endl;
		goto L;
	}
	return 0;
}