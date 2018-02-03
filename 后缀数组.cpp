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
int rk[maxl],suffix[maxl];
int height[maxl];

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
		A[i].num=String[i]-'a'+1;//precalc rk
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
	rk[A[0].p]=1;
	for(int i=0;i<len-1;i++)
	{
        if(A[i+1].num==A[i].num)
            rk[A[i+1].p]=rk[A[i].p];
        else
            rk[A[i+1].p]=rk[A[i].p]+1;
    }
    //------precalc end
    int K=1;
    while(K*2<=len)
    {
        for(int i=0;i<len;i++)
        {
            s1[i].x=rk[i];
            if(i+K<=len-1) s1[i].y=rk[i+K];
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
        rk[s1[0].p]=1;
        for(int i=0;i<len-1;i++)
	    {
            if(s1[i+1].x==s1[i].x&&s1[i+1].y==s1[i].y)
                rk[s1[i+1].p]=rk[s1[i].p];
            else
                rk[s1[i+1].p]=rk[s1[i].p]+1;
        }
        K*=2;
    }
    for(int i=0;i<len;i++) suffix[rk[i]]=i;
    
    cout<<"Rank:"<<endl;            // 某后缀排第几位
    for(int i=0;i<len;i++) cout<<rk[i]<<' ';
    cout<<endl<<"Suffix:"<<endl;    // 排某位的是哪个后缀
    for(int i=1;i<=len;i++) cout<<suffix[i]<<' ';
    cout<<endl;
}
void calc_height() // height[i]: LongestPrefix(suffix[rk[i-1]],suffix[rk[i]]) 排名相邻的两个后缀的最长公共前缀
{
    int j,k=0;
    for(int i=0;i<len;height[rk[i++]]=k) 
        for(k?k--:0,j=suffix[rk[i]-1];String[i+k]==String[j+k];k++) ;
    
    for(int i=2;i<=len;i++)
        cout<<height[i]<<' ';
    cout<<endl;
}
int main()
{
	scanf("%s",String);
	len=strlen(String);
	calc_suffix();
	// rk[0 ~ len-1] = 1 ~ len,   suffix[1 ~ len] = 0 ~ len-1
    calc_height();
    // height[2 ~ len]
	return 0;
}
