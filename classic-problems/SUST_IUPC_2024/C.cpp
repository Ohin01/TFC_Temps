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
#define YES             cout << "YES\n"
#define NO              cout << "NO\n"
#define lcm(a, b)       ((a / __gcd(a, b)) * b)

const ll MOD = 1e9 + 7;//998244353;
const ll INF = 9e18;
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

vll p(MAX);
ll dp[MAX][LOGN + 1][3];
ll pref[MAX][LOGN + 1][3];
vll a(MAX);
ll n;
vvll g(MAX);

void dfs(int node, int par)
{
    p[node] = par;
    for (auto ch: g[node])
    {
        if (par == ch)
        {
            continue;
        }

        dfs(ch, node);
    }
}

void func1(int node, int par)
{
    for (auto ch: g[node])
    {
        func1(ch, node);
    }

    FOR(i, 1, LOGN + 1)
    {
        pref[node][i][0] = a[node];
        pref[node][i][1] = a[node];
        pref[node][i][2] = a[node];
    }

    if (g[node].empty()) return;

    FOR(d, 2, LOGN + 1)
    {
        pref[node][d][0] = pref[g[node][0]][d - 1][2] + a[node];
        pref[node][d][1] = pref[g[node][1]][d - 1][2] + a[node];
        pref[node][d][2] = pref[g[node][0]][d - 1][2] + pref[g[node][1]][d - 1][2] + a[node];
    }
}

void solve()
{
    cin >> n;

    FOR(i, 1, n + 1) cin >> a[i];

    FOR(i, 1, n)
    {
        ll u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0);

    FOR(i, 2, n + 1)
    {
        for (int j = 0; j < g[i].size(); j++)
        {
            ll ch = g[i][j];
            if (ch == p[i]) g[i].erase(g[i].begin() + j);
        }
    }

    func1(1, 0);

    FOR(u, 1, n + 1)
    {
        FOR(d, 1, LOGN + 1)
        {
            dp[u][d][0] = dp[u][d - 1][0] + pref[u][d][0];
            dp[u][d][1] = dp[u][d - 1][1] + pref[u][d][1];
            dp[u][d][2] = dp[u][d - 1][2] + pref[u][d][2];
        }
    }

    ll q;
    cin >> q;

    while (q--)
    {
        ll u, t;
        cin >> u >> t;

        ll cur = p[u];
        ll prev = u;

        ll time = t;
        ll tt = min((ll)LOGN, time);
        ll ex = 0;
        if (time > LOGN) ex = time - LOGN;

        ll ans = dp[u][tt][2] + ex * pref[u][LOGN][2];
        time--;

        while (cur != 0 && time != 0)
        {
            tt = min((ll)LOGN, time);
            if (prev == g[cur][0])
            {
                ex = 0;

                if (time > LOGN) ex = time - LOGN;

                ans += dp[cur][tt][1] + ex * pref[cur][LOGN][1];
            }

            else 
            {
                
                ex = 0;

                if (time > LOGN) ex = time - LOGN;

                ans += dp[cur][tt][0] + ex * pref[cur][LOGN][0];
            }

            prev = cur;
            cur = p[cur];
            time--;
        }

        cout << ans << endl;
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