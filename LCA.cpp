/*
tag: 最近公共祖先 LCA lca 倍增 树上距离 
 */
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=10004;
const int maxd=20;

int n,m,E_num,root;
int fa[maxn][maxd],dep[maxn];//fa[i][j]: node i's (2^j)th parent
bool flag[maxn];

struct Edge
{
    int to;
    Edge *next;
}E[maxn];
struct vertex
{
    Edge *next;
}V[maxn];

void addedge(int u,int v) // undirected edge
{
    Edge *p=&E[++E_num];
    p->to=v;
    p->next=V[u].next;
    V[u].next=p;
    
    Edge *q=&E[++E_num];
    q->to=u;
    q->next=V[v].next;
    V[v].next=q;
}
void bfs(int root)
{
    queue <int> q;
    q.push(root);
    dep[root]=0;
    fa[root][0]=root; // root's parent = root
    while(!q.empty())
    {
	int now=q.front();
	q.pop();
	for(int i=1;i<maxd;i++)
	    fa[now][i]=fa[fa[now][i-1]][i-1];
	for(Edge *p=V[now].next;p;p=p->next)
	{
	    int to=p->to;
	    if(to==fa[now][0]) continue;
	    dep[to]=dep[now]+1;
	    fa[to][0]=now;
	    q.push(to);
	}
    }
}
int LCA(int u,int v)
{
    int tu=u,tv=v;
    if(dep[tu]>dep[tv])swap(tu,tv);
    int dep_diff=dep[tv]-dep[tu];

    for(int i=0; dep_diff>0; i++,dep_diff/=2)
	if(dep_diff%2) tv=fa[tv][i]; // jump to the same depth
    if(tu==tv)return tu;

    for(int i=maxd-1;i>=0;i--)
    {
	if(fa[tu][i]==fa[tv][i]) continue; // Common Ancestors
	tu=fa[tu][i];
	tv=fa[tv][i];
    }
    return fa[tu][0];
}
int main()
{
    int Q;
    scanf("%d%d",&n,&Q); // n nodes, Q queries
    m=n-1;
    int u,v;
    for(int i=1;i<=m;i++)  // input A TREE!!!!
    {
	scanf("%d%d",&u,&v); // u is v's parent!
	addedge(u,v); // undirected edge
	flag[v]=true; // find root
    }
    int root=1;
    for(int i=1;i<=n;i++)
    {
	if(!flag[i])
	{
	    root=i;
	    break;
	}
    }
    bfs(root);

    int qu,qv;
    while(Q--)
    {
	scanf("%d%d",&qu,&qv); // query LCA(qu, qv)
	printf("%d\n",LCA(qu,qv));
    }
    /*
    如果想查询qu与qv间的距离，只需预处理出每个点到root的距离droot[]
    显然有：
    dist[qu,qv] = droot[qu] + droot[qv] - 2*droot[LCA(qu,qv)]
     */
    return 0;
}

