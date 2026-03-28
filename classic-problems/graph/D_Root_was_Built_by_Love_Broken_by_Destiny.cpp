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

vll curcomp;
bool cycle = false;

void dfs(ll node, ll par, vvll &graph, vb &vis)
{
    vis[node] = true;

    curcomp.pb(node);

    for (auto child: graph[node])
    {
        if (child == par)
        continue;

        if (vis[child])
        {
            cycle = true;
            return;
        }

        dfs(child, node, graph, vis);
    }
}

void dfs2(ll node, ll par, vvll &graph, ll &root, ll &ans)
{
    ll leaf = 0;
    ll nonleaf = 0;

    for (auto child: graph[node])
    {
        if (child == par)
        continue;

        if (graph[child].size() == 1)
        leaf++;

        else
        nonleaf++;

        dfs2(child, node, graph, root, ans);
    }

    //cout << node << " " << leaf << " " << nonleaf << endl;

    if (node == root)
    {
        if (nonleaf > 2)
        {
            ans = 0;
            return;
        }

        else if (nonleaf == 1 || nonleaf == 2)
        {
            ans *= 2;
        }

        ans *= fact[leaf];
        ans %= MOD;

    }

    else
    {
        if (nonleaf > 1)
        {
            ans = 0;
            return;
        }

        ans *= fact[leaf];
        ans %= MOD;
    }

    //cout << "ans " << ans << endl;
}

void solve()
{
    cycle = false;

    ll n, m;
    cin >> n >> m;

    vvll graph(n + 1);

    FOR(i, 0, m)
    {
        ll n1, n2;
        cin >> n1 >> n2;

        graph[n1].pb(n2);
        graph[n2].pb(n1);
    }

    ll comp = 0;
    vvll comps;

    vb vis(n + 1, false);
    vll color(n + 1, 0);

    FOR(i, 1, n + 1)
    {
        if (vis[i])
        continue;

        dfs(i, -1, graph, vis);

        comps.pb(curcomp);
        curcomp.clear();

        if (cycle == true)
        {
            cout << 0 << endl;
            return;
        }
    }

    // FOR(i, 0, comps.size())
    // {
    //     FOR(j, 0, comps[i].size())
    //     {
    //         cout << comps[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    vll eachcomp(comps.size());

    ll ans = 1;

    FOR(i, 0, comps.size())
    {
        if (comps[i].size() == 2)
        {
            ans *= 2;
            ans %= MOD;
        }

        else
        {
            FOR(j, 0, comps[i].size())
            {
                if (graph[comps[i][j]].size() > 1)
                {
                    dfs2(comps[i][j], -1, graph, comps[i][j], ans);
                    ans *= 2;
                    ans %= MOD;

                    //cout << "rppt " << comps[i][j] << " " << ans << endl; 
                    break;
                }
            }
        }
    }

    ans *= fact[comps.size()];
    ans %= MOD;

    cout << ans << endl;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    pre();

    while (cases--)
    {
        solve();
    }
}