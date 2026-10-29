#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;
typedef vector<vb>      vvb;
typedef pair<int, int>  pi;
typedef vector<pi>      vpi;
typedef pair<ll, ll>    pll;
typedef vector<pll>     vpll;

#define pb              push_back
#define ff              first
#define ss              second
#define index           find_by_order
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

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
        return min(a, b);
    }

    void push(int x, int lx, int rx)
    {
        if (lazy[x] == 0) return;

        res[x] += lazy[x];

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

        if (r < lx || rx < l || l > r) 
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

void solve()
{
    ll n;
    cin >> n;

    vll a(n + 1), h(n + 1);
    FOR(i, 1, n + 1) cin >> a[i] >> h[i];

    vll ind(MAX, -1);
    ll z = 0;

    SegTree dp;
    dp.init(MAX, INF);
    
    vll em(n + 1, 0);
    dp.build(em, 0, 0, dp.sz - 1);

    dp.update(1, 1, h[1], 0, 0, dp.sz - 1);

    stack<tuple<ll, ll, ll>> st;
    st.push({h[1], 1, 1});

    vll val(n + 1, INF);
    val[1] = h[1];

    ind[a[1]] = 1; 

    //FOR(i, 1, n + 1) cout << dp.query(i, i, 0, 0, dp.sz - 1) << " "; cout << endl;

    FOR(i, 2, n + 1)
    {
        //ll lst = dp.query(i - 1, i - 1, 0, 0, dp.sz - 1);

        if (ind[a[i]] != -1)
        {
            ll lst = ind[a[i]];

            if (lst > z) z = lst;        
        }

        ind[a[i]] = i;

        tuple<ll, ll, ll> cur = {h[i], i, i};

        while (!st.empty())
        {
            tuple<ll, ll, ll> t = st.top();
            
            ll v = get<0>(t);
            ll l = get<1>(t);
            ll r = get<2>(t);

            if (v <= h[i])
            {
                st.pop();

                get<1>(cur) = l;
                dp.update(l, r, -v, 0, 0, dp.sz - 1);
            }

            else break;
        }

        st.push(cur);
        dp.update(get<1>(cur), get<2>(cur) - 1, h[i], 0, 0, dp.sz - 1);

        ll ans = INF;

        if (z + 1 < i)
        ans = min(ans, dp.query(z + 1, i - 1, 0, 0, dp.sz - 1));

        val[i] = min(ans, val[i - 1] + h[i]);

        dp.update(i, i, val[i - 1] + h[i], 0, 0, dp.sz - 1);

        // cout << z + 1 <<  " " << i - 1 << endl;
        
        // FOR(i, 1, n + 1) cout << "dp: " << dp.query(i, i, 0, 0, dp.sz - 1) << " "; cout << endl;
        // FOR(i, 1, n + 1) cout << "val: " << val[i] << " "; cout << endl;
    }

    cout << min(val[n], val[n - 1] + h[n]) << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}