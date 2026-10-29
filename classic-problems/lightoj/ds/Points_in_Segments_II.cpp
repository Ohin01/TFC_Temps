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
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    template<typename T, typename U>
    size_t operator()(const pair<T, U>& x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = splitmix64((uint64_t)x.first + FIXED_RANDOM);
        uint64_t h2 = splitmix64((uint64_t)x.second + FIXED_RANDOM);

        return h1 ^ (h2 >> 1);
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
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

void pre() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (int i = MX - 2; i >= 0; i--) inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
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
        return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); //+ 1;
    }

    ll rev(int i) 
    {
        return vals[i]; //vals[i - 1];
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
        int L = lower_bound(vals.begin(), vals.end(), l) - vals.begin(); // + 1;
        int R = upper_bound(vals.begin(), vals.end(), r) - vals.begin() - 1; // remove -1;

        if (L > R) return {-1, -1}; // no valid range
        return {L, R};
    }
};

void solve()
{
    ll n, qq;
    cin >> n >> qq;

    vll l(n), r(n), q(qq);

    FOR(i, 0, n) cin >> l[i] >> r[i];
    FOR(i, 0, qq) cin >> q[i];

    vll tmp;

    FOR(i, 0, n)
    {
        tmp.pb(l[i]);
        tmp.pb(r[i]);
    }

    FOR(i, 0, qq) tmp.pb(q[i]);

    Compression cmp;
    cmp.build(tmp);

    ll sz = cmp.vals.size();

    SegTree st;
    st.init(sz, 0);

    FOR(i, 0, n)
    {
        ll left = cmp.get(l[i]);
        ll right = cmp.get(r[i]);

        st.update(left, right, 1, 0, 0, st.sz - 1);
    }

    FOR(i, 0, qq)
    {
        ll p = cmp.get(q[i]);
        cout << st.query(p, p, 0, 0, st.sz - 1) << endl;
    }


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
        cout << endl;
        solve();
    }
}