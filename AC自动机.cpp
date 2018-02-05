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
}tr[100000];
int root=0,num,N;
void insert(const string &in)
{
	int now=1;
	for(auto &ch:in)
	{
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
				if(is_find)break;
			}
			tr[now].fail=result; // (son of root).fail=root.
#ifdef DEBUG
			cout<<now<<' '<<tr[now].fail<<endl;
#endif
		}
		for(int i=0;i<26;i++)
		{
			if(tr[now].next[i])
				q.push(tr[now].next[i]);
		}
	}
}
int query(const string &q)
{
	int node=root;
	int res=0;
	for(auto &ch:q)
	{
		while(node && !tr[node].next[ch-'a']) node=tr[node].fail;
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
	string in;
	init();
	cin>>N;
	for(int i=1;i<=N;i++)
	{
		cin>>in;
		insert(in);
	}
}
int main()
{	
	readin();
	calc_fail();
	string q;
	cin>>q;
	cout<<query(q)<<endl;
	getchar();getchar();
	return 0;
}
