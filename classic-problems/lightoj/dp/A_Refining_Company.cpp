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
vvll prefura(502, vll(502)), prefrad(502, vll(502));
ll dp[502][502];
ll ura[501][501];
ll rad[501][501];


ll box(int x1, int y1, int x2, int y2, vvll &pref)
{
    if (x2 == 0 || y2 == 0) return 0;
    if (x2 < x1 || y2 < y1) return 0;
    return pref[x2][y2] - pref[x2][y1 - 1] - pref[x1 - 1][y2] + pref[x1 - 1][y1 - 1];
}

// ll func(ll ind, ll prev)
// {
//     if (ind > n) return 0;
//     if (dp[ind][prev] != -1) return dp[ind][prev];

//     ll ans = 0;

//     FOR(i, prev, m + 1)
//     {
//         ans = max(ans, func(ind + 1, i) + box(ind, 1, ind, i, prefura) + box(ind, i + 1, ind, m, prefrad));
//     }

//     return dp[ind][prev] = ans;
// }

void solve()
{
    //memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    FOR(i, 0, n + 1)
    {
        FOR(j, 0, m + 1) prefrad[i][j] = prefura[i][j] = dp[i][j] = 0;
    }

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1) cin >> ura[i][j];
    }

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1) cin >> rad[i][j];
    }

    //ll ans = 0;

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            prefura[i][j] = prefura[i][j - 1] + ura[i][j];
            prefrad[i][j] = prefrad[i][j - 1] + rad[i][j];
        }
    }

    FOR(j, 1, m + 1)
    {
        FOR(i, 1, n + 1)
        {
            prefura[i][j] += prefura[i - 1][j];
            prefrad[i][j] += prefrad[i - 1][j];

            //cout << prefrad[i][j] << " ";
        }
        //cout << endl;
    }

    // FOR(i, 1, n + 1)
    // {
    //     FOR(j, 1, m + 1) cout << prefura[i][j] << " ";
    //     cout << endl;
    // }
    FORR(j, m, 0) dp[n][j] = box(n, 1, n, j, prefura) + box(n, j + 1, n, m, prefrad);

    FORR(i, n - 1, 1)
    {
        vll suf(m + 1);
        suf[m] = dp[i + 1][m];

        FORR(j, m - 1, 0)
        {
            suf[j] = max(suf[j + 1], dp[i + 1][j]); 
        }

        FORR(j, m, 0)
        {
            dp[i][j] = box(i, 1, i, j, prefura) + box(i, j + 1, i, m, prefrad) + suf[j];
        }
    }

    ll ans = 0;

    FORR(j, m, 0) ans = max(ans, dp[1][j]);

    cout << ans << endl;
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