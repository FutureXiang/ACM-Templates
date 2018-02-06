#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;
int a[10005],N;
int amin[10005][15]; //从第i个数起，连续2^j个数的最小值。
void RMQ()
{
    for(int i=1;i<=N;++i)
        amin[i][0]=a[i];
    for(int j=1;j<=14;++j) // 先求低阶j的。
    {
        for(int i=1;i<=N;++i)
        {
            if(i+(1<<j)-1 > N) continue; // out of range
            amin[i][j]=min(amin[i][j-1],amin[i+(1<<(j-1))][j-1]);
        }
    }
}
int query(int x,int y) // 找到两个覆盖区间，如min(a[2,7]) = min(a[2,5],[4,7])
{
    if(x>y) swap(x,y);
    int k=(int)(log(double(y-x)+1.0)/log(2.0));
    return min( amin[x][k], amin[y-(1<<k)+1][k] );
}
int main()
{
    int Q;
    cin>>N>>Q;
    for(int i=1;i<=N;++i) cin>>a[i];
    RMQ();
    while(Q--)
    {
        int x,y;
        cin>>x>>y;
        cout<<query(x,y)<<endl;
    }
    getchar();getchar();
    return 0;
}
// PreProcess O(nlogn), Query O(1)