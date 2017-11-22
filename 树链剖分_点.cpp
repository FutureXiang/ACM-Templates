/*
tag: 树链剖分 维护 树上 修改 边权 点权 线段树 最大值
 */
#include <iostream>
#include <climits>
#include <string>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=30004;
const int maxm=90004;

int flag[maxn],value[maxn],temp[maxn];
int n,eid_num,E_num;

struct edge
{
    int to;
    edge *next;
}E[maxm];
struct vertex
{
    edge *next;
    int size,fa,dep,son; // dfs1
    int top,eid;// dfs2, eid=ID(u) 根据访问顺序
}V[maxn];

//--------------------------- segment tree start
struct seg
{
    int w,lazy;
    int mmax;
}s[maxn*3];
void lazy_down(int now,int len)
{
    s[now*2].lazy+=s[now].lazy;
    s[now*2+1].lazy+=s[now].lazy;
    s[now*2].w+=(len-len/2)*s[now].lazy;
    s[now*2+1].w+=len/2*s[now].lazy;
    s[now*2].mmax+=s[now].lazy;
    s[now*2+1].mmax=s[now].lazy;
    s[now].lazy=0;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        s[now].mmax=s[now].w=temp[++eid_num]; //线段树下标是eid
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w=s[now*2].w+s[now*2+1].w;
    s[now].mmax=max(s[now*2].mmax,s[now*2+1].mmax);
}
void add(int now,int l,int r,int ql,int qr,int A)
{
    if(ql>qr) swap(ql,qr);
    int m=(l+r)/2;
    if(ql<=l && r<=qr)
    {
        s[now].lazy+=A;
        s[now].w+=A*(r-l+1); // !!!!!
	s[now].mmax+=A;
        return;
    }
    if(s[now].lazy) lazy_down(now,r-l+1);
    if(ql<=m) add(now*2,l,m,ql,qr,A);
    if(qr>m)  add(now*2+1,m+1,r,ql,qr,A);
    s[now].w = s[now*2].w + s[now*2+1].w; // !!
    s[now].mmax=max(s[now*2].mmax,s[now*2+1].mmax);
}
int query(int now,int l,int r,int ql,int qr, int flag) //flag=0: sum; 1:max
{
    if(ql>qr) swap(ql,qr);
    int ans=0, mmax=INT_MIN;
    if(ql<=l && r<=qr) return flag==0?s[now].w:s[now].mmax;
    int m=(l+r)/2;
    if(s[now].lazy) lazy_down(now,r-l+1);
    if(flag==0)
    {
        if(ql<=m) ans += query(now*2,l,m,ql,qr,flag);
	if(qr>m)  ans += query(now*2+1,m+1,r,ql,qr,flag);
    }
    else if(flag==1)
    {
        if(ql<=m) mmax = max(mmax,query(now*2,l,m,ql,qr,flag));
	if(qr>m)  mmax = max(mmax,query(now*2+1,m+1,r,ql,qr,flag));
    }
    return flag==0?ans:mmax;
}

//--------------------------- segment tree end

void init()
{
    E_num=eid_num=0;
    for(int i=1;i<=n;i++)
    {
	V[i].next=NULL;
	V[i].size=V[i].son=V[i].fa=V[i].dep=V[i].top=V[i].eid=0;
	flag[i]=temp[i]=0;
    }
    for(int i=1;i<=n*3;i++)
    {
	s[i].w=s[i].lazy=0;
	s[i].mmax=INT_MIN; //注意负数
    }
}
void addedge(int x,int y)
{
    edge *p=&E[++E_num];
    p->to=y;
    p->next=V[x].next;
    V[x].next=p;
}
void input()
{
    int a,b,c;
    for(int i=1;i<=n-1;i++)
    {
	scanf("%d%d",&a,&b);
	addedge(a,b);
	addedge(b,a);
    }
    for(int i=1;i<=n;i++) scanf("%d",&value[i]);
    V[1].fa=-1; V[1].dep=1; V[1].top=1;
}
void dfs1(int u) // generate size, fa, dep, son.
{
    if(u==0) return;
    flag[u]=1;
    for(edge *p=V[u].next;p;p=p->next)
    {
	int to=p->to;
	if(!flag[to])
	{
	    V[to].dep=V[u].dep+1;
	    V[to].fa=u;
	    flag[to]=1;
	    dfs1(to);
	    V[u].size+=(V[to].size+1); // +1
	}
	else
	{
	    p->to=0; //删除回边
	    continue;
	}
    }
    int maxx=-1;
    for(edge *p=V[u].next;p;p=p->next)
    {
	int to=p->to;
	if(V[to].size>maxx && to!=0)
	{
	    maxx=V[to].size;
	    V[u].son=to;
	}
    }
}
void dfs2(int u) // generate son, eid, top.
{
    int son=V[u].son;
    if(son==0) return;
    V[son].top=V[u].top;
    V[son].eid=++eid_num;
    dfs2(son);

    for(edge *p=V[u].next;p;p=p->next)
    {
	int to=p->to;
	if(to!=0 && to!=son)
	{
	    V[to].top=to;
	    V[to].eid=++eid_num;
	    dfs2(to);
	}
    }
}

void print1()
{
    for(int i=1;i<=n;i++)
	cout<<V[i].top<<' ';
    cout<<endl;
}
void print2()
{
    for(int i=1;i<=n;i++)
	cout<<V[i].eid<<' ';
    cout<<endl;
}
//work start----------------------------------------------
int path_sum(int a,int b) //PATH From A to B
{
    int ans=0;
    while(1)
    {
	int t1=V[a].top,t2=V[b].top;
	if(t1==t2) //同一条链上
	{
	    if(V[a].eid<=V[b].eid) ans+=query(1,1,n,V[a].eid,V[b].eid,0);
	    if(V[a].eid>V[b].eid) ans+=query(1,1,n,V[b].eid,V[a].eid,0);
	    break;
	}
	else
	{
	    if(V[t1].dep<=V[t2].dep)
	    {
		ans+=query(1,1,n,V[t2].eid,V[b].eid,0);
		b=V[t2].fa;
	    }
	    else
	    {
		ans+=query(1,1,n,V[t1].eid,V[a].eid,0);
		a=V[t1].fa;
	    }
	}
    }
    return ans;
}
int path_max(int a,int b) //PATH From A to B
{
    int ans=INT_MIN;
    while(1)
    {
	int t1=V[a].top,t2=V[b].top;
	if(t1==t2) //同一条链上
	{
	    if(V[a].eid<=V[b].eid) ans=max(ans,query(1,1,n,V[a].eid,V[b].eid,1));
	    if(V[a].eid>V[b].eid) ans=max(ans,query(1,1,n,V[b].eid,V[a].eid,1));
	    break;
	}
	else
	{
	    if(V[t1].dep<=V[t2].dep)
	    {
		ans=max(ans,query(1,1,n,V[t2].eid,V[b].eid,1));
		b=V[t2].fa;
	    }
	    else
	    {
		ans=max(ans,query(1,1,n,V[t1].eid,V[a].eid,1));
		a=V[t1].fa;
	    }
	}
    }
    return ans;
}
void path_add(int a,int b,int A)
{
    while(1)
    {
        int t1=V[a].top,t2=V[b].top;
        if(t1==t2) //同一条链上
        {
            if(V[a].eid<=V[b].eid) add(1,1,n,V[a].eid,V[b].eid,A);
            if(V[a].eid>V[b].eid) add(1,1,n,V[b].eid,V[a].eid,A);
            break;
        }
        else if(V[t1].dep<=V[t2].dep)
        {
            add(1,1,n,V[t2].eid,V[b].eid,A);
            b=V[t2].fa;
        }
        else
        {
            add(1,1,n,V[t1].eid,V[a].eid,A);
            a=V[t1].fa;
        }
    }
}
void in_seg()
{
    for(int i=1;i<=n;i++)
	temp[V[i].eid]=value[i]; //原本为节点号，现在是eid
}
int main()
{
    scanf("%d",&n);
    init();
    input();

    dfs1(1);
    dfs2(1);

    for(int i=1;i<=n;i++) V[i].eid++; // 为了适应线段树从1开始
    eid_num=0;
    in_seg();
    build(1,1,n); //以点的eid为下标

    int a,b;
    int Q;
    scanf("%d", &Q);
    char op[10];
    while(Q--)
    {
	scanf("%s", op);
	scanf("%d%d", &a, &b);
	if(op[0]=='m') printf("%d\n", path_max(a, b));
	else if(op[0]=='s') printf("%d\n", path_sum(a, b));
	else if(op[0]=='c')
	    path_add(a,a,b-path_sum(a,a)); //改成b
    }
    return 0;
}
/* 注意
max时要取INT_MIN，可能有负数
点老id和eid之间的转换
线段树下标是eid
*/
