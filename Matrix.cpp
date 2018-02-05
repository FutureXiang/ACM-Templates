#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=10;
int mat[maxn][maxn],N,P;
int tmp[maxn][maxn],res[maxn][maxn];
void mat_multi(int a[][maxn],int b[][maxn]) // a=a*b
{
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            for(int k=1;k<=N;++k)
                tmp[i][j]+=a[i][k]*b[k][j];
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            a[i][j]=tmp[i][j];
}
void mat_pow()
{
    memset(res,0,sizeof(res));
    for(int i=1;i<=N;++i) res[i][i]=1; // I(n,n)
    while(P)
    {
        if(P&1) mat_multi(res,mat);
        mat_multi(mat,mat);
        P/=2;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;++j)
            cout<<res[i][j]<<' ';
        cout<<endl;
    }
}
int main()
{
    scanf("%d%d",&N,&P);
    for(int i=1;i<=N;++i)
        for(int j=1;j<=N;++j)
            scanf("%d",&mat[i][j]);
    mat_pow();
    getchar();getchar();
    return 0;
}