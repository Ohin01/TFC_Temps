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

// ll func(int ind, int val, int tight)
// {
//     if (ind <= 0) return 0;
//     if (dp[ind][val] != -1) return dp[ind][val];

//     int ans = 0;

//     if (val == 1) ans = 1 + func(ind - 1, 1) + func(ind - 1, 0);
//     else ans = func(ind - 1, 1) + func(ind - 1, 0);

//     return dp[ind][val] = ans;
// }

// void solve()
// {
//     memset(dp, -1, sizeof(dp));

//     ll n;
//     cin >> n;

//     ll ans = 0;
//     ll cnt = 0;

//     FORR(i, 30, 0)
//     {
//         if ((n & (1<<i)) != 0)
//         {
//             ans += func(i, 0);

//             if (i >= 1)
//             {
//                 ans += cnt * (1<<(i - 1));
//             }

//             if ((n & (1<<(i + 1))) != 0) 
//             {
//                 ans++;
//                 cnt++;
//             }
//         }

//         //cout << ans << " " << i << endl;
//     }

//     //cout << func(1, 1) << endl;

//     cout << ans << endl;
// }
pll dp[31][2][2];
ll n;

pll func2(int ind, int val, int tight)
{
    if (ind <= 0) return {0, 0};
    if (dp[ind][val][tight] != make_pair(-1LL, -1LL)) return dp[ind][val][tight];

    ll ans = 0;

    ll nxt = 0;

    if ((n & (1<<(ind - 1))) != 0) nxt = 1;
    else nxt = 0;

    if (tight == 1)
    {
        if (val == 1)
        {
            if (nxt == 1) ans = 1 + func2(ind - 1, 1, 1) + func2(ind - 1, 0, 0);
            else ans = func2(ind - 1, 0, 1);
        }
        else
        {
            if (nxt == 1) ans = func2(ind - 1, 1, 1) + func2(ind - 1, 0, 0);
            else ans = func2(ind - 1, 0, 1);
        }
    }

    else
    {
        if (val == 1) ans = 1 + func2(ind - 1, 1, 0) + func2(ind - 1, 0, 0);
        else ans = func2(ind - 1, 1, 0) + func2(ind - 1, 0, 0);
    }

    return dp[ind][val][tight] = ans;
}

void solve2()
{
    cin >> n;

    FOR(i, 0, 31)
    {
        FOR(j, 0, 2)
        {
            FOR(k, 0, 2) dp[i][j][k] = {-1, -1};
        }
    }

    cout << func2(30, 0, 1).ff << endl;
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
        solve2();
    }
}