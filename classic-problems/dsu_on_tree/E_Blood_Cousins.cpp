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
vll depth(MAXN, 1);

vll ans(MAXN);
unordered_map<ll, vpll> q;
ll prnt[MAXN];

vvll par(MAX, vll(20, 0));

void fillAncestor(int n)
{
    FOR(i, 1, 20)
    {
        FOR(j, 1, n + 1)
        {
            if (par[j][i - 1] != 0)
            par[j][i] = par[ par[j][i - 1] ][i - 1];

            else
            par[j][i] = 0;
        }
    }
}

int kthAncestor(int node, int k)
{
    int ans = node;

    FOR(i, 0, 20)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i];

            if (ans == 0) return 0;
        }
    }

    return ans;
}

void dfs(int u, int p) 
{
    sz[u] = 1;
    heavy[u] = -1;
    node[tt] = u;
    tin[u] = tt++; 

    par[u][0] = p;
    
    int max_sz = 0;

    for (int v : adj[u]) 
    {
        if (v != p) 
        {
            depth[v] = depth[u] + 1;
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

    for (int v : adj[u]) 
    {
        if (v != p && v != heavy[u]) 
        {
            for (int t = tin[v]; t <= tout[v]; t++) 
            {
                int w = node[t]; //subtree of child in subtree of parent

                ans[depth[w]]++;
            }
        }
    }

    //Add node u itself
    ans[depth[u]]++;
    

    //Answer Queries for u here
    vpll &all = q[u];

    FOR(i, 0, all.size())
    {
        ll d = all[i].ff;
        ll ind = all[i].ss;

        prnt[ind] = max(0ll, ans[d] - 1);

        //cout << u << " " << d  << endl;
    }
    // ...

    //Clear if needed
    if (keep == 0) 
    {
        for (int t = tin[u]; t <= tout[u]; t++) 
        {
            int w = node[t];

            //ans[depth[w]] ^= (1 << ch[w]);
            ans[depth[w]]--;
        }
    }
}

void solve()
{
    ll n;
    cin >> n;

    ll p[n + 1];

    FOR(i, 1, n + 1)
    {
        ll pp;
        cin >> pp;

        p[i] = pp;

        if (pp == 0)
        continue;

        adj[pp].pb(i);
        adj[i].pb(pp);
    }

    FOR(i, 1, n + 1)
    {
        if (p[i] == 0)
        dfs(i, 0);

        //cout << depth[i] << " ";
    }

    fillAncestor(n);

    //cout << par[3][0] << endl;

    //cout << kthAncestor(3, 1) << endl;

    ll m;
    cin >> m;

    FOR(i, 1, m + 1)
    {
        ll v, h;
        cin >> v >> h;

        ll anc = kthAncestor(v, h);

        //cout << anc << endl;

        if (anc == 0)
        continue;

        q[anc].pb({depth[v], i});
    }

    FOR(i, 1, n + 1)
    {
        if (p[i] == 0)
        dsu(i, 0, 0);
    }

    FOR(i, 1, m + 1)
    {
        cout << prnt[i] << " ";
    }
    cout << endl;
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