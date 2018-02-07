/*
tag: spfa 负环 dfs
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <deque>
using namespace std;
const int maxn=1005;
struct Edge
{
    int w;
    int to;
    Edge *next;
}E[maxn];
struct vertex
{
    Edge *next;
}V[maxn];
int n,m,E_num;

bool v[maxn];  //visited or not
int dis[maxn]; //distance from S to i

void addedge(int u,int v,int l) //directed graph
{
    Edge *p=&E[++E_num];
    p->to=v;
    p->w=l;
    p->next=V[u].next;
    V[u].next=p;
}
void init()
{
    for(int i=1;i<=n;i++)
    {
        v[i]=false;
        dis[i] = 0;     // 为了查找负权回路，初始化设为0 !!!
        V[i].next=NULL;
    }
}
bool spfa_dfs(int u)
{
    v[u]=true;
    for(Edge *p=V[u].next;p;p=p->next)
    {
        int to=p->to;
        if(dis[to]>dis[u]+p->w)
        {
            dis[to]=dis[u]+p->w;
            if(v[to]) return true; // !!!
            else
                if(spfa_dfs(to)) return true;
        }
    }
    v[u]=false; // !!!
    return false;
}
int main()
{
    while(cin>>n>>m)
    {
	    init();
        int u,v,l;
        for(int i=1;i<=m;i++)
        {
            cin>>u>>v>>l;
            addedge(u,v,l); // directed edge
        }
        bool flag=false;
        for(int i=1;i<=n;++i)
        {
            flag=spfa_dfs(i);
            if(flag) break;
        }
        if(flag) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
