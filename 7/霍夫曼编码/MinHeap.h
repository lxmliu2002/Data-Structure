#pragma once
#include<iostream>
#include"myExceptions.h"
using namespace std;

//���Ѷ��壺
//ÿ���ڵ��ֵ�����ڵ������ӽڵ��ֵͬʱ��һ����ȫ������
template<class T>
class MinHeap {
public:
	MinHeap(int MaxHeapSize = 10);
	~MinHeap() { delete[]heap; }
	int Size()const { return CurrentSize; }
	//�������ȼ���ߵ�Ԫ��
	T Min()
	{
		if (CurrentSize == 0)
			throw OutOfBounds();
		return heap[1];
	}
	MinHeap<T>& Insert(const T& x);
	MinHeap<T>& DeleteMin(T& x);
	//���Ѻ���
	void Initialize(T a[], int size, int ArraySize);
	// ��������Ϊ�գ������ͷſռ䡪��������a
	void Deactivate()
	{
		heap = NULL; CurrentSize = MaxSize = 0;
	}

private:
	int CurrentSize, MaxSize;
	//һά������Ч����
	//�ѽڵ��1��ʼ��ţ�������2i���Һ�����2i+1
	T* heap;
};

template<class T>
MinHeap<T>::MinHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1];
	CurrentSize = 0;
}

template<class T>
MinHeap<T>& MinHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	int i = ++CurrentSize;
	//�ж��ӽڵ��Ƿ�ȸ��ڵ�С���ǵĻ����ڵ�����
	while (i != 1 && x < heap[i / 2])
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	//��x�������λ��
	heap[i] = x;
	return *this;
}

template<class T>
MinHeap<T>& MinHeap<T>::DeleteMin(T& x)
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	//�������һ��Ԫ��ɾ��
	x = heap[1];
	//y�����������һ��Ԫ�أ�ɾ��������ڵ��λ��
	T y = heap[CurrentSize--];
	int i = 1, ci = 2;
	while (ci <= CurrentSize)
	{
		//ʹciָ��i�����������н�С��һ��
		if (ci < CurrentSize && heap[ci] > heap[ci + 1])
			ci++;
		//����������һ��Ԫ�ر�ciС�Ļ�����ȷ������ѭ����ֵ����
		if (y <= heap[ci])
			break;
		//���ڸ��ڵ�ĺ��ӽڵ�������Ȼ���ж���һ��
		heap[i] = heap[ci];
		i = ci;
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}

template<class T>
void MinHeap<T>::Initialize(T a[], int size, int ArraySize)
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
			if (c < CurrentSize && heap[c] > heap[c + 1])
				c++;
			if (y <= heap[c])
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
	MinHeap<T>H(1);
	H.Initialize(a, n, n);
	T x;
	for (int i = n - 1; i >= 1; i--)
	{
		H.DeleteMin(x);
		a[i + 1] = x;
	}
	H.deactivateArray();
}