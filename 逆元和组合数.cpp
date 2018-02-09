#include <iostream>
using namespace std;

const int MAX_A = 1000;         // C(A, B)
const int MOD = (int)(1e9) + 7;
long long factorial[MAX_A];
long long inverse[MAX_A];

long long multi_mod(long long a, long long b, long long c)  //返回(a*b) mod c
{
    a %= c;
    b %= c;
    long long ret = 0;
    while (b)
    {
        if (b & 1)
            ret = (ret + a) % c;
        a <<= 1;
        a %= c;
        b >>= 1;
    }
    return ret;
}

long long pow_mod(long long x, long long n, long long mod)  //返回(x^n) mod c
{
    x %= mod;
    if (n == 1) return x;
    long long ret = 1;
    while (n)
    {
        if (n & 1)
            ret = multi_mod(ret, x, mod);
        n >>= 1;
        x = multi_mod(x, x, mod);
    }
    return ret;
}

long long get_inverse(long long a)  // 求 a 在 MOD 下的乘法逆元
{
    return pow_mod(a, MOD - 2, MOD);
}

void init_comb(int n)
{
    factorial[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        factorial[i] = factorial[i - 1] * i;
        factorial[i] %= MOD;
    }
    inverse[n] = get_inverse(factorial[n]);
    for (int i = n - 1; i >= 0; i--)
    {
        inverse[i] = inverse[i + 1] * (i + 1);
        inverse[i] %= MOD;
    }
}

long long comb(long long a, long long b)    // 给出组合数 C(b, a)
{
	if (b == 0)
		return 1;
	long long ret = factorial[a] * inverse[a - b];
	ret %= MOD;
	ret *= inverse[b];
	ret %= MOD;
	return ret;
}

int main()
{
    init_comb(MAX_A);
    cout<<comb(4,2)<<endl; // 6
    cout<<comb(6,3)<<endl; // 20
    cout<<comb(100,50)<<endl;
    getchar();getchar();
    return 0;
}