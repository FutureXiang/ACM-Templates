#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
using namespace std;
struct trie
{
	int next[30];
	bool is_str;
}tr[100000];
int root=0,num;
char ch[100];
void insert(const char* word)
{
	int now=1;
	while(*word)
	{
		if(tr[now].next[*word-'a'+1]==0)
			tr[now].next[*word-'a'+1]=++num;
		now=tr[now].next[*word-'a'+1];
		word++;
	}
	tr[now].is_str=true;
}
bool search(const char* word)
{
	int now=1;
	while(*word&&now)
	{
		now=tr[now].next[*word-'a'+1];
		word++;
	}
	return (now&&tr[now].is_str);
}
int main(int argc, char *argv[])
{
	num=root=1;
	memset(tr[root].next,0,sizeof(tr[root].next));
	tr[root].is_str=false;

	cin>>ch;
	insert(ch);
    cin>>ch;
	insert(ch);
	cin>>ch;
	insert(ch);
	cin>>ch;
	insert(ch);
	cin>>ch;
	insert(ch);

	cin>>ch;
	cout<<search(ch)<<endl;
	cin>>ch;
	cout<<search(ch)<<endl;
	cin>>ch;
	cout<<search(ch)<<endl;

	return 0;
}
