/*
tag: 线段树 seg 区间修改 区间查询 逆序 全局第k大数
 */
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn=10005;
struct seg
{
    int w,lazy;
}s[maxn*3];
int n;
void lazy_down(int now,int len)
{
    s[now*2].lazy   += s[now].lazy; //lazy down
    s[now*2+1].lazy += s[now].lazy;

    s[now*2].w   += (len-len/2)*s[now].lazy; // add lazy
    s[now*2+1].w += len/2*s[now].lazy;
    
    s[now].lazy=0; // reset lazy
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        scanf("%d",&s[now].w);
        return;
    }
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w = s[now*2].w + s[now*2+1].w; // !!
}
void add(int now,int l,int r,int ql,int qr,int A)
{
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
    int ans=0;
    if(ql<=l && r<=qr) return s[now].w;
    int m=(l+r)/2;
    if(s[now].lazy) lazy_down(now,r-l+1);
    if(ql<=m) ans += query(now*2,l,m,ql,qr);
    if(qr>m)  ans += query(now*2+1,m+1,r,ql,qr);

    return ans;
}
void init()
{
    for(int i=1;i<=n*3;i++)
	s[i].w=s[i].lazy=0;
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
	else if(op[0]=='q')
	{
	    scanf("%d%d",&x,&y);
	    cout<<query(1,1,n,x,y)<<endl;
	}
    }
    return 0;
}
