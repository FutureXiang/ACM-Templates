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

bool v[maxn];
int dis[maxn];

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
    for(int i=1;i<=n;i++)
    {
	v[i]=false;
	dis[i]=~0u>>1;
	V[i].next=NULL;
    }
}
int spfa(int S, int T)
{
    deque <int> q;
    q.push_back(S); v[S]=true; dis[S]=0;
    while(!q.empty())
    {
        int now=q.front();
        q.pop_front();
	for(Edge *p=V[now].next;p;p=p->next)
        {
            if(dis[now]+p->w<dis[p->to])
            {
                dis[p->to]=dis[now]+p->w;
                if(!v[p->to])
                {
		    if(dis[p->to]<=dis[now]) q.push_front(p->to);
		    else q.push_back(p->to);
                    v[p->to]=true;
                }
            }
        }
        v[now]=false; // after update!!!!!!!!!!!
    }
    if(dis[T]==~0u>>1) dis[T]=-1;
    return dis[T];
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
	  addedge(u,v,l);
	}
	int S,T;
	cin>>S>>T;
	cout<<spfa(S,T)<<endl;
    }
    return 0;
}
