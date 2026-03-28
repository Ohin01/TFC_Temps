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

vector<int> g[MAX]; 
int par[MAX][LOGN];
int depth[MAX];

int sz[MAX];
int done[MAX];
int cenpar[MAX]; // Parent of node in Centroid Tree
int tot;

int best_dist[MAX]; 

void dfs_lca(int node, int p) 
{
    par[node][0] = p;
 
    for (auto child : g[node]) 
    {
        if (child == p) continue;
        depth[child] = depth[p] + 1;
        dfs_lca(child, node);
    }
}

void fillAncestor(int n) 
{
    for (int i = 1; i < LOGN; i++) 
    {
        for (int j = 1; j <= n; j++) 
        {
            if (par[j][i - 1] != 0)
                par[j][i] = par[par[j][i - 1]][i - 1];
            else
                par[j][i] = 0;
        }
    }
}

int get_lca(int n1, int n2) 
{
    if (depth[n1] > depth[n2]) swap(n1, n2);

    int diff = depth[n2] - depth[n1];

    for (int i = 0; i < LOGN; i++) {
        if ((diff >> i) & 1) n2 = par[n2][i];
    }

    if (n1 == n2) return n1;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (par[n1][i] != par[n2][i]) {
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }
    return par[n1][0];
}

int get_dist(int u, int v) {
    if (u <= 0 || v <= 0) return INF; 
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

void calc_sz(int u, int p) 
{
    tot++;
    sz[u] = 1;
    for (auto v : g[u]) 
    {
        if (v == p || done[v]) continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

int find_cen(int u, int p) 
{
    for (auto v : g[u]) 
    {
        if (v == p || done[v]) continue;
        if (sz[v] > tot / 2) return find_cen(v, u);
    }
    return u;
}

void decompose(int u, int pre) 
{
    tot = 0;
    calc_sz(u, -1);
    int cen = find_cen(u, -1);
    
    cenpar[cen] = pre; // pre is the parent in the Centroid Tree
    done[cen] = 1;
    
    for (auto v : g[cen]) 
    {
        if (!done[v]) decompose(v, cen);
    }
}

void dfs(int node, int p)
{
    for (auto ch: g[node])
    {
        if (ch == p) continue;

        depth[ch] = depth[node] + 1;
        dfs(ch, node);
    }
}

void solve() {
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v; 
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    decompose(1, -1);

    FOR(i, 1, n + 1) 
    {
        if (cenpar[i] == -1)
        dfs(i, -1);
    }

    FOR(i, 1, n + 1)
    {
        cout << (char)(depth[i] + 'A') << " ";
    } cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}