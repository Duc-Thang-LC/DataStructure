// Đây là code Segment Tree cổ điển

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int ST[40002];
const int oo = -1000002;

void update(int i, int val, int node, int l, int r)
{
	if (i < l || i > r)return;
	if (i == l && l == r)
	{
		ST[node] = val;
		return;
	}
	int mid = (l + r) / 2;
	update(i, val, node * 2, l, mid);
	update(i, val, node * 2 + 1, mid + 1, r);
	ST[node] = max(ST[node * 2], ST[node * 2 + 1]);
}

int getmax(int u, int v, int node, int l, int r)
{
	if (u > r || v < l)return -oo;
	if (u <= l && r <= v)return ST[node];
	int mid = (l + r) / 2;
	return max(getmax(u, v, node * 2, l, mid), getmax(u, v, node * 2 + 1, mid + 1, r));
}

int main()
{
	int n, q;
	cin >> n >> q;
	while (q--)
	{
		int x;
		cin >> x;
		if (x == 1)
		{
			int i, val;
			cin >> i >> val;
			update(i, val, 1, 0, n - 1);
		}
		else
		{
			int l, r;
			cin >> l >> r;
			cout << getmax(l, r, 1, 0, n - 1) << endl;
		}
	}
}
