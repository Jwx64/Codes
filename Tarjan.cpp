割点：
void tarjan_point(int i, int fd) //给边上标号来判定重边
{
    dfn[i] = low[i] = ++dfs_clock;
    int j, id, chd = 0;
    for (int p = first[i]; p; p = E[p].next)
    {
        j = E[p].to, id = E[p].id;
        if (dfn[j])
        {
            if (dfn[j] < dfn[i] && id != fd)
                low[i] = min(low[i], dfn[j]); //利用返祖边更新low函数
            continue;
        }
        chd++;
        tarjan_point(j, id);
        if (low[j] >= dfn[i])
            mark[i] = 1;              //只要i有一个儿子满足lowj>=dfni就说明i是割点
        low[i] = min(low[i], low[j]); //利用树边更新low函数
    }
    if (fd == 0 && chd == 1)
        mark[i] = 0; //对于开始遍历的根结点需要特殊判断，可能这个点不是割点
}



割边：
void tarjan_edge(int i, int fd) //给边上标号来判定重边
{
    dfn[i] = low[i] = ++dfs_clock;
    int j, id;
    for (int p = first[i]; p; p = E[p].next)
    {
        j = E[p].to, id = E[p].id;
        if (dfn[j])
        {
            if (dfn[j] < dfn[i] && id != fd)
                low[i] = min(low[i], dfn[j]); //利用返祖边更新low函数
            continue;
        }
        tarjan_edge(j, id);
        low[i] = min(low[i], low[j]); //和儿子的连边更新low函数
        if (low[j] == dfn[j])
        {
            a[++cnt] = (data){min(i, j), max(i, j)};
            mark[id] = 1; //改成判定这一条指向儿子的边是不是割边，此写法也不受重边的影响。
        }
    }
}



边双连通分量：
void tarjan_edge(int i, int fd)
{
    dfn[i] = low[i] = ++dfs_clock;
    stk[++top] = i;
    int j, id;
    for (int p = first[i]; p; p = E[p].next)
    {
        j = E[p].to, id = E[p].id;
        if (dfn[j])
        {
            if (dfn[j] < dfn[i] && id != fd)
                low[i] = min(low[i], dfn[j]);
            continue;
        }
        tarjan_edge(j, id);
        low[i] = min(low[i], low[j]);
        if (low[j] == dfn[j]) //第一次发现割边就应该算成一个边双连通分量
        {
            mark[id] = 1;
            ebc_cnt++;
            while (1)
            {
                int x = stk[top--];
                ebc[ebc_cnt]++;
                ebcno[x] = ebc_cnt;
                if (x == j)
                    break;
            }
            MAX_ebc = max(MAX_ebc, ebc[ebc_cnt]);
        }
    }
    if (!fd && top) //改了写法之后需要特殊处理遍历树的根结点
    {
        ebc_cnt++;
        while (top)
        {
            int x = stk[top--];
            ebc[ebc_cnt]++;
            ebcno[x] = ebc_cnt;
        }
        MAX_ebc = max(MAX_ebc, ebc[ebc_cnt]);
    }
}



点双连通分量（割点的分量标号没什么意义）：
void tarjan_point(int i, int fd)
{
    dfn[i] = low[i] = ++dfs_clock;
    stk[++top] = i;
    int j, id, chd = 0;
    for (int p = first[i]; p; p = E[p].next)
    {
        j = E[p].to, id = E[p].id;
        if (dfn[j])
        {
            if (dfn[j] < dfn[i] && fd != id)
                low[i] = min(low[i], dfn[j]);
            continue;
        }
        chd++;
        tarjan_point(j, id);
        low[i] = min(low[i], low[j]);
        if (low[j] >= dfn[i]) //注意判定条件和边双连通分量的区别
        {
            mark[i] = 1;
            bcc_cnt++;
            bcc[bcc_cnt]++;
            bccno[i] = 0;
            while (1)
            {
                int x = stk[top--];
                bcc[bcc_cnt]++;
                bccno[x] = bcc_cnt;
                if (x == j)
                    break;
            }
            MAX_bcc = max(MAX_bcc, bcc[bcc_cnt]);
        }
    }
    if (fd == 0 && chd == 1)
        mark[i] = 0;
}



强连通分量：
void tarjan_scc(int i)
{
    dfn[i] = low[i] = ++dfs_clock;
    stk[++top] = i;
    for (int p = first[i]; p; p = E[p].next)
    {
        int j = E[p].to;
        if (dfn[j])
        {
            if (!sccno[j])
                low[i] = min(low[i], dfn[j]); //反向边更新low函数
            continue;
        }
        tarjan_scc(j);
        low[i] = min(low[i], low[j]);
    }
    if (low[i] == dfn[i])
    {
        scc_cnt++;
        while (1)
        {
            int x = stk[top--];
            sccno[x] = scc_cnt;
            if (x == i)
                break;
        }
    }
}