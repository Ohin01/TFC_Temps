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

vector<vector<pll>> graph(MAX);
vll intime(MAX, -1);
vll low(MAX, -1);
vb vis(MAX, false);
int timer = 0;
vll ans(MAX, -1);

void articulation_bridge(ll node, ll par)
{
    timer++;
    vis[node] = true;
    intime[node] = timer;
    low[node] = timer;

    for (auto ch: graph[node])
    {
        ll child = ch.ff;
        ll id = ch.ss;
        if (child == par) continue;

        if (vis[child])
        {
            low[node] = min(low[node], intime[child]);
        }

        else
        {
            articulation_bridge(child, node);
            low[node] = min(low[node], low[child]);

            if (low[child] > intime[node])
            {
                ans[child] = id;
                ans[node] = id;
            }
        }
    }
}

void dfs(ll node, vb &seen, vll &comp, vector<vector<pll>> &cutgraph)
{
    seen[node] = true;
    comp.pb(node);

    for (auto ch: cutgraph[node])
    {
        ll child = ch.ff;

        if (seen[child]) continue;

        dfs(child, seen, comp, cutgraph);
    }
}

void bfs(vll &comp, ll n, vector<vector<pll>> &cutgraph)
{
    queue<ll> q;

    vb done(n + 1);

    FOR(i, 0, comp.size())
    {
        if (ans[comp[i]] != -1)
        {
            q.push(comp[i]);
            done[i]= true;
        }
    }

    while (!q.empty())
    {
        ll cur = q.front();
        q.pop();
        done[cur] = true;

        for (auto ch: cutgraph[cur])
        {
            ll child = ch.ff;

            if (done[child]) continue;

            ans[child] = ans[cur];
            q.push(child);
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;

    FOR(i, 1, n + 1)
    {
        graph[i].clear();
        ans[i] = -1;
        vis[i] = false;
        intime[i] = -1;
        low[i] = -1;
        timer = 0;
    }

    FOR(i, 1, m + 1)
    {
        ll n1, n2;
        cin >> n1 >> n2;

        graph[n1].pb({n2, i});
        graph[n2].pb({n1, i});
    }

    articulation_bridge(1, -1);

    unordered_set<ll, custom_hash> bridges;

    FOR(i, 1, n + 1)
    {
        if (ans[i] != -1)
        bridges.insert(ans[i]);
    }

    vector<vector<pll>> cutgraph(n + 1);

    FOR(i, 1, n + 1)
    {
        FOR(j, 0, graph[i].size())
        {
            if (bridges.find(graph[i][j].ss) == bridges.end())
            {
                cutgraph[i].pb(graph[i][j]);
            }
        }
    }

    vb seen(n + 1);
    vvll allcomp;

    FOR(i, 1, n + 1)
    {
        if (seen[i]) continue;

        vll comp;

        dfs(i, seen, comp, cutgraph);

        allcomp.pb(comp);
    }

    FOR(i, 0, allcomp.size())
    {
        FOR(j, 0, allcomp[i].size())
        {
            cout << allcomp[i][j] << " ";
        }
        cout << endl;
    }

    FOR(i, 0, allcomp.size())
    {
        vll &comp = allcomp[i];

        bfs(comp, n, cutgraph);
    }

    FOR(i, 1, n + 1)
    cout << ans[i] << " ";
    cout << endl;

    ll q;
    cin >> q;

    while (q--)
    {
        ll nn;
        cin >> nn;

        cout << ans[nn] << " ";
    }
    cout <<endl;
    
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}