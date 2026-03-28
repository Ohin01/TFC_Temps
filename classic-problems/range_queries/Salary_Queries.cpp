#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename dataType>
using ordered_set = tree<dataType, null_type, less<dataType>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType1, typename dataType2>
using ordered_map = tree<dataType1, dataType2, less<dataType1>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType>
using ordered_multiset = tree<dataType, null_type, less_equal<dataType>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

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
const ld PI = acos((ld) -1);
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void pre(){
    fact[0]=1;
    inv[0]=1;
    FOR(i, 1, MX){
        fact[i] = (i * fact[i - 1])% MOD;
        inv[i] = Bigmod(fact[i], MOD - 2LL, MOD);
    }
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

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
            res[x] += v;
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

struct Compression //0-based
{
    vector<ll> vals;

    void build(const vector<ll>& a) 
    {
        vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    int get(ll x) 
    {
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
    }

    ll rev(int i) 
    {
        return vals[i - 1];
    }

    // compress entire array
    vector<int> compress_array(const vector<ll>& a) 
    {
        vector<int> res(a.size());

        for (int i = 0; i < a.size(); i++) 
        {
            res[i] = get(a[i]);
        }
        return res;
    }

    pair<int,int> get_range(ll l, ll r) 
    {
        int L = lower_bound(vals.begin(), vals.end(), l) - vals.begin() + 1; // + 1;
        int R = upper_bound(vals.begin(), vals.end(), r) - vals.begin(); // remove -1;

        if (L > R) return {-1, -1}; // no valid range
        return {L, R};
    }
};


void solve()
{
    ll n, m;
    cin >> n >> m;

    vll h(n + 1);

    vll cmp;

    FOR(i, 1, n + 1)
    {
        cin >> h[i];
        cmp.pb(h[i]);
    }

    vector<pair<ll, pll>> q;

    FOR(i, 0, m)
    {
        char c;
        cin >> c;

        if (c == '?') 
        {
            ll a, b;
            cin >> a >> b;

            q.pb({2, {a, b}});

            // cmp.pb(a);
            // cmp.pb(b);
        }

        else
        {
            ll k, v;
            cin >> k >> v;

            q.pb({1, {k, v}});

            cmp.pb(v);
        }
    }

    Compression cc;

    cc.build(cmp);

    SegTree ft;

    ft.init(cc.vals.size() + 1, 0);

    FOR(i, 1, n + 1)
    {
        ft.update(cc.get(h[i]), 1, 0, 0, ft.sz - 1);
    }

    FOR(i, 0, m)
    {
        int tt = q[i].ff;

        if (tt == 1)
        {
            ll k = q[i].ss.ff;
            ll v = q[i].ss.ss;

            ft.update(cc.get(h[k]), -1, 0, 0, ft.sz - 1);
            ft.update(cc.get(v), 1, 0, 0, ft.sz - 1);

            h[k] = v;
        }

        else
        {
            ll l = q[i].ss.ff;
            ll r = q[i].ss.ss;

            pi p = cc.get_range(l, r);

            ll L = p.ff;
            ll R = p.ss;

            cout << ft.query(L, R, 0, 0, ft.sz - 1) << endl;
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}