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

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

void pre() {
    fact[0] = 1;
    for (int i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (int i = MX - 2; i >= 0; i--) inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

ll n, m;
vpi pnts;
int dp[15][1<<15];
int dist[20][20][20][20];
char grid[20][20];
pi st;

bool valid(int x, int y)
{
    if (x < 0 || x >= n) return false;
    if (y < 0 || y >= m) return false;
    return true;
}

int func(int ind, int mask)
{
    int x = pnts[ind].ff;
    int y = pnts[ind].ss;

    if (mask == 0) return dist[st.ff][st.ss][x][y];
    if (dp[ind][mask] != -1) return dp[ind][mask];

    int ans = INT_MAX;

    FOR(i, 0, pnts.size())
    {
        if ((mask & (1<<i)) != 0)
        {
            ans = min(ans, dist[x][y][pnts[i].ff][pnts[i].ss] + func(i, mask ^ (1<<i)));
        }
    }

    return dp[ind][mask] = ans;
}

void solve()
{
    cin >> n >> m;
    
    memset(dp, -1, sizeof(dp));
    pnts.clear();

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            cin >> grid[i][j];

            if (grid[i][j] == 'x') st = {i, j};

            if (grid[i][j] == 'g') pnts.pb({i, j});
        }
    }

    FOR(i, 0, n)
    {
        FOR(j, 0, m)
        {
            queue<pi> q;
            q.push({i, j});
            dist[i][j][i][j] = 0;
            vvb vis(n, vb(m, false));
            vis[i][j] = true;

            while (!q.empty())
            {
                pi p = q.front();
                q.pop();

                int x = p.ff;
                int y = p.ss;

                for (auto &mvv: mv)
                {
                    int nx = x + mvv.ff;
                    int ny = y + mvv.ss;

                    if (valid(nx, ny) && !vis[nx][ny])
                    {
                        vis[nx][ny] = true;
                        dist[i][j][nx][ny] = dist[i][j][x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }
    }

    int g = pnts.size();

    if (g == 0) 
    {
        cout << 0 << endl;
        return;
    }

    int ans = INT_MAX;
    int mask = (1<<g) - 1;

    FOR(i, 0, g)
    {
        int x = pnts[i].ff;
        int y = pnts[i].ss;

        ans = min(ans, dist[st.ff][st.ss][x][y] + func(i, mask ^ (1<<i)));
    }

    cout << ans << endl;

    //cout << dist[st.ff][st.ss][2][2] << endl;


}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}