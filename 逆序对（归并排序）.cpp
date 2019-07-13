#include <bits/stdc++.h>
using namespace std;
long long ans = 0;
int n, a[500005], s[500005];
void msort(int l, int r)
{
    if (l == r)
        return;
    int mid = l + ((r - l) >> 1);
    msort(l, mid);
    msort(mid + 1, r);
    int i = l, j = mid + 1, t = l;
    while (i <= mid && j <= r)
        if (a[i] <= a[j])
            s[t++] = a[i++];
        else
            s[t++] = a[j++],
            ans += (long long)mid - i + 1;
    while (i <= mid)
        s[t++] = a[i++];
    while (j <= r)
        s[t++] = a[j++];
    for (int i = l; i <= r; i++)
        a[i] = s[i];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    msort(1, n);
    printf("%lld\n", ans);
    return 0;
}