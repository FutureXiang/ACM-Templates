#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxL=100005;
const int maxl=10004;
char a[maxL],b[maxl];
int la,lb;
int nxt[maxl];
void get_next()
{
    int j=0;
    for(int i=1;i<lb;i++) // preprocess "next array"
    {
	    while(j>0&&b[i]!=b[j]) j=nxt[j-1]; // j-1!
	    if(b[i]==b[j]) j++;
	    nxt[i]=j;
    }
}
void readin()
{
    scanf("%s%s",a,b);
    la=strlen(a);
    lb=strlen(b);
    memset(nxt,0,sizeof(nxt));
}
int main()
{
    readin();
    get_next();
    int j=0;
    int cnt=0;
    for(int i=0;i<la;i++)
    {
        while(j>0 && a[i]!=b[j]) j=nxt[j-1]; // j-1! (restore j->j-1->nxt[j-1])
        if(a[i]==b[j]) j++;
        if(j==lb)
        {
            printf("start with %d\n",i-lb+1);
            cnt++;
            j=nxt[j-1]; // j-1!，以便继续匹配。令j=0，如果要求不重叠的话。
        }
    }
    printf("Appeared %d times.\n",cnt);
    getchar();getchar();
    return 0;
}
