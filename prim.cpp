#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
using namespace std;
const int maxn=1003;
const int maxm=10004;

struct Edge
{
    int w;
    int to; 
    Edge *next;
}E[maxm*2];
struct vertex
{
    Edge *next;
}V[maxn];
int n,m,E_num;
int dis[maxn];
bool v[maxn];

void addedge(int u,int v,int l)
{
    Edge *p=&E[++E_num];
    p->to=v;
    p->w=l;
    p->next=V[u].next;
    V[u].next=p;
}
void init()
{
    E_num=0;
    for(int i=0;i<=n;++i)
    {
        V[i].next=0;
        dis[i]=INT_MAX;
        v[i]=false;
    }
}
int prim(int S)
{
    int ans=0,connected=0;
    dis[S]=0;
    for(int i=1;i<=n;++i)
    {
        int dt=-1,dmin=INT_MAX;
        for(int i=1;i<=n;++i)
        {
            if(dis[i]<dmin && !v[i])
            {
                dmin=dis[i];
                dt=i;
            }
        }
        if(dt==-1) break;
        connected++;
        v[dt]=true;
        ans+=dis[dt];
        for(Edge *p=V[dt].next;p;p=p->next)
            dis[p->to] = min(dis[p->to], p->w);
    }
    if(connected<n) return -1;
    return ans;
}
int main()
{
    cin>>n>>m;
    init();
    int u,v,l;
    for(int i=1;i<=m;i++)
    {
        cin>>u>>v>>l;
        addedge(u,v,l);
        addedge(v,u,l);
    }
    cout<<prim(1)<<endl;
    getchar();getchar();
    return 0;
}
