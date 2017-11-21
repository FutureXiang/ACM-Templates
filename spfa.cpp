/*
tag: 最短路 spfa 优化 负权回路
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
int times[maxn]; // visited times
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
	times[i]=0;
	dis[i]=~0u>>1;  //INT_MAX
	V[i].next=NULL;
    }
}
int spfa(int S, int T)
{
    deque <int> q;  // for SLF
    q.push_back(S); v[S]=true; dis[S]=0; times[S]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop_front();
	if(times[now]>n) return -2; // 负权回路
	for(Edge *p=V[now].next;p;p=p->next)
        {
            if(dis[now]+p->w<dis[p->to])
            {
                dis[p->to]=dis[now]+p->w;
                if(!v[p->to])
                {
		    if(dis[p->to]<=dis[now]) q.push_front(p->to); // Small Label First
		    else q.push_back(p->to);
                    v[p->to]=true;
		    times[p->to]++;
                }
            }
        }
        v[now]=false; // after update !!!!!!!!!!!
    }
    if(dis[T]==~0u>>1) dis[T]=-1; // can not reach T
    return dis[T];
}
int main()
{
    while(cin>>n>>m) // multi cases
    {
	init();
	int u,v,l;
	for(int i=1;i<=m;i++)
	{
	  cin>>u>>v>>l;
	  addedge(u,v,l); // directed edge
	}
	int S,T;
	cin>>S>>T; // Source & Target
	cout<<spfa(S,T)<<endl;
    }
    return 0;
}
