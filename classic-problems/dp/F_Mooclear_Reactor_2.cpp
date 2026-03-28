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
    vll cnt;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
        cnt.assign(sz * 2, 0);
    }

    ll operation(ll a, ll b)
    {
        return a + b;
    }

    void assign(int i, int t, int v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] += v;
            cnt[x] += t;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) assign(i, t, v, 2 * x + 1, lx, mid);
        else assign(i, t, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
        cnt[x] = operation(cnt[2 * x + 1], cnt[2 * x + 2]);
    }

    ll query(ll k, int x, int lx, int rx)
    {
        if (k <= 0 || cnt[x] == 0) return 0;

        if (lx == rx)
        {
            ll take = min(k, cnt[x]);
            return (res[x] / cnt[x]) * take;
        }

        ll mid = (lx + rx) / 2;
        ll rightCnt = cnt[2 * x + 2];

        if (rightCnt >= k)
        {
            return query(k, 2 * x + 2, mid + 1, rx);
        }
        else
        {
            return res[2 * x + 2] + query(k - rightCnt, 2 * x + 1, lx, mid);
        }
    }
};

map<ll, ll> comp;
vvll level(MAX);
ll n, m;
ll dp[MAX];
vector<vector<pll>> q(MAX);
ll anss[MAX];

ll func(int lev, SegTree &st)
{
    if (lev == -1) return 0;
    if (dp[lev] != -1) return dp[lev];

    for (auto val: level[lev])
    {
        st.assign(comp[val], 1, val, 0, 0, st.sz - 1);
    }

    FOR(i, 0, q[lev].size())
    {
        st.assign(comp[q[lev][i].ff], 1, q[lev][i].ff, 0, 0, st.sz - 1);

        anss[q[lev][i].ss] = st.query(lev + 1, 0, 0, st.sz - 1);

        st.assign(comp[q[lev][i].ff], -1, (-1 * q[lev][i].ff), 0, 0, st.sz - 1);
    }

    return dp[lev] = max(func(lev - 1, st), st.query(lev + 1, 0, 0, st.sz - 1));
}

void solve()
{
    cin >> n >> m;
    vll xm(n), ym(n), xs(m), ys(m);


    FOR(i, 0, n) cin >> xm[i] >> ym[i];

    FOR(i, 0, m) cin >> xs[i] >> ys[i];

    comp.clear();

    FOR(i, 0, n + 1)
    {
        level[i].clear();
        dp[i] = -1;
    }

    FOR(i, 0, m + 1)
    {
        q[i].clear();
        anss[i] = 0;
    }

    vll all;

    FOR(i, 0, n) all.pb(xm[i]);
    FOR(i, 0, m) all.pb(xs[i]);

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    FOR(i, 0, all.size())
    {
        comp[all[i]] = i;
    }

    FOR(i, 0, n)
    {
        level[ym[i]].pb(xm[i]);
    }

    FOR(i, 0, m)
    {
        q[ys[i]].pb({xs[i], i});
    }

    SegTree st(all.size() + 10);

    ll ans = func(n, st);

    FOR(i, 0, m)
    {
        cout << max(anss[i], ans) << " ";
    }

    cout << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}