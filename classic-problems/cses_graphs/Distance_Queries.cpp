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

void dfs(ll node, ll parent, vvi &graph, vvi &par, vi &depth)
{
    par[node][0] = parent;

    for (auto child: graph[node])
    {
        if (child == parent) continue; 

        depth[child] = depth[node] + 1;

        dfs(child, node, graph, par, depth);
    }
}

void fillAncestor(int n, vvi &par)
{
    FOR(i, 1, 20)
    {
        FOR(j, 1, n + 1)
        {
            if (par[j][i - 1] != -1)
            par[j][i] = par[ par[j][i - 1] ][i - 1];

            else
            par[j][i] = -1;
        }
    }
}

int kthAncestor(int node, int k, vvi &par)
{
    int ans = node;

    FOR(i, 0, 20)
    {
        if ((k & (1<<i)) != 0)
        {
            ans = par[ans][i];

            if (ans == -1) return -1;
        }
    }

    return ans;
}

int LCA(int n1, int n2, vvi &par, vi &depth)
{
    if (depth[n1] > depth[n2])
    swap(n1, n2);

    int diff = depth[n2] - depth[n1];

    n2 = kthAncestor(n2, diff, par);

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

void solve()
{
    int n;
    cin >> n;

    int q;
    cin >> q;

    vvi graph(n + 1);
    vvi par(n + 1, vi(20, -1));
    vi depth(n + 1, 0);

    FOR(i, 2, n + 1)
    {
        ll nn, rr;
        cin >> nn >> rr;

        graph[rr].push_back(nn);
        graph[nn].push_back(rr);
    }

    dfs(1, -1, graph, par, depth);

    fillAncestor(n, par);

    while (q--)
    {
        ll u, k;
        cin >> u >> k;

        ll lca = LCA(u, k, par, depth);

        cout << depth[u] + depth[k] - 2 * depth[lca] << endl;
    }


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