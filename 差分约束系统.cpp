/*
tag: 差分约束 不等式 spfa 负权回路 负环
based on POJ3169, but WA.
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
const int maxn=1003;
const int maxm=10004;
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
int n,ML,MD,E_num;

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
    for(int i=0;i<=n;i++)
    {
	v[i]=false;
	times[i]=0;
	dis[i]=~0u>>1;  //INT_MAX
	V[i].next=NULL;
    }
}
int spfa(int S)
{
    deque <int> q;  // for SLF
    q.push_back(S); v[S]=true; dis[S]=0; times[S]=1;
    while(!q.empty())
    {
        int now=q.front();
        q.pop_front();
	if(times[now]>n) return -1; // 负权回路
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
    for(int i=1;i<=n;i++)
	if(dis[i]==~0u>>1) return -2; // 不确定
    return dis[n];
}
int main()
{
    scanf("%d%d%d",&n,&ML,&MD);
    init();
    for(int i=1;i<=ML;++i) // cows like each other
    {
	int a,b,l;
	scanf("%d%d%d",&a,&b,&l);//x(b)-x(a)<=l  --> dis[a]+l >= dis[b]
	addedge(a,b,l);
    }
    for(int i=1;i<=MD;i++) // cows dislike each other
    {
	int a,b,l;
	scanf("%d%d%d",&a,&b,&l);//x(b)-x(a)>=l  --> x(a)-x(b)<=-l --> dis[b]+ (-l) >= dis[a]
	addedge(b,a,-l);
    }
    for(int i=1;i<=n-1;i++)
	addedge(i+1,i,0);

    cout<<spfa(1)<<endl; // 求x(n)-x(1)的最大值
    return 0;
}
