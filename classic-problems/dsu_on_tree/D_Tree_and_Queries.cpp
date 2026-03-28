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

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int sz[MAXN], heavy[MAXN];
int tin[MAXN], tout[MAXN], node[MAXN];
int tt = 0;

ll cnt[MAXN];
ll c[MAXN];
unordered_map<ll, vpll> q;
ll prnt[MAXN];
ll n;

struct SegTree
{
    ll sz = 0;
    vll res;

    SegTree(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
    }

    ll operation(ll a, ll b)
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
            res[x] = 0;
            return; 
        }

        ll mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    void assign(int i, int v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] += v;;
            return;
        }

        ll mid = (lx + rx) / 2;

        if (i <= mid) assign(i, v, 2 * x + 1, lx, mid);
        else assign(i, v, 2 * x + 2, mid + 1, rx);

        res[x] = operation(res[2 * x + 1], res[2 * x + 2]);
    }

    ll getRes(int l, int r, int x, int lx, int rx)
    {
        if (r < lx || rx < l) 
        {
            return 0;
        }

        if (lx >= l && rx <= r)
        {
            return res[x];
        }

        ll mid = (lx + rx) / 2;

        return operation(getRes(l, r, 2 * x + 1, lx, mid), getRes(l, r, 2 * x + 2, mid + 1, rx));
    }
};

void dfs(int u, int p) 
{
    sz[u] = 1;
    heavy[u] = -1;
    node[tt] = u;
    tin[u] = tt++; 
    
    int max_sz = 0;

    for (int v : adj[u]) 
    {
        if (v != p) 
        {
            dfs(v, u);
            sz[u] += sz[v];

            if (sz[v] > max_sz) 
            {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
    }
    
    tout[u] = tt - 1;
}

void dsu(int u, int p, bool keep, SegTree &st) 
{
    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            dsu(v, u, 0, st); 
        }
    }

    if (heavy[u] != -1) 
    {
        dsu(heavy[u], u, 1, st);
    }

    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            for (int t = tin[v]; t <= tout[v]; t++) 
            {
                int w = node[t]; //subtree of child in subtree of parent

                ll prev = cnt[c[w]];
                ll neww = ++cnt[c[w]];

                if (prev != 0)
                st.assign(prev, -1, 0, 0, st.sz - 1);

                st.assign(neww, 1, 0, 0, st.sz - 1);
            }
        }
    }

    //Add node u itself
    ll prev = cnt[c[u]];
    ll neww = ++cnt[c[u]];

    if (prev != 0)
    st.assign(prev, -1, 0, 0, st.sz - 1);

    st.assign(neww, 1, 0, 0, st.sz - 1);

    // cout << u << endl;

    // FOR(i, 0, n + 1)
    // cout << st.getRes(i, i, 0, 0, st.sz - 1) << " ";
    // cout << endl;
    

    //Answer Queries for u here
    vpll &all = q[u];

    FOR(i, 0, all.size())
    {
        ll d = all[i].ff;
        ll ind = all[i].ss;

        prnt[ind] = st.getRes(d, n, 0, 0, st.sz - 1);

        //cout << u << " " << d << " " << s << endl;
    }
    // ...

    //Clear if needed
    if (keep == 0) 
    {
        for (int t = tin[u]; t <= tout[u]; t++) 
        {
            int w = node[t];

            ll prev = cnt[c[w]];
            ll neww = --cnt[c[w]];

            st.assign(prev, -1, 0, 0, st.sz - 1);
            st.assign(neww, 1, 0, 0, st.sz - 1);
        }
    }
}

void solve()
{
    
    cin >> n;

    ll m;
    cin >> m;

    FOR(i, 1, n + 1)
    cin >> c[i];

    

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1, 0);

    FOR(i, 1, m + 1)
    {
        ll v, h;
        cin >> v >> h;

        q[v].pb({h, i});
    }

    SegTree st(n + 1);

    vll a(n + 1, 0);

    st.build(a, 0, 0, st.sz - 1);

    dsu(1, 0, 0, st);

    FOR(i, 1, m + 1)
    cout << prnt[i] << endl;


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