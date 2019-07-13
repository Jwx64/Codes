#include <iostream>
using namespace std;
#define N 100005

long long a[N], tr[N << 2], tag[N << 2];

inline int ls(int x) { return x << 1; }
inline int ls(int x) { return x << 1 | 1; }
inline void push_up_sum(int p)
{
	tr[p] = tr[ls(p)] + tr[rs(p)];
}
void build(int p, int l, int r)
{
	if (l == r)
	{
		tr[p] = a[l];
		return;
	}
	int mid = l + (r - l) >> 1;
	build(ls(p), l, mid);
	build(rs(p), mid + 1, r);
	push_up_sum(p);
}
inline void l_tag(int p, int k, int l, int r)
{
	tag[p] += k;
	tr[p] += k * (r - l + 1);
}
inline void push_down(int p, int l, int r)
{
	int mid = (l + r) >> 1;
	l_tag(ls(p), tag[p], l, mid);
	l_tag(rs(p), tag[p], mid + 1, r);
	tag[p] = 0;
}
inline void update(int ql, int qr, int l, int r, int p, int k)
{
	if (ql <= l && qr >= r)
	{
		l_tag(l, r, p, k);
		return;
	}
	push_down(l, r, p);
	int mid = (l + r) >> 1;
	if (ql <= mid)
		update(ql, qr, l, mid, ls(p), k);
	if (qr > mid)
		update(ql, qr, mid + 1, r, rs(p), k);
	push_up_sum(p);
}
inline ll query(int ql, int qr, int l, int r, int p)
{
	if (ql <= l && qr >= r)
		return tr[p];
	long long res = 0;
	int mid = (l + r) >> 1;
	push_down(l, r, p);
	if (ql <= mid)
		res += query(ql, qr, l, mid, ls(p));
	if (qr > mid)
		res += query(ql, qr, mid + 1, r, rs(p));
	return res;
}
