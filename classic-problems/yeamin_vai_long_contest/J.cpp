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
#define YES             cout << "Yes\n"
#define NO              cout << "No\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e16;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

vvll graph(MAX);
vll intime(MAX, -1);
vll low(MAX, -1);
int timer = 0;
vb points(MAX, false);
vb vis(MAX);

map<pll, bool> brides;

void articulation_bridge(ll node, ll par)
{
    timer++;
    vis[node] = true;
    intime[node] = timer;
    low[node] = timer;

    for (auto child: graph[node])
    {
        if (child == par) continue;

        if (vis[child]) low[node] = min(low[node], intime[child]);

        else
        {
            articulation_bridge(child, node);
            low[node] = min(low[node], low[child]);

            if (low[child] > intime[node])
            {
                ll mn = min(child, node);
                ll mx = max(child, node);
                //if (child > node) swap(child, node);
                brides[{mn, mx}] = true;
            }
        }
    }
}


void solve()
{
    ll n, m;
    cin >> n >> m;

    vector<vpll> adj(n + 1);
    vpll all;
    FOR(i, 0, m)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        if (u > v) swap(u, v);
        all.pb({u, v});

        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    vector<ll> dist(n + 1, INF);

    priority_queue<pll, vector<pll>, greater<pll>> pq;
    ll src = 1;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) 
    {
        ll currDist = pq.top().first;
        ll u = pq.top().second;
        pq.pop();

        if (currDist > dist[u]) continue;

        for (auto edge : adj[u]) 
        {
            ll v = edge.first;
            ll weight = edge.second;

            if (dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    //FOR(i, 1, n + 1) cout << dist[i] << " "; cout << endl;

    // FOR(i, 1, n + 1)
    // {
    //     ll node = i;
    //     for (auto ed: adj[node])
    //     {
    //         ll ch = ed.ff;
    //         ll wt = ed.ss;

    //         if (dist[node] + wt == dist[ch])
    //         {
    //             graph[node].pb(ch);
    //             graph[ch].pb(node);
    //             cout << ch << " " << node << endl;
    //         }
    //     }
    // }

    vb done(n + 1, false);
    queue<ll> q;
    q.push(n);
    done[n] = true;

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();

        for (auto ed: adj[node])
        {
            ll ch = ed.ff;
            ll wt = ed.ss;

            if (dist[ch] + wt == dist[node])
            {
                if (!done[ch]) q.push(ch);
                graph[node].pb(ch);
                graph[ch].pb(node);
                done[ch] = true;
                //cout << ch << " " << node << endl;
            }
        }
    }

    articulation_bridge(1, 0);

    FOR(i, 0, m)
    {
        auto it = brides.find(all[i]);

        if (it != brides.end()) YES;
        else NO;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}