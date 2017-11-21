/*
tag: dinic 网络流 最大流 增广
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=1003;
const int maxm=1003;
struct Edge
{
    int w,to;
    Edge *next,*inv;
}E[maxm];
struct Vertex
{
    Edge *next;
}V[maxn];
int n,m,E_num;
int level[maxn];

void init()
{
    E_num=0;
    for(int i=1;i<=n;i++) V[i].next=NULL;
    int a,b,l;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&l);
        Edge *p=&E[++E_num];
        p->next=V[a].next;p->to=b;p->w=l;
        
	Edge *q=&E[++E_num];
        q->next=V[b].next;q->to=a;q->w=0; // 0!
        
	p->inv=q;q->inv=p;
	V[a].next=p;V[b].next=q;
    }
}
int makelevel()
{
    queue<int> q;
    for(int i=1;i<=n;i++) level[i]=-1;
    q.push(1);
    level[1]=0;
    while(!q.empty())
    {
        int now=q.front();
        q.pop();
        for(Edge *p=V[now].next;p;p=p->next)
        {
            if(level[p->to]==-1&&p->w>0)
            {
                q.push(p->to);
                level[p->to]=level[now]+1;
            }
        }
        if(level[n]!=-1) break;
    }
    return level[n]>0;
}
int find(int now,int f)
{
    if(now==n) return f;
    for(Edge *p=V[now].next;p;p=p->next)
    {
        if(level[p->to]==level[now]+1&&p->w>0)
        {
            int newf=find(p->to,min(f,p->w)); // min(f, p->w):可流过
            if(newf)
            {
                p->w-=newf;
                p->inv->w+=newf; // 反向弧流量增加
                return newf;
            }
            else
                level[p->to]=0; //FASTER!!!!!
        }
    }
    return 0;
}
void dinic()
{
    int ans=0,d;
    while(makelevel()) // bfs建层次图，直到流不到汇点
    {
        while(d=find(1,99999999)) //dfs继续增广
            ans+=d;
    }
    printf("%d\n",ans);
}
int main()
{
    scanf("%d%d",&m,&n); // Source: 1 Target: n
    init();
    dinic();
    return 0;
}
