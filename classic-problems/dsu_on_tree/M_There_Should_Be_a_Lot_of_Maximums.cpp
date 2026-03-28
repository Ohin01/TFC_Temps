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

ll val[MAXN];
ll par[MAXN];
ll q[MAXN];
ll prnt[MAXN];

map<ll, ll> all;
vll arr;
ll ind;

map<ll, ll> cur;
ll mad[MAXN];


void dfs(int u, int p) 
{
    all[val[u]]++;
    par[u] = p;

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

void dsu(int u, int p, bool keep) 
{
    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            dsu(v, u, 0); 
        }
    }

    if (heavy[u] != -1) 
    {
        dsu(heavy[u], u, 1);
    }

    if (heavy[u] != -1)
    {
        mad[u] = mad[heavy[u]];
    }

    else
    {
        ind = arr.size() - 1;
    }

    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            for (int t = tin[v]; t <= tout[v]; t++) 
            {
                int w = node[t]; //subtree of child in subtree of parent

                cur[val[w]]++;

                if (cur[val[w]] >= 2)
                mad[u] = max(mad[u], val[w]);
                
                all[val[w]]--;
            }
        }
    }

    //Add node u itself
    cur[val[u]]++;

    if (cur[val[u]] >= 2)
    mad[u] = max(mad[u], val[u]);
    
    all[val[u]]--;

    while (all[arr[ind]] < 2)
    ind--;
    

    //Answer Queries for u here
    prnt[q[u]] = max(mad[u], arr[ind]);
    // ...

    //Clear if needed
    if (keep == 0) 
    {
        for (int t = tin[u]; t <= tout[u]; t++) 
        {
            int w = node[t];

            cur[val[w]]--;
            
            all[val[w]]++;
        }
    }
}

void solve()
{
    ll n;
    cin >> n;

    vpll edges;

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        adj[u].pb(v);
        adj[v].pb(u);

        edges.pb({u, v});
    }

    FOR(i, 1, n + 1)
    cin >> val[i];

    dfs(1, 0);

    arr.pb(0);

    for (auto &p: all)
    {
        if (p.ss >= 2)
        arr.pb(p.ff);
    }

    all[0] = INF;

    ind = arr.size() - 1;

    FOR(i, 0, edges.size())
    {
        ll f = edges[i].ff;
        ll s = edges[i].ss;

        if (f == par[s])
        q[s] = i + 1;

        else
        q[f] = i + 1;
    }


    dsu(1, 0, 0);

    FOR(i, 1, n)
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