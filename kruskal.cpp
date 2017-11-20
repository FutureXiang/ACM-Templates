#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn=1003;
const int maxm=10004;
int n,m,f[maxn],k;
struct edge
{
       int x,y,w;
}s[maxm];
bool cmp_edge(edge x,edge y)
{
     return x.w<y.w;
}
int find(int x)
{
    if(x!=f[x]) return f[x]=find(f[x]);
    else return f[x];
}
void kruskal()
{
    int ans=0;
    for(int i=1;i<=n;i++) f[i]=i;
    sort(s+1,s+m+1,cmp_edge);

    for(int i=1;i<=m;i++)
    {
	int p=find(s[i].x);
	int q=find(s[i].y);
	if(q!=p)
	{
	    ans+=s[i].w;
	    f[q]=p;
	}
    }
    bool flag=true;
    for(int i=1;i<n;i++)
    {
	if(find(i)!=find(i+1)) 
	{
	    flag=false;
            break;
	}
    }
    if(flag)printf("%d\n",ans);
    else printf("?\n");
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>s[i].x>>s[i].y>>s[i].w;
    kruskal();
    return 0;
}
