#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1e9 + 7;

struct FenTree
{
    vector<ll> sum;
    int sz;

    void init(int n)
    {
        sum.assign(n + 1, 0);
        sz = n;
    }

    void update(int ind, ll x)
    {
        while (ind < sz) //ind < sz
        {
            sum[ind] += x;
            ind |= (ind + 1);
        }
    }

    ll query(int ind)
    {
        ll ans = 0;
        while (ind >= 0)
        {
            ans += sum[ind];
            ind = (ind & (ind + 1)) - 1;
        }
        return ans;
    }

    ll query(int l, int r)
    {
        if (l == 0) return query(r);
        return query(r) - query(l - 1);
    }
};

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
//vector<int> gb_vec; // Replaced map with vector
vector<int> pref;

int tot;
int n, k1, k2;
ll ans = 0;

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

FenTree ft;

void fillDist(int node, int p, int d, vector<int> &allDists)
{
    if (d > k2) return;
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
    //gb_vec[0] = 1;
    //pref[0] = 1;
    ft.update(0, 1);
    added_dists.push_back(0);
    ll mx = 0;
    ll mn = INF;

    for (auto ch: g[cen])
    {
        if (done[ch] == 1) continue;

        vector<int> allDists;
        fillDist(ch, cen, 1, allDists);

        int boro = -1;
        
        for (int d: allDists) 
        {
            added_dists.push_back(d);
            boro = max(boro, d);
        }

        mx = max(mx, (ll)boro);

        vector<int> cnt(boro + 1, 0);

        for (int d: allDists) cnt[d]++; 
            
        for (int d = 0; d <= boro; d++)
        {
            if (d <= k1) ans += ft.query(k1 - d, k2 - d) * cnt[d];
            else if (d > k1 && d <= k2) ans += ft.query(0, k2 - d) * cnt[d];
        }

        for (int d = 0; d <= boro; d++)
        {
            ft.update(d, cnt[d]);
        }
    }

    vector<int> cnt(mx + 1, 0);

    for (int d: added_dists) cnt[d]++;
    for (int d = 0; d <= mx; d++) ft.update(d, -1 * cnt[d]);
    //for (int i = 0; i <= mx; i++) pref[i] = 0;

    for (auto v : g[cen]) 
    {
        if (!done[v]) decompose(v, cen);
    }
}

void solve() 
{
    cin >> n >> k1 >> k2;

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
    //gb_vec.assign(n + 1, 0); // Frequency array for distances
    pref.assign(n + 1, 0);

    ft.init(k2 + 1);

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