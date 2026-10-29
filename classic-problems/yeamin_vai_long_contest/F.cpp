#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9 + 7;

vector<vector<int>> g;
vector<int> sz;
vector<int> done;
vector<bool> vis;
vector<int> cenpar;
vector<int> gb_vec;
ll n, q;
vector<int> query, ans;
vector<bool> leaf;
int tot = 0;

void dfs(int u, int p)
{
    int cnt = 0;
    for (auto ch : g[u])
    {
        if (ch == p)
            continue;
        cnt++;
        dfs(ch, u);
    }

    if (cnt == 0)
        leaf[u] = true;
    else if (cnt == 1 && u == 1)
        leaf[1] = true;
}

void calc_sz(int u, int p)
{
    tot++;
    sz[u] = 1;
    for (auto v : g[u])
    {
        if (v == p || done[v])
            continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

int find_cen(int u, int p)
{
    for (auto v : g[u])
    {
        if (v == p || done[v])
            continue;
        if (sz[v] > tot / 2)
            return find_cen(v, u);
    }
    return u;
}

void fillDist(int node, int p, int d, vector<int> &allDists)
{
    if (leaf[node])
    {
        // cout << "Node: " << node << endl;
        allDists.push_back(d);
    }

    for (auto ch : g[node])
    {
        if (ch == p || done[ch])
            continue;

        fillDist(ch, node, d + 1, allDists);
    }
}

void decompose(int u, int pre)
{
    tot = 0;
    calc_sz(u, 0);
    int cen = find_cen(u, 0);

    cenpar[cen] = pre;
    done[cen] = 1;

    vector<int> added_dists;

    if (leaf[cen])
    {
        gb_vec[0] = 1;
        added_dists.push_back(0);
    }

    for (auto ch : g[cen])
    {
        if (done[ch] == 1)
            continue;

        vector<int> allDists;
        // cout << "Centroid: " << cen << endl;

        fillDist(ch, cen, 1, allDists);

        // cout << "Dist: ";

        for (int d : allDists)
        {
            for (int j = 1; j <= q; j++)
            {
                int k = query[j];

                if (k >= d && gb_vec[k - d] > 0)
                    ans[j] += gb_vec[k - d];
            }
            // cout << d << " ";
        }
        // cout << endl;

        for (int d : allDists)
        {
            gb_vec[d]++;
            added_dists.push_back(d);
        }
    }

    for (int d : added_dists)
        gb_vec[d] = 0;

    for (auto v : g[cen])
    {
        if (!done[v])
            decompose(v, cen);
    }
}

void solve()
{
    cin >> n >> q;

    g.assign(n + 1, vector<int>());
    sz.assign(n + 1, 0);
    done.assign(n + 1, 0);
    cenpar.assign(n + 1, 0);
    vis.assign(n + 1, false);
    leaf.assign(n + 1, false);
    gb_vec.assign(n + 1, 0);
    query.assign(q + 1, 0);
    ans.assign(q + 1, 0);

    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= q; i++)
        cin >> query[i];

    dfs(1, 0);
    decompose(1, 0);

    // for (int i = 1; i <= n; i++) if (leaf[i]) cout << i << " "; cout << endl;

    for (int i = 1; i <= q; i++)
        cout << ans[i] << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}