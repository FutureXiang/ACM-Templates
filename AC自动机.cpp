#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;
struct trie
{
	int next[26];
	int cnt_str;
	int f,fail;
	char ch;
}tr[1003];
int root=0,num,N,CharNum;
int TrieG[102][102];
void insert(const char *in)
{
	int now=1;
	for(int i=0;i<strlen(in);++i)
	{
		char ch=in[i];
		if(!tr[now].next[ch-'a'])
		{
			tr[now].next[ch-'a']=++num;
			tr[num].f=now;
			tr[num].ch=ch;
		}
		now=tr[now].next[ch-'a'];
	}
	tr[now].cnt_str++;
}
void calc_fail()
{
	queue<int> q;
	q.push(root);
	while (!q.empty())
	{
		int now=q.front();
		q.pop();
		if(now!=root)
		{
			int tnow=tr[now].f;
			int c=tr[now].ch;
			bool is_find=false;
			int result=root;
			while (tnow!=root)
			{
				tnow=tr[tnow].fail;
				for(int i=0;i<26;i++)
				{
					if(tr[tr[tnow].next[i]].ch==c&&tr[tnow].next[i]!=now)
					{
						is_find=true;
						result=tr[tnow].next[i];
						break;
					}
				}
				if(is_find) break;
			}
			tr[now].fail=result; // (son of root).fail=root.
#ifdef DEBUG
			cout<<now<<' '<<tr[now].fail<<endl;
#endif
		}
		for(int i=0;i<CharNum;i++)
		{
			if(tr[now].next[i])
			{
				q.push(tr[now].next[i]);
				TrieG[now][i]=tr[now].next[i];
			}
			else
				TrieG[now][i]=TrieG[tr[now].fail][i]; // Trie Graph: node * Char
		}
	}
}
int query(const string &q)
{
	int node=root;
	int res=0;
	for(auto &ch:q)
	{
		while(node!=root && !tr[node].next[ch-'a']) node=tr[node].fail;
		if(tr[node].next[ch-'a'])
		{
			node=tr[node].next[ch-'a'];
			int tmp=node; // ?
			while(tmp!=root)
			{
				res+=tr[tmp].cnt_str;
				#ifdef DEBUG
				if(tr[tmp].cnt_str) cout<<"ended with :"<<ch<<endl;
				#endif
				tmp=tr[tmp].fail;
				//tr[tmp].cnt_str=0; // 相同的只算一次的话
			}
		}
	}
	return res;
}
void init()
{
	num=root=1;
	memset(tr[root].next,0,sizeof(tr[root].next));
	tr[root].cnt_str=0; tr[root].f=-1; tr[root].fail=root; tr[root].ch=' ';
}
void readin()
{
	char in[100];
	init();
	cin>>N>>CharNum;
	for(int i=1;i<=N;i++)
	{
		cin>>in;
		insert(in);
	}
}
int TrieCount[1003][1003];
int main()
{	
	readin();
	calc_fail();
	for(int i=1;i<=num;i++)
	{
		cout<<i<<": ";
		for(int j=0;j<CharNum;j++)
		{
			cout<<' '<<TrieG[i][j];
			TrieCount[i][TrieG[i][j]?TrieG[i][j]:1]++;
		}
		cout<<endl;
	}
	for(int i=1;i<=num;i++)
	{
		cout<<i<<": ";
		for(int j=1;j<=num;j++)
			cout<<' '<<TrieCount[i][j];
		cout<<endl;
	}
	string q;
	cin>>q;
	cout<<query(q)<<endl;
	getchar();getchar();
	return 0;
}
// http://www.cppblog.com/menjitianya/archive/2014/07/10/207604.html