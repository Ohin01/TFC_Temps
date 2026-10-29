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
const int MAX = 3e4 + 5;
const int MX = 1e6 + 5;
const int LOGN = 18;
const ld PI = acos((ld) -1);

struct SegTree
{
    ll sz = 0;
    vll res;

    void init(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, 0);
    }

    ll operation(ll a, ll b)
    {
        return a + b;
    }

    void assign(int i, int v, int x, int lx, int rx)
    {
        if (lx == rx)
        {
            res[x] = v;;
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

SegTree t;

vector<int> g[MAX];
int par[MAX][LOGN + 1], depth[MAX], sz[MAX];
int T = 0, head[MAX], st[MAX], en[MAX];

void dfs(int node, int p = 0) 
{
    par[node][0] = p;
    sz[node] = 1;

    if (p != 0) g[node].erase(find(g[node].begin(), g[node].end(), p)); //erase the parent

    for (auto &ch: g[node])
    {
        if (ch == p) continue;
        
        depth[ch] = depth[node] + 1;
        dfs(ch, node);
        sz[node] += sz[ch];

        if(sz[ch] > sz[g[node][0]]) swap(ch, g[node][0]); //heavy child is always the first child
    }
}

void fillAncestor(int n)
{
    FOR(i, 1, LOGN)
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

int LCA(int n1, int n2)
{
    if (depth[n1] > depth[n2]) swap(n1, n2);

    int diff = depth[n2] - depth[n1];
    n2 = kthAncestor(n2, diff);

    if (n1 == n2) return n1;

    FORR(i, LOGN - 1, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    return par[n1][0];
}

void dfs_hld(int node) 
{
    st[node] = ++T;

    for (auto ch: g[node]) 
    {
        if (ch == g[node][0]) head[ch] = head[node]; //head means top of the heavy chain
        else head[ch] = ch;
       
        dfs_hld(ch);
    }

    en[node] = T;
}

int query_up(int u, int v) //v is lca
{
    ll ans = 0;

    while(head[u] != head[v]) //untill u and v are in the same heavy path
    {
        ans += t.getRes(st[head[u]], st[u], 0, 0, t.sz - 1);
        u = par[head[u]][0];
    }

    ans += t.getRes(st[v], st[u], 0, 0, t.sz - 1);
    return ans;
}

int query(int u, int v) 
{
    int lca = LCA(u, v);
    int ans = query_up(u, lca);

    if (v != lca) ans += (query_up(v, kthAncestor(v, depth[v] - depth[lca] - 1))); //dont include lca
    return ans;
}

void solve()
{
    int n;
    cin >> n;

    FOR(i, 0, n + 1)
    {
        g[i].clear();
        depth[i] = 0;
        sz[i] = 0;
        st[i] = 0;
        T = 0;
    }

    vll a(n + 1);

    FOR(i, 1, n + 1) cin >> a[i];

    for (int i = 1; i < n; i++) 
    {
        int u, v;
        cin >> u >> v;

        u++, v++;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    fillAncestor(n);
    head[1] = 1;
    dfs_hld(1);

    t.init(n + 1);

    FOR(i, 1, n + 1)
    {
        t.assign(st[i], a[i], 0, 0, t.sz - 1);
    }

    ll q;
    cin >> q;

    while (q--)
    {
        ll ty;
        cin >> ty;

        if (ty == 0)
        {
            ll l, r;
            cin >> l >> r;

            l++, r++;
            cout << query(l, r) << endl;
        }

        else
        {
            ll node, val;;
            cin >> node >> val;
            node++;
            a[node] = val;
            t.assign(st[node], val, 0, 0, t.sz - 1);
        }
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
        cout << "Case " << i << ": " << endl;
        solve();
    }
}