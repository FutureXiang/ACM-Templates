/*
tag: 强连通分量 tarjan 缩点 有向图 dfs
 */
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
const int maxn=10004;
const int maxm=100005;
int n,m,E_num;
int dfn[maxn],low[maxn];
int cnt_dfs;
int stack[maxn],cnt_stack;
bool instack[maxn];

struct edge
{
    int to;
    edge *next;
}E[maxm];
struct vertex
{
    edge *next;
}V[maxn];
void addedge(int a,int b)
{
    edge *p=&E[++E_num];
    p->to=b;
    p->next=V[a].next;
    V[a].next=p;
}

void tarjan(int u)
{
    dfn[u]=low[u]=++cnt_dfs;
    stack[++cnt_stack]=u;
    instack[u]=true;
    for(edge *p=V[u].next;p;p=p->next)
    {
        int v=p->to;
        if(dfn[v]==0) // not visited
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else if(instack[v]==true)
            low[u]=min(low[u],dfn[v]);
    }

    if(dfn[u]==low[u])
    {
        cout<<u<<':';
        int v=stack[cnt_stack];
        while(u!=v)
        {
            cout<<v<<' ';
            cnt_stack--;
            instack[v]=false;
            v=stack[cnt_stack];
        }
        cout<<u<<endl;
        cnt_stack--;
        instack[u]=false;
    }
}
void init()
{
    E_num=0;
    for(int i=1;i<=n;i++) 
    {
	V[i].next=0;
	dfn[i]=low[i]=0;
	instack[i]=false;
	stack[i]=0;
    }
    cnt_dfs=cnt_stack=0;
}

int main()
{
    scanf("%d%d",&n,&m);
    int a,b;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&a,&b);
        addedge(a,b);
    }
    tarjan(1); //有时不连通，有时不从1开始.注意判断!
    return 0;
}
/*
Low(u)=Min
{
    DFN(u),
    Low(v),(u,v)为树枝边, u为v的父节点
    DFN(v),(u,v)为指向栈中节点的后向边(非横叉边)
}
*/
