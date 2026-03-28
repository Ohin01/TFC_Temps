#include<bits/stdc++.h>
using namespace std;

typedef long long       ll;
typedef long double     ld;
typedef vector<int>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;

#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const int MAX = 2e5 + 5;
const int LOGN = 20;
const ll INF = 1e18 + 10;

struct ISegTree
{
    ll sz = 0;
    vll res;

    void init(int n)
    {
        sz = 1;
        while (sz < n) sz *= 2;
        res.assign(sz * 2, -INF);
    }

    ll operation(ll a, ll b)
    {
        return max(a, b);
    }

    // Iterative build: Fill leaves then compute parents
    void build(vll &a, int x = 0, int lx = 0, int rx = 0)
    {
        for (int i = 0; i < (int)a.size(); i++) {
            res[sz + i] = a[i];
        }
        for (int i = sz - 1; i >= 1; i--) {
            res[i] = operation(res[2 * i], res[2 * i + 1]);
        }
    }

    // Iterative assign: Update leaf and walk up to the root
    void assign(int i, ll v, int x = 0, int lx = 0, int rx = 0)
    {
        int cur = i + sz;
        res[cur] = v;
        while (cur > 1) {
            cur /= 2;
            res[cur] = operation(res[2 * cur], res[2 * cur + 1]);
        }
    }

    // Iterative getRes: Query range [l, r]
    ll getRes(int l, int r, int x = 0, int lx = 0, int rx = 0)
    {
        ll ans = -INF;
        l += sz;
        r += sz;
        
        while (l <= r) {
            if (l % 2 == 1) ans = operation(ans, res[l++]);
            if (r % 2 == 0) ans = operation(ans, res[r--]);
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};

ISegTree t;

vector<int> g[MAX];
int par[MAX][LOGN + 1], depth[MAX], sz[MAX];
int T = 0, head[MAX], st[MAX], en[MAX];

void dfs(int node, int p = 0) 
{
    par[node][0] = p;
    sz[node] = 1;

    if (p != 0) g[node].erase(find(g[node].begin(), g[node].end(), p));

    for (auto &ch: g[node])
    {
        if (ch == p) continue;
        
        depth[ch] = depth[node] + 1;
        dfs(ch, node);
        sz[node] += sz[ch];

        if(sz[ch] > sz[g[node][0]]) swap(ch, g[node][0]);
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
        if (ch == g[node][0]) head[ch] = head[node];
        else head[ch] = ch;
       
        dfs_hld(ch);
    }

    en[node] = T;
}

ll query_up(int u, int v) 
{
    ll ans = -INF;

    while(head[u] != head[v]) 
    {
        ans = max(ans, t.getRes(st[head[u]], st[u], 0, 0, t.sz - 1));
        u = par[head[u]][0];
    }

    ans = max(ans, t.getRes(st[v], st[u], 0, 0, t.sz - 1));
    return ans;
}

int query(int u, int v) 
{
    ll lca = LCA(u, v);
    ll ans = query_up(u, lca);

    if (v != lca) ans = max(ans, query_up(v, kthAncestor(v, depth[v] - depth[lca] - 1)));
    return ans;
}


void solve()
{
    int n;
    cin >> n;

    int q;
    cin >> q;

    vll a(n + 1);
    FOR(i, 1, n + 1) cin >> a[i];
    a[0] = -INF;

    for (int i = 1; i < n; i++) 
    {
        int u, v;
        cin >> u >> v;
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

    while (q--)
    {
        int ty;
        cin >> ty;

        if (ty == 1)
        {
            int s, x;
            cin >> s >> x;

            a[s] = x;
            t.assign(st[s], x, 0, 0, t.sz - 1);
        }

        else
        {
            int u, v;
            cin >> u >> v;

            cout << query(u, v) << " ";
        }
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