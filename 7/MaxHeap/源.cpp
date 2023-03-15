#include<iostream>
#include"myExceptions.h"

using namespace std;

//���Ѷ��壺
//ÿ���ڵ��ֵ�����ڵ������ӽڵ��ֵͬʱ��һ����ȫ������
template<class T>
class MaxHeap {
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap() { delete[]heap; }
	int Size()const { return CurrentSize; }
	//�������ȼ���ߵ�Ԫ��
	T Max()
	{
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax();
	//���Ѻ���
	void Initialize(T a[], int size, int ArraySize);
	// ��������Ϊ�գ������ͷſռ䡪��������a
	void deactivateArray()
	{
		heap = NULL; CurrentSize = MaxSize = 0;
	}

	void print()
	{
		for (int i = 1; i <= CurrentSize; i++)
		{
			cout << heap[i] << " ";
		}
		cout << endl;
	}
private:
	int CurrentSize, MaxSize;
	//һά������Ч����
	//�ѽڵ��1��ʼ��ţ�������2i���Һ�����2i+1
	T* heap;
	T maxElement = 100000000;
	T minElement = -1;
};

template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[2 * MaxSize + 2];
	CurrentSize = 0;
	heap[0] = maxElement;
	for (int i = MaxSize + 1; i <= 2 * MaxSize + 1; i++)
	{
		heap[i] = minElement;
	}
}

template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	int i = ++CurrentSize;
	//�ж��ӽڵ��Ƿ�ȸ��ڵ���ǵĻ����ڵ�����

	//�Ż�����������heap[0]������ʡ��i��=1���ж�����
	//��Ϊ�������x���С��heap[1/2]=heap[0]��Ȼ������while
	//while (i != 1 && x > heap[i / 2])

	while (x > heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//��x�������λ��
	heap[i] = x;
	return *this;
}

template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax()
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	//�������һ��Ԫ��ɾ��
	//y�����������һ��Ԫ�أ�ɾ��������ڵ��λ��
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;

	//���˼�Сֵ֮���ڱȽϵ�ʱ����Ҫ�������ޣ��޸ĺ�����
	while (true)
	{
		if (heap[ci] < heap[ci + 1])
			ci++;
		if (y >= heap[ci])
			break;
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}

	heap[i] = y;
	heap[CurrentSize + 2] = minElement;
	return *this;
}

template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	//���г�ʼ��ֵ����
	delete[]heap;
	heap = a;
	CurrentSize = size;
	MaxSize = ArraySize;

	//��n/2����ʼ�����ڵ���������ʹ�乹��������
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i];
		int c = 2 * i;
		while (c <= CurrentSize)
		{
			if (c < CurrentSize && heap[c] < heap[c + 1])
				c++;
			if (y >= heap[c])
				break;
			heap[c / 2] = heap[c];
			c *= 2;
		}
		heap[c / 2] = y;
	}
}

template<class T>
void HeapSort(T a[], int n)
{
	MaxHeap<T>H(1);
	H.Initialize(a, n, n);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMax(x);
		a[i + 1] = x;
	}
	H.deactivateArray();
}

int main() {
	int n;
	cout << "���������ָ���n��";
	cin >> n;
	int* a = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		a[i] = rand() % 1000000;
	}
	MaxHeap<int> A(n);
	for (int i = 1; i <= n; i++)A.Insert(a[i]);
	A.print();
	cout << endl;
	A.DeleteMax();
	A.print();

	return 0;
}