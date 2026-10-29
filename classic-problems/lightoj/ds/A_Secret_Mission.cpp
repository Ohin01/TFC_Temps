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

typedef int       ll;
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
const int MAX = 5e4 + 5;
const int MX = 1e6 + 5;
const int LOGN = 17;
const ld PI = acos((ld) -1);

struct DSU 
{
    vector<ll> par, rnk, sz;
    ll c;

    DSU(ll n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), c(n) 
    {
        for (ll i = 1; i <= n; i++) par[i] = i;
    }

    ll find(ll i) 
    {
        return (par[i] == i ? i : (par[i] = find(par[i])));
    }

    bool same(ll i, ll j) 
    {
        return find(i) == find(j);
    }

    ll get_size(ll i) 
    {
        return sz[find(i)];
    }

    ll count() 
    {
        return c;    //connected components
    }

    void merge(ll i, ll j) 
    {
        if ((i = find(i)) == (j = find(j))) return;

        if (rnk[i] > rnk[j]) swap(i, j);

        par[i] = j;
        sz[j] += sz[i];
        c--;

        if (rnk[i] == rnk[j]) rnk[j]++;
    }
};

vector<ll> depth(MAX);
vector<vpll> graph(MAX);
int par[MAX][LOGN + 1], mx[MAX][LOGN + 1];

void dfs(int node, int parent)
{
    par[node][0] = parent;
    //mx[1][0] = INT_MAX;

    for (auto ch: graph[node])
    {
        int child = ch.ff;
        int wt = ch.ss;

        if (child == parent) continue;

        depth[child] = depth[node] + 1;
        mx[child][0] = wt;

        dfs(child, node);
    }
}

void fillAncestor(int n)
{
    FOR(i, 1, LOGN)
    {
        FOR(j, 1, n + 1)
        {
            mx[j][i] = 0;

            if (par[j][i - 1] != 0)
            {
                mx[j][i] = max(mx[j][i - 1], mx[ par[j][i - 1] ][i - 1]);
                par[j][i] = par[ par[j][i - 1] ][i - 1];
            }

            else
            par[j][i] = 0;
        }
    }
}

int kthAncestor(int node, int k)
{
    int ans = node;

    FOR(i, 0, LOGN)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i];
            if (ans == 0) return 0;
        }
    }

    return ans;
}

int kthValue(int node, int k)
{
    int res = 0;
    int ans = node;

    FOR(i, 0, LOGN)
    {
        if ((k & (1<<i)) != 0)
        {
            res = max(res, mx[ans][i]);
            ans = par[ans][i];
            if (ans == 0) return 0;
        }
    }

    return res;
}

int LCA(int n1, int n2)
{
    int ans = 0;

    if (depth[n1] > depth[n2]) swap(n1, n2);

    int diff = depth[n2] - depth[n1];
    ans = max(ans, kthValue(n2, diff));
    n2 = kthAncestor(n2, diff);

    if (n1 == n2) return ans;

    FORR(i, LOGN - 1, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            ans = max(ans, mx[n1][i]);
            ans = max(ans, mx[n2][i]);

            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    ans = max(ans, mx[n1][0]);
    ans = max(ans, mx[n2][0]);

    return ans;
}

// vector<ll> depth(MAX);
// vector<vpll> graph(MAX);
// int par[MAX][LOGN + 1], mx[MAX][LOGN + 1];

void solve()
{
    ll n, m;
    cin >> n >> m;

    FOR(i, 0, LOGN)
    {
        FOR(j, 0, n + 1)
        {
            mx[j][i] = 0;
            par[j][i] = 0;
            //cout << mx[j][i] << " ";
        }
        //cout << endl;
    }

    FOR(i, 0, n + 1)
    {
        graph[i].clear();
        depth[i] = 0;
    }

    DSU dsu(n);

    vector<tuple<int, int, int>> t(m);

    FOR(i, 0, m)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        t[i] = {w, u, v};
    }

    sort(t.begin(), t.end());

    FOR(i, 0, m)
    {
        int w = get<0>(t[i]);
        int u = get<1>(t[i]);
        int v = get<2>(t[i]);

        if (dsu.same(u, v))
        {
            continue;
        }

        else
        {
            dsu.merge(u, v);
            graph[u].pb({v, w});
            graph[v].pb({u, w});
        }
    }

    dfs(1, 0);
    fillAncestor(n);

    // FOR(i, 1, n + 1)
    // {
    //     cout << depth[i] << " " << mx[i][0] << endl;
    // }

    //cout << depth[2] << " " << mx[2][0] << endl;

    // FOR(i, 0, LOGN)
    // {
    //     FOR(j, 0, n + 1)
    //     {
    //         //mx[j][i] = INT_MAX;
    //         cout << mx[j][i] << " ";
    //     }
    //     cout << endl;
    // }

    int q;
    cin >> q;

    while (q--)
    {
        ll s, t;
        cin >> s >> t;

        cout << LCA(s, t) << endl;
    }

}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    //cout << log2(MAX) << endl;

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": " << endl;
        solve();
    }
}