#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int gcd(int x,int y)
{
    if(x<y)return gcd(y,x);
    if(!y)return x;
    else
    {
	if(x/2*2==x)
	{
	    if(y/2*2==y) return(gcd(x>>1,y>>1)<<1);
	    else return gcd(x>>1,y);
	}
	else
	{
	    if(y/2*2==y)return gcd(x,y>>1);
	    else return gcd(y,x-y);
	}
    }
}
typedef pair<int,int> P;
P ex_gcd(int i,int j)
{
    P temp,ret;
    if(j==0)
    {
        temp.first=1;
        temp.second=0;
        return temp;
    }
    temp=ex_gcd(j,i%j);
    ret.first=temp.second;
    ret.second=temp.first-i/j*temp.second;
    return ret;
}
P solve(int a,int b,int c)
{
	int d=gcd(a,b);
	P result;
    result=ex_gcd(a,b); // ax + by = d
	if(c/d*d==c)          // d | c
	{
		int temp=((long long)result.first*(c/d))%b;
		while(temp<=0) temp+=b/d;
        while(temp-b/d>0) temp-=b/d;
		return P(temp,(c-(long long)a*temp)/b);
	}
	else return P(-1,-1);
}
// -1 -1 :    No Solution
// Others: The Smallest(x!) Z+ Solution
int main()
{
    // ax=c(mod b)  <=> ax+by=c
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    
    P result=solve(a,b,c);
    cout<<result.first<<' '<<result.second<<endl;

#ifndef ONLINE_JUDGE
    getchar();getchar();
#endif
    return 0;
}
