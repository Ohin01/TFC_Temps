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

double dp[105][105][105];

// double func(ll r, ll s, ll p)
// {
//     if (dp[r][s][p] >= 0) return dp[r][s][p];

//     ll tot = r * s + s * p + p * r;

//     dp[r][s - 1][p] = dp[r][s][p] * 
// }

void solve()
{
    // FOR(i, 0, 101)
    // {
    //     FOR(j, 0, 101)
    //     {
    //         FOR(k, 0, 101)
    //         {
    //             dp[i][j][k] = -1;
    //         }
    //     }
    // }

    ll r, s, p;
    cin >> r >> s >> p;

    dp[r][s][p] = 1.0;

    FORR(i, r, 0)
    {
        FORR(j, s, 0)
        {
            FORR(k, p, 0)
            {
                //if (i == r && j == s && k == p) continue;

                if (i + 1 <= r)
                {
                    ll tot = (i + 1) * j + j * k + k * (i + 1);

                    if (tot > 0) 
                    dp[i][j][k] += dp[i + 1][j][k] * ((double) (i + 1) * k / (1.0 * tot));
                }

                if (j + 1 <= s)
                {
                    ll tot = (i) * (j + 1) + (j + 1) * k + k * (i);

                    if (tot > 0)
                    dp[i][j][k] += dp[i][j + 1][k] * ((double) (j + 1) * i / (1.0 * tot));
                }

                if (k + 1 <= p)
                {
                    ll tot = (i) * j + j * (k + 1) + (k + 1) * (i);

                    if (tot > 0)
                    dp[i][j][k] += dp[i][j][k + 1] * ((double) (j) * (k + 1) / (1.0 * tot));
                }
            }
        }
    }

    //cout << dp[1][0][0] << endl; 

    double x = 0, y = 0, z = 0;

    FOR(i, 0, 101) 
    {
        x += dp[i][0][0];
        y += dp[0][i][0];
        z += dp[0][0][i];
    }

    cout << fixed << setprecision(9) << x << " " << y << " " << z << endl;
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