#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <queue>
using namespace std;
int main()
{
    typedef pair<int,int> P;
    typedef pair<int, P> PP;
    priority_queue<PP, vector<PP>, greater<PP> > Q;
    Q.push(PP(1,P(2,3)));
    Q.push(PP(0,P(3,4)));
    Q.push(PP(0,P(3,5)));
    Q.push(PP(0,P(2,5)));
    Q.push(PP(1,P(2,1)));
    Q.push(PP(1,P(1,2)));
    while(!Q.empty())
    {
        PP now=Q.top();
        Q.pop();
        cout<<now.first<<"  "<<now.second.first<<' '<<now.second.second<<endl;
    }
    // 结果是三关键字字典序
    getchar();getchar();
    return 0;
}
