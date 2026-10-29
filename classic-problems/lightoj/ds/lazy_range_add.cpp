#include<bits/stdc++.h>
using namespace std;

typedef long long   ll;
typedef vector<ll> vll;

struct SegTree
{
    ll sz = 0;
    vll res;
    vll lazy;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
        lazy.assign(sz * 2, 0);
    }

    ll op(ll a, ll b)
    {
        return a + b;
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == 0) return;

        res[x] += (rx - lx + 1) * lazy[x];

        if (lx != rx)
        {
            lazy[2 * x + 1] += lazy[x];
            lazy[2 * x + 2] += lazy[x];
        }

        lazy[x] = 0;
    }

    void build(vll &a, int x, int lx, int rx)
    {
        lazy[x] = 0;

        if (lx == rx)
        {
            if (lx < (int)a.size())
            res[x] = a[lx];

            else
            res[x] = dummy;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    void update(int l, int r, ll v, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) return;

        if (lx >= l && rx <= r)
        {
            lazy[x] += v;
            push(x, lx, rx);
            return;
        }

        ll mid = (lx + rx) / 2;
        update(l, r, v, 2 * x + 1, lx, mid);
        update(l, r, v, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
        push(x, lx, rx);

        if (r < lx || rx < l) 
        {
            return dummy;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return op(query(l, r, 2 * x + 1, lx, mid), query(l, r, 2 * x + 2, mid + 1, rx));
    }
};

int main(void)
{
    return 0;
}

