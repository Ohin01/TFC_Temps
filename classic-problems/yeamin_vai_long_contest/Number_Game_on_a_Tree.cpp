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
}hsh;

typedef long long       ll;
typedef long double     ld;
typedef vector<ll>     vi;
typedef vector<vi>      vvi;
typedef vector<ll>      vll;
typedef vector<vll>     vvll;
typedef vector<bool>    vb;
typedef vector<vb>      vvb;
typedef pair<ll, ll>  pi;
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
const ll MAX = 2e5 + 5;
const ll MX = 1e6 + 5;
const ll LOGN = 20;
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
    for (ll i = 1; i < MX; i++) fact[i] = (i * fact[i - 1]) % MOD;
    inv[MX - 1] = Bigmod(fact[MX - 1], MOD - 2LL, MOD);
    for (ll i = MX - 2; i >= 0; i--) inv[i] = (inv[i + 1] * (i + 1LL)) % MOD;
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

const ll MAXN = 5e5 + 5;

vector<pll> adj[MAXN];
map<ll, ll> all;
ll ans = 0;
ll h[MAXN];

void dfs(ll node, ll par)
{
    for (auto pr: adj[node])
    {
        ll ch = pr.ff;
        ll wt = pr.ss;

        if (ch == par) continue;

        h[ch] = h[node] ^ wt;
        all[h[ch]]++;

        dfs(ch, node);
    }
}

void solve()
{
    ll n;
    cin >> n;

    FOR(i, 0, n + 1)
    {
        adj[i].clear();
        h[i] = 0;
        ans = 0;
    }

    FOR(i, 0, n - 1)
    {
        ll u, v, w;
        cin >> u >> v >> w;

        w = hsh(w);

        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }

    all.clear();
    dfs(1, 0);
    all[0]++;

    //FOR(i, 1, n + 1) cout << h[i] << " "; cout << endl;

    for (auto pr: all)
    {
        //cout << pr.ff << " " << pr.ss << endl;
        ans += (pr.ss - 1) * (pr.ss) / 2;
    }

    cout << n * (n - 1) / 2 - ans << endl;


}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll cases = 1;
    cin >> cases;

    for (ll i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}