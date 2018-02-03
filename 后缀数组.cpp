#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxl=10000;
char String[maxl];//input
int len;// len of String
int rank[maxl],suffix[maxl];
int cnt[maxl]; //sorting arrays
struct sort1
{
	int p,num;
}A[maxl],B[maxl];
struct sort2
{
    int x,y,p;
}s1[maxl],s2[maxl];

void calc_suffix()
{
	for(int i=0;i<=len-1;i++)
	{
		A[i].num=String[i]-'a'+1;//precalc rank
		A[i].p=i;
	}
	memset(cnt,0,sizeof(cnt));
    for(int i=0;i<=len-1;i++) cnt[A[i].num&31]++;
    for(int i=1;i<=31;i++) cnt[i]+=cnt[i-1];
    for(int i=len-1;i>=0;i--) B[--cnt[A[i].num&31]]=A[i];
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<=len-1;i++) cnt[B[i].num>>5]++;
    for(int i=1;i<=31;i++) cnt[i]+=cnt[i-1];
    for(int i=len-1;i>=0;i--) A[--cnt[B[i].num>>5]]=B[i];
	rank[A[0].p]=1;
	for(int i=0;i<len-1;i++)
	{
        if(A[i+1].num==A[i].num)
            rank[A[i+1].p]=rank[A[i].p];
        else
            rank[A[i+1].p]=rank[A[i].p]+1;
    }
    //------precalc end
    int K=1;
    while(K*2<=len)
    {
        for(int i=0;i<len;i++)
        {
            s1[i].x=rank[i];
            if(i+K<=len-1) s1[i].y=rank[i+K];
            else s1[i].y=0;
            s1[i].p=i;
        }
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<=len-1;i++) cnt[s1[i].y]++;
        for(int i=1;i<=len;i++) cnt[i]+=cnt[i-1];
        for(int i=len-1;i>=0;i--) s2[--cnt[s1[i].y]]=s1[i];
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<=len-1;i++) cnt[s2[i].x]++;
        for(int i=1;i<=len;i++) cnt[i]+=cnt[i-1];
        for(int i=len-1;i>=0;i--) s1[--cnt[s2[i].x]]=s2[i];
        rank[s1[0].p]=1;
        for(int i=0;i<len-1;i++)
	    {
            if(s1[i+1].x==s1[i].x&&s1[i+1].y==s1[i].y)
                rank[s1[i+1].p]=rank[s1[i].p];
            else
                rank[s1[i+1].p]=rank[s1[i].p]+1;
        }
        K*=2;
    }
    for(int i=0;i<len;i++) cout<<rank[i]<<' ';
    cout<<endl;
    for(int i=0;i<len;i++) suffix[rank[i]]=i+1;
    for(int i=1;i<=len;i++) cout<<suffix[i]<<' ';
    cout<<endl;
}
int main()
{
	scanf("%s",String);
	len=strlen(String);
	calc_suffix();
	//rank:0~len-1  suffix:1~len
	return 0;
}
