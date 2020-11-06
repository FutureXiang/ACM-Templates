#include <iostream>
#include <climits>
#include <cstdio>
#include <algorithm>

using namespace std;
const int maxn = 200005;

int n;
struct seg {
    long long sum, lazy;
    long long mmin, mmax;
} s[maxn * 4];

void lazy_down(int now, int len) {
    s[now * 2].lazy += s[now].lazy;
    s[now * 2 + 1].lazy += s[now].lazy;

    s[now * 2].sum += (long long) (len - len / 2) * s[now].lazy;
    s[now * 2 + 1].sum += (long long) (len / 2) * s[now].lazy;
    s[now * 2].mmin += s[now].lazy;
    s[now * 2 + 1].mmin += s[now].lazy;
    s[now * 2].mmax += s[now].lazy;
    s[now * 2 + 1].mmax += s[now].lazy;
    s[now].lazy = 0;
}

void build(int now, int l, int r) {
    if (l == r) {
        long long in;
        cin >> in;
        s[now].sum = in;
        s[now].mmin = in;
        s[now].mmax = in;
        return;
    }
    int m = (l + r) / 2;
    build(now * 2, l, m);
    build(now * 2 + 1, m + 1, r);
    s[now].sum = s[now * 2].sum + s[now * 2 + 1].sum;
    s[now].mmin = min(s[now * 2].mmin, s[now * 2 + 1].mmin);
    s[now].mmax = max(s[now * 2].mmax, s[now * 2 + 1].mmax);
}

void add(int now, int l, int r, int ql, int qr, long long A) {
    if (r < ql || l > qr) return;
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        s[now].lazy += A;
        s[now].sum += (long long) (A) * (long long) (r - l + 1);
        s[now].mmin += A;
        s[now].mmax += A;
        return;
    }

    if (s[now].lazy) lazy_down(now, r - l + 1);

    if (ql <= m) add(now * 2, l, m, ql, qr, A);
    if (qr > m) add(now * 2 + 1, m + 1, r, ql, qr, A);
    s[now].sum = s[now * 2].sum + s[now * 2 + 1].sum;
    s[now].mmin = min(s[now * 2].mmin, s[now * 2 + 1].mmin);
    s[now].mmax = max(s[now * 2].mmax, s[now * 2 + 1].mmax);
}

long long query(int now, int l, int r, int ql, int qr, int flag) // flag=0: sum   flag=1: min   flag=2: max
{
    if (r < ql || l > qr) return 0;
    long long ans = 0, mmin = LLONG_MAX, mmax = LLONG_MIN;
    if (ql <= l && r <= qr) return flag == 0 ? s[now].sum : (flag == 1 ? s[now].mmin : s[now].mmax);
    int m = (l + r) / 2;

    if (s[now].lazy) lazy_down(now, r - l + 1);

    if (flag == 0) {
        if (ql <= m) ans += query(now * 2, l, m, ql, qr, flag);
        if (qr > m) ans += query(now * 2 + 1, m + 1, r, ql, qr, flag);
    } else if (flag == 1) {
        if (ql <= m) mmin = min(mmin, query(now * 2, l, m, ql, qr, flag));
        if (qr > m) mmin = min(mmin, query(now * 2 + 1, m + 1, r, ql, qr, flag));
    } else if (flag == 2) {
        if (ql <= m) mmax = max(mmax, query(now * 2, l, m, ql, qr, flag));
        if (qr > m) mmax = max(mmax, query(now * 2 + 1, m + 1, r, ql, qr, flag));
    }
    return flag == 0 ? ans : (flag == 1 ? mmin : mmax);
}

void init() {
    for (int i = 1; i <= n * 3; i++) {
        s[i].sum = s[i].lazy = 0;
        s[i].mmin = LLONG_MAX; // +inf
        s[i].mmax = LLONG_MIN; // -inf
    }
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    init();
    build(1, 1, n);
    for (int i = 0; i < m; ++i) {
        char a;
        cin >> a;
        int b, c;
        long long d;
        scanf("%d%d", &b, &c);
        if (a == '+') {
            cin >> d;
            add(1, 1, n, b, c, d);
        } else {
            cout << query(1, 1, n, b, c, (a == '=' ? 0 : (a == '<' ? 1 : 2))) << endl;
        }
    }
    return 0;
}
