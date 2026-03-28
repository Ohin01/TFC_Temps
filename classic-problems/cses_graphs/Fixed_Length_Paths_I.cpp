#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9 + 7;

int LOGN;
vector<vector<int>> g;
vector<vector<int>> ceng;
vector<vector<int>> par;
vector<int> depth;
vector<int> sz;
vector<int> done;
vector<bool> vis;
vector<int> cenpar;
vector<int> best_dist;
vector<int> gb_vec; // Replaced map with vector

int tot;
int n, k;
ll ans = 0;

void calc_sz(int u, int p) 
{
    tot++;
    sz[u] = 1;
    depth[u] = 0;
    for (auto v : g[u]) 
    {
        if (v == p || done[v]) continue;
        depth[v] = depth[u] + 1;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}

void find_dist(int node, int p)
{
    depth[node] = 0;
    
    for (auto ch: g[node])
    {
        if (node == p || vis[ch]) continue;
        depth[ch] = depth[node] + 1;
        find_dist(ch, node);
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

void fillDist(int node, int p, int d, vector<int> &allDists)
{
    allDists.push_back(d);

    for (auto ch: g[node])
    {
        if (ch == p || done[ch]) continue;

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
    gb_vec[0] = 1;
    added_dists.push_back(0);

    for (auto ch: g[cen])
    {
        if (done[ch] == 1) continue;

        vector<int> allDists;
        fillDist(ch, cen, 1, allDists);
            
        for (int d: allDists)
        {
            if (k >= d && gb_vec[k - d] > 0) ans += gb_vec[k - d];
        }

        for (int d: allDists)
        {
            gb_vec[d]++;
            added_dists.push_back(d);
        }
    }

    // Reset only the modified indices to keep it efficient
    for (int d : added_dists) gb_vec[d] = 0;

    for (auto v : g[cen]) 
    {
        if (!done[v]) decompose(v, cen);
    }
}

void solve() 
{
    cin >> n >> k;

    LOGN = (n > 1) ? (int)log2(n) + 2 : 2;

    g.assign(n + 1, vector<int>());
    ceng.assign(n + 1, vector<int>());
    par.assign(n + 1, vector<int>(LOGN, 0));
    depth.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    done.assign(n + 1, 0);
    cenpar.assign(n + 1, 0);
    best_dist.assign(n + 1, INF);
    vis.assign(n + 1, false);
    gb_vec.assign(n + 1, 0); // Frequency array for distances

    for (int i = 1; i < n; i++) 
    {
        int u, v; 
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    decompose(1, 0);

    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}