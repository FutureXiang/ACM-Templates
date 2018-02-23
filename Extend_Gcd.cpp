#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int gcd(int x,int y)
{
	if(y==0) return x;
	return gcd(y,x%y);
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
    result=ex_gcd(a,b);
	if(c%d==0) //d|c
	{
		int temp=(result.first*(c/d))%b;
		while(temp<=0)temp+=b;
		return P(temp,(c-a*temp)/b);
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
