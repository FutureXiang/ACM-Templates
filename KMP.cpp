#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
char a[100005],b[10004];
int la,lb;
int next[10004];

// http://www.matrix67.com/blog/archives/115

int main()
{
    scanf("%s%s",a,b);
    la=strlen(a);
    lb=strlen(b);
    memset(next,0,sizeof(next));
    
    int j=0;
    for(int i=1;i<lb;i++) // preprocess "next array": for shifting string b
    {
	while(j>0&&b[i]!=b[j]) j=next[j-1]; // j-1!
	if(b[i]==b[j]) j++;
	next[i]=j;
    }

    j=0; // updating j
    int cnt=0;
    for(int i=0;i<la;i++)
    {
	while(j>0&&a[i]!=b[j]) j=next[j-1]; // j-1! (restore j->j-1->next[j-1])
	if(a[i]==b[j])j++;
	if(j==lb)
	{
	    printf("start with %d\n",i-lb+1);
	    cnt++;
	    j=next[j-1]; // j-1!
	}
    }
    printf("%d\n",cnt);
    return 0;
}
