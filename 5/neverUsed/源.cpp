#include<iostream>
using namespace std;

template<typename T1,typename T2>
class HashTable
{
public:
	HashTable(int divisor);//���캯������һ��divisor���ȵ��������֮ƥ���bool���ͳ�ֵȫΪtrue��empty��neverUsed����
	bool Search(const T1& t1, const T2& t2)const;//�����������жϹؼ���Ϊt2��λ�õ�ֵ�Ƿ�Ϊt1
	HashTable<T1, T2>& Insert(const T1& t);//���뺯������t�������Ӧ��λ��
	HashTable<T1, T2>& Delete(const T2& t);//����ɾ�����꺯����Ҫɾ���ļ�Ϊt������λ��
	void Output();//�������������λ�õ�ǰ�ǿյ�������������
	void NewHash();//ɢ�����麯��
private:
	int hSearch(const T2& t);//���Ҳ������꺯����Ѱ���ʺ�k��������������λ��
	int dSearch(const T2& t);//����ɾ�����꺯����Ҫɾ���ļ�Ϊk������λ��
	int divisor;//����
	T1* ht;//��ȡԭʼ����
	bool* empty;//�жϵ�ǰλ���Ƿ�Ϊ�գ�Ϊ����ɲ���Ԫ��
	bool* neverUsed;//�жϵ�ǰλ���Ƿ�ʹ�ù�
};
template<typename T1, typename T2>//���캯������һ��divisor���ȵ��������֮ƥ���bool���ͳ�ֵȫΪtrue��empty��neverUsed����
HashTable<T1, T2>::HashTable(int divisor)
{
	this->divisor = divisor;
	ht = new T1[this->divisor];
	empty = new bool[this->divisor];
	neverUsed = new bool[this->divisor];
	for (int i = 0; i < this->divisor; i++)
	{
		empty[i] = neverUsed[i] = true;
	}
}
template<typename T1, typename T2>//�������������λ�õ�ǰ�ǿյ�������������
void HashTable<T1, T2>::Output()
{
	cout << "��ǰͰ�е�Ԫ��Ϊ��" << endl;
	for (int i = 0; i < this->divisor; i++)
	{
		if (!empty[i])
		{
			cout << "(" << i << ")" << ht[i] << " ";
		}
	}
	cout << endl;
}
template<typename T1, typename T2>//���Ҳ������꺯����Ѱ���ʺ�k��������������λ��
int HashTable<T1, T2>::hSearch(const T2& t)
{
	int i = t % this->divisor;
	int j = i;
	do
	{
		if (empty[j] || ht[j] == t)//��jλ���ǿյĻ���jλ��ԭ����������t��ֱ�ӷ���j
		{
			return j;
		}
		j = (j + 1) % this->divisor;//����һ��λ���Ƿ�Ϊ�ջ���Ϊj
	} while (j != i);
	return j;
}
template<typename T1, typename T2>//����ɾ�����꺯����Ҫɾ���ļ�Ϊk������λ��
int HashTable<T1, T2>::dSearch(const T2& t)
{
	int i = t % this->divisor;
	int j = i;
	do
	{
		if (neverUsed[j] || ht[j] == t)//��jλ�ñ�ʹ�ù�����jλ��ԭ����������k��ֱ�ӷ���j
		{
			return j;
		}
		j = (j + 1) % this->divisor;//����һ��λ���Ƿ�Ϊ�ջ���Ϊj
	} while (j != i);
	return j;
}
template<typename T1, typename T2>//�����������жϹؼ���Ϊt2��λ�õ�ֵ�Ƿ�Ϊt1
bool HashTable<T1, T2>::Search(const T1& t1, const T2& t2)const
{
	int b = hSearch(t2);
	if (empty[b] || ht[b] != t2)
	{
		cout << "û���ҵ�" << t2 << "���Ԫ��" << endl;
		return false;
	}
	cout << "Ԫ��" << t2 << "�ڵ�" << b << "��Ͱ��" << endl;
	return true;
}
template<typename T1, typename T2>//���뺯������t�������Ӧ��λ��
HashTable<T1, T2>& HashTable<T1, T2>::Insert(const T1& t)
{
	T2 t2 = t;
	//b��ʾ�ʺ�k�����λ������
	int b = hSearch(t);
	//����λ��Ϊ�գ���b���뼴��
	if (empty[b])
	{
		empty[b] = neverUsed[b] = false;
		ht[b] = t;
		return *this;
	}
	//����λ�õ�ֵ�Ѿ�Ϊk���ʾû�пռ�����ظ�Ԫ�ػ�����һ��������������ˣ��������꺯��j=i����ht[j]!=k��ֱ�ӷ���*this����
	return *this;
}
template<typename T1, typename T2>//����ɾ�����꺯����Ҫɾ���ļ�Ϊt������λ��
HashTable<T1, T2>& HashTable<T1, T2>::Delete(const T2& t)
{
	int b = dSearch(t);
	if (ht[b] == t)
	{
		if (empty[b] == true)
		{
			cout << "�ظ�ɾ��" << endl;
		}
		else
		{
			//��ɾ��һ��Ԫ�غ�Ҫ�ж��ѿ�λ��������ʹ�ù����Ƿ񳬹�60%���ǵĻ���������
			empty[b] = true;
			int sum1 = 0;//sum1��¼�ѿ�λ������
			int sum2 = 0;//sum2��¼�ѿ�λ��������ʹ�ù�������
			for (int i = 0; i < this->divisor; i++)
			{
				if (empty[i])//����ѿգ�sum1++
				{
					sum1++; 
					if (!neverUsed[i])//���������ʹ�ù���sum2++
					{
						sum2++;
					}
				}
			}
			if (float(sum1 / sum2) > 0.6)
			{
				NewHash();
			}
		}
	}
	else
	{
		cout << "δ�ҵ���ӦԪ��" << endl;
	}
	return *this;
}
template<typename T1, typename T2>//ɢ�����麯��
void HashTable<T1, T2>::NewHash()
{
	for (int i = 0; i < this->divisor; i++)
	{
		if (empty[i] == true && neverUsed[i] == false)
		{
			neverUsed[i] = true;
			continue;
		}
		if (empty[i] == false)
		{
			T1 t1 = ht[i];
			T2 t2 = t1;
			//�жϴ�λ�õ�Ԫ���Ƿ�Ӧ�ò��뵽��λ��
			int b = hSearch(t2);
			//�ǵĻ�������һ��ѭ��
			if (b == i)
			{
				continue;
			}
			//���ǵĻ�����λ�õ�empty��neverUsed����Ϊtrue��ʾ��λ��û��Ԫ�أ�Ȼ�󽫶�ӦԪ�ز��뵽����λ��
			empty[i] = true;
			neverUsed[i] = true;
			Insert(t1);
		}
	}
}
int main()
{
	int num, delnum;
	cout << "������Ԫ������:";
	cin >> num;
	HashTable<int, int>zqzy(num);
	for (int i = 0; i < num; i++)
	{
		int k;
		cout << "�������" << i + 1 << "��Ҫ����ļ�k��ֵ:";
		cin >> k;
		zqzy.Insert(k);
	}
	zqzy.Output();
	cout << "������Ҫɾ����Ԫ����:";
	cin >> delnum;
	for (int i = 0; i < delnum; i++)
	{
		int k;
		cout << "�������" << i + 1 << "��Ҫɾ���ļ�k��ֵ:";
		cin >> k;
		zqzy.Delete(k);
	}
	zqzy.Output();
	return 0;
}

