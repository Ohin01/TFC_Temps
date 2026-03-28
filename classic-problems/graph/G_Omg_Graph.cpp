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

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void pre(){
    fact[0]=1;
    inv[0]=1;
    FOR(i, 1, MX){
        fact[i] = (i * fact[i - 1])% MOD;
        inv[i] = Bigmod(fact[i], MOD - 2LL, MOD);
    }
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

void dfs(ll node, vvll &graph, vb &vis)
{
    vis[node] = true;

    for (auto child: graph[node])
    {
        if (vis[child])
        continue;

        dfs(child, graph, vis);
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<pll>> graph(n + 1);

    vector<pair<ll, pll>> edges;

    FOR(i, 0, m)
    {
        ll n1, n2, w;
        cin >> n1 >> n2 >> w;

        edges.pb({w, {n1, n2}});
        graph[n1].pb({n2, w});
        graph[n2].pb({n1, w});
    }

    vb vis1(n + 1, false), vis2(n + 1, false);
    
    // dfs(1, graph, vis1);
    // dfs(n, graph, vis2);

    vb vis(n + 1, false);
    vll mxdist(n + 1, INF);
    mxdist[1] = 0;

    priority_queue<pll, vpll, greater<pll>> q;
    q.push({0, 1});

    while (!q.empty())
    {
        pll front = q.top();
        q.pop();
        ll node = front.ss;

        if (vis[node])
        continue;

        vis[node] = true;

        for (auto child: graph[node])
        {
            ll ch = child.ff;
            ll wt = child.ss;

            if (vis[ch])
            continue;

            if (max(wt, mxdist[node]) < mxdist[ch])
            {
                mxdist[ch] = max(wt, mxdist[node]);
                q.push({wt, ch});
            }
        }
    }

    sort(edges.begin(), edges.end());

    ll ans = INF;

    ll sel = 0;

    FOR(i, 0, m)
    {
        ll wt = edges[i].ff;
        ll n1 = edges[i].ss.ff;
        ll n2 = edges[i].ss.ss;

        ans = min(ans, wt + max(mxdist[n1], mxdist[n]));
    }

    cout << ans << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}