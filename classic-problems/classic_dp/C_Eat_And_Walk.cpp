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
const ll INF = 9e15;
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

void solve()
{
    ll n, k;
    cin >> n >> k;

    vll a(n + 1);

    FOR(i, 1, n + 1) cin >> a[i];

    vvll dp(2, vll(k + 10, INF));

    dp[(n + 1) & 1][0] = 0;
    
    ll ans = 0;

    FORR(i, n, 1)
    {
        ll cur = i & 1;
        ll prev = cur ^ 1;

        for (ll c = 0; c * i <= k; c++)
        {
            dp[cur][c] = dp[prev][c];
            if (c - a[i] >= 0)
            dp[cur][c] = min(dp[prev][c], dp[prev][c - a[i]] + i * a[i]);
        }

        //for (ll c = 0; c <= 10; c++) cout << c << " " << dp[cur][c] << endl; cout << endl;

        for (ll c = 0; c * i <= k; c++)
        {
            if (dp[cur][c] + 2 * i <= k)
            ans = max(ans, c);
        }
    }


    // FOR(i, 0, k + 1)
    // {
    //     if (dp[n & 1][i] + 2 * i <= k) ans = max(ans, i);
    //     //cout << dp[n & 1][i] << endl;
    // }

    cout << ans << endl;
}

void solve2()
{
    ll n, k;
    cin >> n >> k;

    vll a(n + 1);

    FOR(i, 1, n + 1) cin >> a[i];

    vll dp(k + 10, INF);

    dp[0] = 0;
    
    ll ans = 0;

    FORR(i, n, 1)
    {
        for (ll c = k / i; c >= 0; c--)
        {
            if (c - a[i] >= 0)
            dp[c] = min(dp[c], dp[c - a[i]] + i * a[i] + (c - a[i] == 0) * 2 * i);
        }

        for (ll c = 0; c * i <= k; c++)
        {
            if (dp[c] <= k)
            ans = max(ans, c);
        }
    }

    cout << ans << endl;
}

void solve3()
{
    ll n, k;
    cin >> n >> k;
 
    vll a(n + 1);
 
    FOR(i, 1, n + 1) cin >> a[i];
 
    vpll dp(k + 10, {INF, 0});
 
    dp[0] = {0, 0};
    
    ll ans = 0;
 
    FOR(i, 1, n + 1)
    {
        for (ll c = k / i; c >= 0; c--)
        {
            if (c - a[i] >= 0)
            dp[c] = min(dp[c], {dp[c - a[i]].ff + i * a[i] + 2 * i - dp[c - a[i]].ss * 2, i});
        }
 
        for (ll c = 0; c * i <= k; c++)
        {
            if (dp[c].ff <= k)
            ans = max(ans, c);
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
        solve2();
    }
}