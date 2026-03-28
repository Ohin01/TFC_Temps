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

ll downDP[MAX];
ll upDP[MAX];
ll p[MAX];

void dfs(int node, int par, vvi &g)
{
    p[node] = par;

    for (auto ch: g[node])
    {
        if (ch == par) continue;

        dfs(ch, node, g);

        downDP[node] = max(downDP[node], 1 + downDP[ch]); 
    }
}

void dfs2(int node, int par, vvi &g)
{
    vll childs;

    for (auto ch: g[node])
    {
        if (ch == par) continue;
        childs.pb(ch);
    }

    ll sz = childs.size();

    if (sz == 0) return;

    vll val(sz);

    vll suf(sz);
    vll pref(sz);

    FOR(i, 0, sz) val[i] = downDP[childs[i]] + 1;

    suf[sz - 1] = val[sz - 1];
    pref[0] = val[0];

    FOR(i, 1, sz) pref[i] = max(val[i], pref[i - 1]);
    FORR(i, sz - 2, 0) suf[i] = max(val[i], suf[i + 1]); 

    FOR(i, 0, sz)
    {
        ll mx = upDP[node];

        i == 0?  : mx = max(mx, pref[i - 1]);
        i == sz - 1? : mx = max(mx, suf[i + 1]);

        upDP[childs[i]] = max(upDP[childs[i]], 1 + mx);

        dfs2(childs[i], node, g);
    }
}


void solve()
{
    ll n;
    cin >> n;

    vvi g(n + 1);

    FOR(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;

        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(1, 0, g);
    dfs2(1, 0, g);
    
    FOR(i, 1, n + 1) cout << max(downDP[i], upDP[i]) << " ";
    cout << endl;
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