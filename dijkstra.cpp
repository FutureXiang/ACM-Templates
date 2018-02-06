#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <queue>
using namespace std;
const int maxn=30004;
const int maxm=60004;
struct Edge
{
    int w;
    int to;
    Edge *next;
}E[maxm];
struct vertex
{
    Edge *next;
}V[maxn];
int dis[maxn];
int n,m,num;
void addedge(int x,int y,int l)
{
    Edge *p=&E[++num];
    p->to=y;
    p->w=l;
    p->next=V[x].next;
    V[x].next=p;
}
typedef pair<int,int> P;
void dijkstra(int S)
{
    priority_queue<P, vector<P>, greater<P> > q;
    q.push(P(0,S)); // pair greater: 按first第一，second第二。

    for(int i=1;i<=n;i++) dis[i]=INT_MAX;
    dis[S]=0;
    while(!q.empty())
    {
        P now=q.top();
        q.pop();
        int nowto=now.second,nowd=now.first;
        if(dis[nowto]!=nowd) continue;
        for(Edge *p=V[nowto].next;p;p=p->next)
        {
            int v=p->to, r=p->w+dis[nowto];
            if(dis[v]>r)
            {
                dis[v]=r;
                q.push(P(v,dis[v]));
            }
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int u,v,l;
    for(int i=1;i<=n;i++) V[i].next=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&l);
        addedge(u,v,l);
    }
    dijkstra(1);
    for(int i=1;i<=n;++i)
        cout<<dis[i]<<endl;
    getchar();getchar();
    return 0;
}
