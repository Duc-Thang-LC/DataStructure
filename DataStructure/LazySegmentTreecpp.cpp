#include <iostream>
#include <algorithm>

using namespace std;

int arr[4 * 50002];
int lazy[4 * 50002];

void lazydown(int id, int l, int r)
{

	lazy[id * 2] += lazy[id];
	lazy[id * 2 + 1] += lazy[id];

	arr[id * 2] += lazy[id];
	arr[id * 2 + 1] += lazy[id];

	lazy[id] = 0;
}

void update(int id, int u, int v, int l, int r, int val)
{
	if (u > r || v < l)return;

	if (u <= l && r <= v)
	{
		lazy[id] += val;
		arr[id] += val;
		return;
	}

	lazydown(id, l, r);

	int m = (l + r) / 2;
	update(id * 2, u, v, l, m, val);
	update(id * 2 + 1, u, v, m + 1, r, val);

	arr[id] = max(arr[id * 2], arr[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v)
{
	if (l > v || r < u)return -100000;

	if (u <= l && r <= v)
	{
		return arr[id];
	}

	lazydown(id, l, r);

	int m = (l + r) / 2;
	return max(get(id * 2, l, m, u, v), get(id * 2 + 1, m + 1, r, u, v));
}

int main()
{
	int n, m;
	cin >> n >> m;

	while (m--)
	{
		int t;
		cin >> t;
		if (t == 0)
		{
			int u, v, val;
			cin >> u >> v >> val;
			update(1, u, v, 1, n, val);
		}
		else
		{
			int u, v;
			cin >> u >> v;
			cout << get(1, 1, n, u, v) << endl;
		}
	}

	return 0;
}