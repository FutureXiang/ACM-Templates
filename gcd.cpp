/*
tag: gcd 最大公约数 最大公因子 辗转 大数
 */
#include <iostream>
#include <algorithm>
using namespace std;
long long gcd(long long x,long long y)
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
//1100100210001,120200021 1
//10897286400,12893126400 39916800
//9223372036854775806,9223372036854775800 6
int main()
{
    long long a,b;
    cin>>a>>b;
    cout<<gcd(a,b)<<endl;
    return 0;
}
