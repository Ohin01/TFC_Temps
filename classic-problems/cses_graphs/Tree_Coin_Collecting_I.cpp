#include<bits/stdc++.h>
using namespace std;

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

#define pb               push_back
#define FOR(i, a, b)    for(ll i = (a); i < (b); i++)
#define FORR(i, a, b)    for(ll i = (a); i >= (b); i--)

const ll MOD = 1e9 + 7;
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

vi *g;
int (*par)[20]; 
vi *depth_ptr;
vi *red_ptr;
vi *color_ptr;
vi *downDP_ptr;
vi *upDP_ptr;
vi *dist;

#define depth (*depth_ptr)
#define red (*red_ptr)
#define color (*color_ptr)
#define downDP (*downDP_ptr)
#define upDP (*upDP_ptr)

void dfs(ll node, ll parent)
{
    par[node][0] = parent;
    red[node] = color[node];

    if (color[node] == 1) downDP[node] = upDP[node] = 0;

    for (auto child: g[node])
    {
        if (child == parent) continue; 

        depth[child] = depth[node] + 1;
        red[child] = red[node] + color[child];

        dfs(child, node);

        downDP[node] = min(downDP[node], 1 + downDP[child]); 
    }
}

void fillAncestor(int n)
{
    FOR(j, 1, n + 1)
    {
        dist[j][0] = downDP[j];
    }

    FOR(i, 1, 20)
    {
        FOR(j, 1, n + 1)
        {
            if (par[j][i - 1] != 0)
            {
                par[j][i] = par[ par[j][i - 1] ][i - 1];
                dist[j][i] = min(dist[j][i - 1], dist[par[j][i - 1]][i - 1]);
            }

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

int LCA(int n1, int n2)
{
    if (depth[n1] > depth[n2])
    swap(n1, n2);

    int diff = depth[n2] - depth[n1];

    n2 = kthAncestor(n2, diff);

    if (n1 == n2)
    return n1;

    FORR(i, 19, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    return par[n1][0];
}

int path(int n1, int n2)
{
    int res = min(downDP[n1], downDP[n2]);

    if (depth[n1] > depth[n2])
    swap(n1, n2);

    int diff = depth[n2] - depth[n1];

    FOR(i, 0, 20)
    {
        if ((diff & (1<<i)) != 0)
        {
            res = min(res, dist[n2][i]);
            n2 = par[n2][i];
        }
    }

    if (n1 == n2)
    return res;

    FORR(i, 19, 0)
    {
        if (par[n1][i] != par[n2][i])
        {
            //res = min(res, dist[n1])
            n1 = par[n1][i];
            n2 = par[n2][i];
        }
    }

    return res;
}

void dfs2(int node, int parent)
{
    vll childs;

    for (auto ch: g[node])
    {
        if (ch == parent) continue;
        childs.pb(ch);
    }

    ll sz = childs.size();

    if (sz == 0) return;

    vi val(sz);

    vi suf(sz);
    vi pref(sz);

    FOR(i, 0, sz) val[i] = downDP[childs[i]] + 1;

    suf[sz - 1] = val[sz - 1];
    pref[0] = val[0];

    FOR(i, 1, sz) pref[i] = min(val[i], pref[i - 1]);
    FORR(i, sz - 2, 0) suf[i] = min(val[i], suf[i + 1]); 

    FOR(i, 0, sz)
    {
        int mx = upDP[node];

        if (i > 0) mx = min(mx, pref[i - 1]);
        if (i < sz - 1) mx = min(mx, (int)suf[i + 1]);

        upDP[childs[i]] = min(upDP[childs[i]], 1 + mx);

        dfs2(childs[i], node);
    }
}

void solve()
{
    ll n;
    cin >> n;

    g = new vi[n + 1];
    par = new int[n + 1][20](); 
    depth_ptr = new vi(n + 1, 0);
    red_ptr = new vi(n + 1);
    color_ptr = new vi(n + 1);
    downDP_ptr = new vi(n + 1, 1e8);
    upDP_ptr = new vi(n + 1, 1e8);
    dist = new vi(n + 1, 1e8);

    ll q;
    cin >> q;

    FOR(i, 1, n + 1) cin >> color[i];

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0);
    dfs2(1, 0);

    fillAncestor(n);

    //FOR(i, 1, n + 1) cout << downDP[i] << " " << upDP[i] << endl;

    while (q--)
    {
        ll u, v;
        cin >> u >> v;

        ll lca = LCA(u, v);

        ll path = depth[u] + depth[v] - 2 * depth[lca];

        if (red[u] + red[v] - 2 * red[lca] > 0) cout << path << "\n";
        else
        {
            cout << path + 2 * min(upDP[lca], min(downDP[u], downDP[v])) << "\n";
        }
    }

    delete[] g;
    delete[] par;
    delete depth_ptr;
    delete red_ptr;
    delete color_ptr;
    delete downDP_ptr;
    delete upDP_ptr;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    while (cases--)
    {
        solve();
    }
    return 0;
}