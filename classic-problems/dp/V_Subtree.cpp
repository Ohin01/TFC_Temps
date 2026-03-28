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
const int MAX = 1e5 + 5;
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

long long egcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = egcd(a, m, x, y);

    if (g != 1) return -1; // inverse doesn't exist

    x = (x % m + m) % m;
    return x;
}

ll down[MAX];
ll up[MAX];
ll dp[MAX];
vvi graph(MAX);
ll n, m;

void dfs(ll node, ll par)
{
    down[node] = 1;
    vll childs;
    vll val;

    for (auto child: graph[node])
    {
        if (child == par) continue;

        dfs(child, node);

        childs.pb(child);
        val.pb((1 + down[child]) % m);

        down[node] *= (1 + down[child]);
        down[node] %= m;
    }

    ll sz = childs.size();

    if (sz == 1)
    {
        dp[childs[0]] = 1;
        return; 
    }

    if (sz == 0) return;

    vll suf(childs.size());
    vll pref(childs.size());

    suf[sz - 1] = val[sz - 1];
    pref[0] = val[0];

    FOR(i, 1, sz)
    {
        pref[i] = pref[i - 1] * val[i];
        pref[i] %= m;
    }

    FORR(i, sz - 2, 0)
    {
        suf[i] = suf[i + 1] * val[i];
        suf[i] %= m;
    }

    dp[childs[0]] = suf[1];
    dp[childs[sz - 1]] = pref[sz - 2];

    FOR(i, 1, sz - 1)
    {
        dp[childs[i]] = suf[i + 1] * pref[i - 1];
        dp[childs[i]] %= m;
    }
}

ll calc(ll node, ll par)
{
    if (up[node] != -1) return up[node];

    ll ans = (dp[node]) + 1;
    ans %= m;

    cout << node << " " << up[par] << " " << down[node] << " " << dp[node] << endl;

    ans *= down[node];
    ans %= m;

    return up[node] = ans;
}

void func(ll node, ll par)
{
    calc(node, par);

    for (auto child: graph[node])
    {
        if (child == par)
        continue;

        func(child, node);
    }
}


void solve()
{
    cin >> n >> m;

    FOR(i, 0, n - 1)
    {
        ll u, v;
        cin >> u >> v;

        graph[u].pb(v);
        graph[v].pb(u);
    }

    memset(up, -1, sizeof(up));

    dfs(1, 0);

    up[1] = down[1];

    func(1, 0);

    FOR(i, 1, n + 1)
    {
        cout << up[i] << endl;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}