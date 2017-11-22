/*
tag: 线段树 seg 区间修改 区间查询 逆序 全局第k大数
 */
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
using namespace std;
const int maxn=10005;

int n;
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
        scanf("%d",&s[now].w);
	s[now].mmax=s[now].w;
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w = s[now*2].w + s[now*2+1].w; // !!
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
void init()
{
    for(int i=1;i<=n*3;i++)
    {
	s[i].w=s[i].lazy=0;
	s[i].mmax=INT_MIN; //注意负数
    }
}
int main()
{
    scanf("%d",&n);
    init();
    build(1,1,n);
    char op[10];
    int x,y,z;
    while(cin>>op)
    {
	if(op[0]=='e') break;
	if(op[0]=='a')
	{
	    scanf("%d%d%d",&x,&y,&z);
	    add(1,1,n,x,y,z);
	}
	else if(op[0]=='s')
	{
	    scanf("%d%d",&x,&y);
	    cout<<query(1,1,n,x,y,0)<<endl;
	}
	else if(op[0]=='m')
	{
	    scanf("%d%d",&x,&y);
	    cout<<query(1,1,n,x,y,1)<<endl;
	}
    }
    return 0;
}
