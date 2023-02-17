#include <iostream>
#include <vector>
using namespace std;

const int N = 100;
int n, m, label;
int vis[N], flag[N];
vector<int> g[N];
void dfs(int x, int reach[], int label)
{// �����������. reach[i] ������������ڽ��ڶ���v�Ŀɵ���Ķ���
	reach[x] = 1;
	flag[x] = label;
	for (int i = 0; i < g[x].size(); i++)
	{
		int y = g[x][i];
		if (reach[y] == 0)// y ��һ��û�е���Ķ���
		{
			// ������������ݹ鷽��
			dfs(y, reach, label);
		}
	}
}
int lablecomponents(int c[])
{// ������ͼ�Ĺ��������
	// ���ع����ĸ���
	// �� c[i] �Ƕ��� i �Ĺ�����
	// ȷ����һ������ͼ
	fill(c, c + n + 1, 0);
	label = 0;
	for (int i = 1; i <= n; i++)
	{
		if (c[i] == 0)// ���� i δ����
		{// ���� i ��һ���¹���
			dfs(i, c, label); // ���¹�������� 
			label++;
		}
	}
	return label;
}
int main() {
	cout << "������ڵ����ͱ���" << endl;
	cin >> n >> m;
	cout << "������ÿ�������ߵĽڵ���" << endl;
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	lablecomponents(vis);
	cout << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (flag[i] == flag[j] && i != j)
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	return 0;
}