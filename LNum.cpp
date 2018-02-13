#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxL=100;
struct LNum
{
    int a[maxL],len; // 0 ~ len-1    
    void operator = (const LNum &o)
    {
        memset(a,0,sizeof a);
        len=o.len;
        for(int i=0;i<len;++i)
            a[i]=o.a[i];
    }
    LNum operator + (const LNum &o)
    {
        LNum ret={{0},0};
        for(int i=0;i<max(len,o.len);++i)
        {
            int tmp=ret.a[i]+a[i]+o.a[i];
            if(tmp>=10)
            {
                ret.a[i]=tmp-10;
                ret.a[i+1]=1;
                ret.len=i+2;
            }
            else
            {
                ret.a[i]=tmp;
                ret.len=i+1;
            }
        }
        return ret;
    }
    LNum operator - (const LNum &o)
    {
        LNum ret={{0},0};
        for(int i=0;i<len;++i)
        {
            int tmp=ret.a[i]+a[i]-o.a[i];
            if(tmp<0)
            {
                ret.a[i]=tmp+10;
                ret.a[i+1]=-1;
                ret.len=i+2;
            }
            else
            {
                ret.a[i]=tmp;
                ret.len=i+1;
            }
        }
        return ret;
    }
    LNum operator * (const LNum &o)
    {
        LNum ret={{0},0};
        for(int j=0;j<o.len;++j)
        {
            LNum t={{0},0};
            for(int i=0;i<len;++i)
            {
                int tmp=t.a[i]+a[i]*o.a[j];
                if(tmp>=10)
                {
                    t.a[i+1]=tmp/10;
                    t.a[i]=tmp-t.a[i+1]*10;
                    t.len=i+2;
                }
                else
                {
                    t.a[i]=tmp;
                    t.len=i+1;
                }
            }
            // left shift
            for(int i=t.len+j-1;i>=j;--i)
                t.a[i]=t.a[i-j];
            for(int i=j-1;i>=0;--i)
                t.a[i]=0;
            t.len+=j;
            ret=ret+t;
        }
        return ret;
    }
    bool operator < (const LNum &o)
    {
        if(len<o.len) return true;
        if(len>o.len) return false;
        for(int i=len-1;i>=0;--i)
        {
            if(a[i]<o.a[i]) return true;
            if(a[i]>o.a[i]) return false;
        }
        return false;
    }
    bool operator > (const LNum &o)
    {
        if(len>o.len) return true;
        if(len<o.len) return false;
        for(int i=len-1;i>=0;--i)
        {
            if(a[i]>o.a[i]) return true;
            if(a[i]<o.a[i]) return false;
        }
        return false;
    }
    bool operator == (const LNum &o)
    {
        if(len!=o.len) return false;
        for(int i=len-1;i>=0;--i)
            if(a[i]!=o.a[i]) return false;
        return true;
    }

    void atoLNum(const string &in)
    {
        len=in.size();
        for(int i=len-1;i>=0;--i)
            a[i]=in[len-i-1]-'0';
    }
    void input()
    {
        string in;
        cin>>in;
        atoLNum(in);
    }
    void print()
    {
        bool prefix_0=true;
        for(int i=len-1;i>=0;--i)
        {
            if(a[i]) prefix_0=false;
            if(!prefix_0) printf("%d",a[i]);
        }
        cout<<endl;
    }
};
int main()
{
    LNum a={{0},0},b={{0},0},c={{0},0};
    a.input();
    b.input();
    c=a*b;
    c.print();

    LNum d,e,f;
    d.atoLNum("12345");
    e.atoLNum("54321");
    f.atoLNum("0");
    f=d*e;
    f.print();
    
    cout<<(c==f)<<endl;
    cout<<(a>b)<<endl;
    getchar();getchar();
    return 0;
}