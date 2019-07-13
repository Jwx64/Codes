#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
struct Edge {
    int v, nex;
} e[1000005];
int head[200005], eum;
void addedge(int u, int v) {
    e[++eum].nex=head[u];
    head[u]=eum;
    e[eum].v=v;
}

int ans[200005], times, n, m, u, v, dfn[200005], low[200005];
void tarjan(int u, int fa) {
    dfn[u]=low[u]=++times;
    int child=0;
    for (int i=head[u]; i; i=e[i].nex) {
        int v=e[i].v;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u]=min(low[u], low[v]);
            if (low[v]>=dfn[u] && u!=fa) ans[u]=true;
            if (fa==u) child++;
        }
        low[u]=min(low[u], dfn[v]);
    }
    if (child>=2 && fa==u)
        ans[u]=true;
    return;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i=1; i<=m; i++) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    for (int i=1; i<=n; i++)
        if (!dfn[i])
            tarjan(i, i);
    vector<int> a;
    for (int i=1; i<=n; i++)
        if (ans[i])
            a.push_back(i);
    printf("%d\n", a.size());
    for (vector<int>::iterator it=a.begin(); it!=a.end(); it++)
        printf("%d ", *it);
    return 0;
}