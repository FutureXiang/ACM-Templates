#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <queue>
using namespace std;
const int maxn=1003;

int map[maxn][maxn];
int degree[maxn];
int n,m,num;

vector<int> Array;
void topo()
{
    priority_queue<int, vector<int>, greater<int> > q; // 优先队列：拓扑序字典序最小
    for(int i=1;i<=n;++i)
        if(degree[i]==0) q.push(i);
    while(!q.empty())
    {
        int now=q.top();
        q.pop();
        Array.push_back(now);
        for(int i=1;i<=n;++i)
        {
            if(!map[now][i]) continue;
            int to=i;
            if(degree[to]==0) continue;
            degree[to]--;
            if(degree[to]==0)
                q.push(to);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int u,v;
    memset(map,0,sizeof map);
    memset(degree,0,sizeof degree);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        // 本题可能出现重边，则应该使用邻接矩阵（重边时避免反复degree++）
        if(map[u][v]==0) degree[v]++;
        map[u][v]=1;
    }
    topo();
    if(Array.size()<n) printf("Not A DAG!\n");
    for(auto &i: Array)
        cout<<i<<endl;
    getchar();getchar();
    return 0;
}
