#include<iostream>
using namespace std;
int n, m;
typedef long long ll;
#define MAX 200001
ll sum[MAX << 2];
int mm[MAX << 2];
ll lazy[MAX << 2];
int a[MAX];
char c;
int le, ri, p;

inline void pushup(int rt) 
{
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	mm[rt] = min(mm[rt << 1], mm[rt << 1 | 1]);
}

inline void pushdown(int rt, int l, int r)
{
	lazy[rt << 1] += lazy[rt], lazy[rt << 1 | 1] += lazy[rt];
	int mid = (l + r) / 2;
	sum[rt << 1] += lazy[rt] * (mid - l + 1);
	sum[rt << 1 | 1] += lazy[rt] * (r - mid);
	mm[rt << 1] += lazy[rt];
	mm[rt << 1 | 1] += lazy[rt];
	lazy[rt] = 0;
}

void build(int l, int r, int cur)
{
	if (l == r)
	{
		sum[cur] = a[l];
		mm[cur] = a[l];
		return;
	}
	int mid = (l + r)>>1;
	build(l, mid, cur << 1);
	build(mid + 1, r, cur << 1 | 1);
	pushup(cur);
}

ll Sum(int L, int R, int l, int r, int cur)
{
	if (l >= L && r <= R)
		return sum[cur];
	if (lazy[cur])
		pushdown(cur, l, r);
	int mid = (l + r) >> 1;
	ll res = 0;
	if (mid >= L)
		res += Sum(L, R, l, mid, cur << 1);
	if (mid < R)
		res += Sum(L, R, mid + 1, r, cur << 1 | 1);
	return res;
}

ll Min(int L, int R, int l, int r, int cur)
{
	if (l>=L&&r<=R)
		return mm[cur];
	if (lazy[cur])
		pushdown(cur, l, r);
	int mid = (l + r) >> 1;
	if (mid >= R)
		return Min(L, R, l, mid, cur << 1);
	else if (mid < L)
		return Min(L, R, mid + 1, r, cur << 1 | 1);
	return min(Min(L, R, l, mid, cur << 1), Min(L, R, mid + 1, r, cur << 1 | 1));
}

void update(int L, int R, int l, int r, int cur, int z)
{
	if (l >= L&&r <= R)
	{
		sum[cur] += (ll)z * (r - l + 1);
		mm[cur] += z;
		lazy[cur] += z;
		return;
	}
	if (lazy[cur])
		pushdown(cur, l, r);
	int mid = (l + r) >> 1;
	if (mid >= L)
		update(L, R, l, mid, cur << 1, z);
	if (mid < R)
		update(L, R, mid + 1, r, cur << 1 | 1, z);
	pushup(cur);
}

int main()
{
	ios::sync_with_stdio(false);
	//memset(lazy, 0, sizeof(lazy));
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	build(1, n, 1);
	for (int i = 0; i < m; i++)
	{
		cin >> c;
		if (c == 'M')
		{
			cin >> le >> ri;
			cout << Min(le, ri, 1, n, 1) << '\n';
		}
		else if (c == 'S')
		{
			cin >> le >> ri;
			cout<<Sum(le, ri, 1, n, 1)<<'\n';
		}
		else
		{
			cin >> le >> ri >> p;
			update(le, ri, 1, n, 1, p);
		}
	}
	return 0;
}