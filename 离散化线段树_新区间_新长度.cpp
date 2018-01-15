#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,T,N;
struct seg
{
    int w,lazy;
}s[300005*8];
struct Qs
{
    int l,r,k;
}Q[300005];
int points[300005*2],P;
int length(int l,int r)
{
    return points[r+1]-points[l];
}
void lazy_down(int now,int l,int r)
{
    int m=(l+r)/2;
    s[now*2].lazy=s[now].lazy;
    s[now*2+1].lazy=s[now].lazy;
    s[now*2].w=length(l,m)*s[now].lazy; // len:should be original length
    s[now*2+1].w=length(m+1,r)*s[now].lazy;     // not len/2 and len-len/2
    s[now].lazy=-1;
}
void build(int now,int l,int r)
{
    if(l==r)
    {
        s[now].w=points[l+1]-points[l];//[points[i],points[i+1]-1]
#ifdef debug
	cout<<l<<": "<<points[l]<<' '<<points[l+1]-1<<endl;
#endif
        return;
    }
    s[now].lazy=-1; //!!!
    int m=(l+r)/2;
    build(now*2,l,m);
    build(now*2+1,m+1,r);
    s[now].w = s[now*2].w + s[now*2+1].w;
}
void change(int now,int l,int r,int ql,int qr,int A)
{
    if(r<ql||l>qr) return;
    int m=(l+r)/2;
    if(ql<=l && r<=qr)
    {
        s[now].w=A*length(l,r); // original length!!!
	s[now].lazy=A; // lazy=-1(default!!) / 0 / 1
        return;
    }
    if(l==r) return;
    if(s[now].lazy!=-1) lazy_down(now,l,r);
    if(ql<=m) change(now*2,l,m,ql,qr,A);
    if(qr>m)  change(now*2+1,m+1,r,ql,qr,A);
    s[now].w = s[now*2].w + s[now*2+1].w;
}
int query(int now,int l,int r,int ql,int qr)
{
    if(r<ql||l>qr) return 0;
    int ans=0;
    if(ql<=l && r<=qr) return s[now].w;
    int m=(l+r)/2;
    if(l==r) return 0;
    if(s[now].lazy!=-1) lazy_down(now,l,r);
    if(ql<=m) ans += query(now*2,l,m,ql,qr);
    if(qr>m)  ans += query(now*2+1,m+1,r,ql,qr);
    return ans;
}
int main()
{
    scanf("%d%d",&N,&T);
    for(int i=1;i<=T;i++)
    {
	scanf("%d%d%d",&Q[i].l,&Q[i].r,&Q[i].k);
	points[++P]=Q[i].l;
	points[++P]=Q[i].r+1; //including Q[i].r : [Q[i].l,Q[i.r+1])
    }
    points[++P]=1;
    points[++P]=N+1;
    sort(points+1,points+P+1);
    n=unique(points+1,points+P+1)-points-1;
    //points[1,n-1], points[n]=N+1.
    build(1,1,n-1);

    for(int i=1;i<=T;i++)
    {
	int l,r;
	l=lower_bound(points+1,points+n+1,Q[i].l)-points;
	r=lower_bound(points+1,points+n+1,Q[i].r+1)-points -1; //!!!!!!!
#ifdef debug
	cout<<"Q:"<<l<<' '<<r<<endl; //new point:[l,r] == [Q[i].l,Q[i].r]
#endif
	if(Q[i].k==1)
	    change(1,1,n-1,l,r,0);
	else
	    change(1,1,n-1,l,r,1);
#ifdef debug
	for(int j=1;j<=n-1;j++)
	    cout<<query(1,1,n-1,j,j)<<' ';
	cout<<endl;
#endif
	printf("%d\n",s[1].w);
	//cout<<query(1,1,n-1,1,n-1)<<endl;
    }
    return 0;
}
