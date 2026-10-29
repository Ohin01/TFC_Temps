#include<bits/stdc++.h>
using namespace std;

typedef long long   ll;
typedef vector<ll> vll;

struct SegTree
{
    ll sz = 0;
    vll res;
    ll dummy;

    void init(int n, ll d)
    {
        dummy = d;
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, d);
    }

    ll op(ll a, ll b)
    {
        return a + b;
    }

    void build(vll &a, int x, int lx, int rx)
    {
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

    void update(int i, ll v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] = v;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) update(i, v, 2 * x + 1, lx, mid);
        else update(i, v, 2 * x + 2, mid + 1, rx);

        res[x] = op(res[2 * x + 1], res[2 * x + 2]);
    }

    ll query(int l, int r, int x, int lx, int rx)
    {
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

    //first value greater than v, or lower_bound of prefix sum v, or kth number
    ll walk (ll v, int x, int lx, int rx)
    {
        if (res[x] < v) return -1;

        if (lx == rx)
        {
            return lx;
        }

        ll mid = (lx + rx) / 2;

        if (res[2 * x + 1] < v) return walk(v - res[2 * x + 1], 2 * x + 2, mid + 1, rx);
        else return walk(v, 2 * x + 1, lx, mid);
    }
};

int main(void)
{
    
}