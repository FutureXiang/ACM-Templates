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
bool v[maxn];
int n,m,num;
void addedge(int x,int y,int l)
{
    Edge *p=&E[++num];
    p->to=y;
    p->w=l;
    p->next=V[x].next;
    V[x].next=p;
}

void dijkstra(int S)
{
    for(int i=1;i<=n;i++) dis[i]=INT_MAX;
    dis[S]=0;
    memset(v,0,sizeof v);
    v[S]=1;
    for(Edge *p=V[S].next;p;p=p->next)
        dis[p->to]=min(p->w,dis[p->to]);
    for(int i=1;i<=n;++i)
    {
        int dmin=INT_MAX,dt=-1;
        for(int i=1;i<=n;++i)
        {
            if(dmin>dis[i] && !v[i])
            {
                dmin=dis[i];
                dt=i;
            }
        }
        if(dt==-1) break;
        v[dt]=true;
        for(Edge *p=V[dt].next;p;p=p->next)
        {
            int r=p->w+dis[dt];
            if(dis[p->to]>r) dis[p->to]=r;
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
