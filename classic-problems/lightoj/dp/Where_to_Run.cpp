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
vector<vpll> g(15);

ll func(ll node, ll mask, vvll &cnt)
{
    //cout << node << " " << mask << endl;
    if ((mask ^ (1<<node)) == 0) return 1;
    if (cnt[node][mask] != -1) return cnt[node][mask];

    ll ans = 0;

    for (auto &ch: g[node])
    {
        int child = ch.ff;
        //cout << node << " " << child << endl;
        if ((mask & (1<<child)) != 0)
        {
            if (func(child, mask ^ (1<<node), cnt) > 0) ans++;
        }
    }
    
    return cnt[node][mask] = ans;
}

double calc(ll node, ll mask, vector<vector<double>> &dp, vvll &cnt)
{
    if ((mask ^ (1<<node)) == 0) return 0;
    if (dp[node][mask] >= 0) return dp[node][mask]; 

    ll ej = func(node, mask, cnt);

    if (ej == 0) return dp[node][mask] = 0;

    double right = 5.0;

    for (auto &ch: g[node])
    {
        ll child = ch.ff;
        ll wt = ch.ss;

        if ((mask & (1<<child)) != 0)
        {
            if (func(child, mask ^ (1<<node), cnt) > 0)
            {
                right += wt + calc(child, mask ^ (1<<node), dp, cnt);
            }
        }
    }

    //cout << node << " " << mask << " " << right << " " << right / ((ej) * 1.0) << endl;

    return dp[node][mask] = right / ((ej) * 1.0);
}

void solve()
{
    cin >> n >> m;

    FOR(i, 0, n) g[i].clear();

    FOR(i, 0, m)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        g[u].pb({v, w});
        g[v].pb({u, w});
    }

    vvll cnt(n, vll((1<<n), -1));
    vector<vector<double>> dp(n, vector<double>((1<<n), -1));

    FOR(i, 0, n)
    {
        FOR(mask, 0, (1<<n))
        {
            if (cnt[i][mask] == -1)
            {
                cnt[i][mask] = func(i, mask, cnt);
            }
        }
    }

    //cout << calc(3, 24, dp, cnt) << endl;

    cout << fixed << setprecision(6) << calc(0, (1<<n) - 1, dp, cnt) << endl;

    //cout << func(1, 29, cnt) << endl;

    
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