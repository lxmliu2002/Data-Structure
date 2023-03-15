#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int N = 100;
vector<int> g[N];
int start, theEnd;
int reach[N], vis[N];
int m, n;
int len;


bool bfs(int v, int label)
{// ������������� reach[i] ������ǴӶ���v�ɵ�������ж���
	len = 1;
	queue<int>q;
	reach[v] = label;
	q.push(v);
	while (!q.empty())
	{
		// �Ӷ�����ɾ��һ����ǹ��Ķ���
		int w = q.front();
		q.pop();
		if (w == theEnd)
			break;
		// �������û�е�����ڽ��ڶ���w�Ķ���
		int u;
		for (int i = 0; i < g[w].size(); i++)
		{
			u = g[w][i];
			if (!vis[u])
			{
				len++;
				reach[u] = w;
				vis[u] = 1;
				q.push(u);
			}
		}
	}
	if (len == 1)
		return false;
	return true;
}
//����ʹ��bfs��дfindpath����
bool findpath_bfs(int Start, int End) {
	reach[1] = Start;
	len = 1;
	theEnd = End;
	fill(vis, vis + n, 0);
	if (Start == End || bfs(Start, 1)) {
		reach[0] = 0;
		return true;
	}
	return false;
}
//���·���ϵĽڵ��
void show_bfs(int x) {
	if (x == start) {
		cout << x << " ";
		return;
	}
	show_bfs(reach[x]);
	cout << x << " ";
	reach[0]++;
}
int main() {
	cout << "������ڵ����ͱ���" << endl;
	cin >> n >> m;
	int u, v;
	cout << "������ÿ���������ڵ���" << endl;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cout << "��������ʼ�ڵ����ֹ�ڵ�" << endl;
	cin >> start >> theEnd;
	if (findpath_bfs(start, theEnd))
	{
		cout << "bfs·��:";
		show_bfs(theEnd);
		cout << endl;
		cout << "bfs·������:" << reach[0] << endl;
	}
	return 0;
}