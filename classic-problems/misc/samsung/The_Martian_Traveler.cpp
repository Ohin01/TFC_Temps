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

vb vis(MAX, false);
vvll graph(MAX);
vvll inv(MAX);

void store_order(ll node, vll &order)
{
    vis[node] = true;

    for (auto child: graph[node])
    {
        if (vis[child]) continue;

        store_order(child, order);
    }

    order.pb(node);
}

void dfs(ll node, vll &comp, vb &used)
{
    used[node] = true;
    comp.pb(node);

    for (auto child: inv[node])
    {
        if (used[child]) continue;

        dfs(child, comp, used);
    }
}

vvll kosaraju(ll node)
{
    vvll ans;

    vb used(MAX, false);

    vll order;

    store_order(node, order);

    reverse(order.begin(), order.end());

    FOR(i, 0, order.size())
    {
        if (used[order[i]])
        continue;

        vll temp;

        dfs(order[i], temp, used);

        ans.pb(temp);
    }

    return ans;
}

void solve()
{
    ll n, m, k;
    cin >> n >> m >> k;

    FOR(i, 1, n)
    {
        graph[i].clear();
        inv[i].clear();
        vis[i]= false;
    }

    while (m--)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].pb(v);
        inv[v].pb(u);
    }

    FOR(i, 1, n + 1)
    {
        if (vis[i])
        continue;

        vvll scc = kosaraju(i);

        FOR(i, 0, scc.size())
        {
            FOR(j, 0, scc[i].size())
            cout << scc[i][j] << " ";

            cout << endl;
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

    while (cases--)
    {
        solve();
    }
}