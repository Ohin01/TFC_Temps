#include<bits/stdc++.h>
using namespace std;

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

const int MAXN = 92;
bool dp[91][(1<<10)][2];
bitset<MAXN> endds[1<<10];
bitset<MAXN> adj[91][2];

// bool dp2[91][(1<<10)];
bitset<MAXN> starts[1<<10];

void solve()
{
    int n, m, d;
    cin >> n >> m >> d;

    vector<vpi> g(91);
    vector<tuple<int, int, int>> edges;

    FOR(i, 1, m + 1)
    {
        int u, v, w;
        cin >> u >> v >> w;

        g[u].pb({v, w});
        g[v].pb({u, w});

        adj[u][w].set(v);
        adj[v][w].set(u);

        edges.pb({u, v, w});
    }

    int d1 = d / 2;
    int d2 = (d + 1) / 2;

    dp[1][0][0] = true;

    FOR(i, 1, d1 + 1)
    {
        int cur = i & 1;
        int prev = cur ^ 1;

        for (int j = 1; j <= n; j++) 
        {
            for (int mask = 0; mask < (1<<i); mask++) 
            {
                dp[j][mask][cur] = false;
            }
        }

        for (int mask = 0; mask < (1<<(i - 1)); mask++)
        {
            for (auto &ed: edges)
            {
                int u = get<0>(ed);
                int v = get<1>(ed);
                int w = get<2>(ed);

                if (dp[u][mask][prev]) dp[v][(mask << 1) | w][cur] = true;
                if (dp[v][mask][prev]) dp[u][(mask << 1) | w][cur] = true;
            }
        }
    }

    bitset<MAXN> aager, notun;

    for (int i = 1; i <= n; i++)
    {
        for (int mask = 0; mask < (1<<d2); mask++)
        {
            aager.reset();
            notun.reset();

            aager.set(i);

            for (int ind = 0; ind < d2; ind++)
            {
                int b;
                if ((mask & (1<<ind)) == 0) b = 0;
                else b = 1;

                notun.reset();

                for (int node = 1; node <= n; node++)
                {
                    if (aager[node] == 1) notun |= (adj[node][b]);
                }

                aager = notun;
            }
            
            if (!aager.none()) starts[mask].set(i);
        }
    }

    for (int mask = 0; mask < (1<<d1); mask++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (dp[i][mask][d1 & 1]) endds[mask].set(i);
        }
    }

    int ans = 0;

    for (int mask1 = 0; mask1 < (1<<d1); mask1++)
    {
        if (endds[mask1].none()) continue;

        for (int mask2 = 0; mask2 < (1<<d2); mask2++)
        {
            if ((starts[mask2] & endds[mask1]) != 0)
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
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