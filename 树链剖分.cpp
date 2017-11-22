/*
tag: 树链剖分 维护 树上 修改 边权 点权 线段树
 */
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1003;
const int maxm=1003;

int flag[maxn],temp_edge[maxn];
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
    int top,vn,eid;// dfs2, eid=ID( Edge(u,u[fa]) )
}V[maxn];

//--------------------------- segment tree start
struct seg
{
    int w,lazy;
}s[maxn*3];
void lazy_down(int now,int len)
{
    s[now*2].lazy+=s[now].lazy;
    s[now*2+1].lazy+=s[now].lazy;
    s[now*2].w+=(len-len/2)*s[now].lazy;
    s[now*2+1].w+=len/2*s[now].lazy;
    s[now].lazy=0;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        s[now].w=flag[++eid_num];
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w=s[now*2].w+s[now*2+1].w;
}
void add(int now,int l,int r,int ql,int qr,int A)
{
    if(ql>qr) swap(ql,qr);
    int m=(l+r)/2;
    if(ql<=l && r<=qr)
    {
        s[now].lazy+=A;
        s[now].w+=A*(r-l+1); // !!!!!
        return;
    }
    if(s[now].lazy) lazy_down(now,r-l+1);
    if(ql<=m) add(now*2,l,m,ql,qr,A);
    if(qr>m)  add(now*2+1,m+1,r,ql,qr,A);
    s[now].w = s[now*2].w + s[now*2+1].w; // !!
}
int query(int now,int l,int r,int ql,int qr)
{
    if(ql>qr) swap(ql,qr);
    int ans=0;
    if(ql<=l && r<=qr) return s[now].w;
    int m=(l+r)/2;
    if(s[now].lazy) lazy_down(now,r-l+1);
    if(ql<=m) ans += query(now*2,l,m,ql,qr);
    if(qr>m)  ans += query(now*2+1,m+1,r,ql,qr);

    return ans;
}

//--------------------------- segment tree end

void init()
{
    E_num=eid_num=0;
    for(int i=1;i<=n;i++)
    {
	V[i].next=NULL;
	V[i].size=V[i].son=V[i].fa=V[i].dep=V[i].top=V[i].vn=V[i].eid=0;
	flag[i]=0;
    }
    for(int i=1;i<=n*3;i++)
	s[i].w=s[i].lazy=0;
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
	scanf("%d%d%d",&a,&b,&c);
	if(a>b) swap(a,b); //a=b.fa
	addedge(a,b);
	addedge(b,a);

	V[a].vn++; V[b].vn++;
	temp_edge[b]=c; // edge(b,a), a=b.fa
    }
    V[1].fa=-1; V[1].dep=1; V[1].top=1;
}
void dfs1(int u) // generate size, fa, dep, son.
{
    if(V[u].vn==0) return;
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
	    p->to=0; //del this repeated edge
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
void in_seg()
{
    eid_num=0; // for putting into segment tree
    for(int i=2;i<=n;i++)
	flag[V[i].eid]=temp_edge[i]; // edge[i.eid]=edge(i, i.fa)
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
	    if(V[a].eid<V[b].eid) ans+=query(1,1,n-1,V[a].eid+1,V[b].eid);
	    if(V[a].eid>V[b].eid) ans+=query(1,1,n-1,V[b].eid+1,V[a].eid);
	    break;
	}
	else
	{
	    if(V[t1].dep<=V[t2].dep)
	    {
		ans+=query(1,1,n-1,V[t2].eid,V[b].eid);
		b=V[t2].fa;
	    }
	    else
	    {
		ans+=query(1,1,n-1,V[t1].eid,V[a].eid);
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
            if(V[a].eid<V[b].eid) add(1,1,n-1,V[a].eid+1,V[b].eid,A);
            if(V[a].eid>V[b].eid) add(1,1,n-1,V[b].eid+1,V[a].eid,A);
            break;
        }
        else if(V[t1].dep<=V[t2].dep)
        {
            add(1,1,n-1,V[t2].eid,V[b].eid,A);
            b=V[t2].fa;
        }
        else
        {
            add(1,1,n-1,V[t1].eid,V[a].eid,A);
            a=V[t1].fa;
        }
    }
}
int main()
{
    scanf("%d",&n);
    init();
    input();

    dfs1(1);
    memset(flag,0,sizeof(0));
    dfs2(1);

    in_seg();
    build(1,1,n-1);

    int a,b;
    char op;
    while(cin>>op)
    {
	if(op=='e') break;
	cin>>a>>b;
	if(op=='q') cout<<path_sum(a,b)<<endl;
	else if(op=='a')
	{
	    int c;
	    cin>>c;
	    path_add(a,b,c);
	}
    }
    return 0;
}

