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

int nC2(ll n)
{
    return n * (n - 1) / 2;
}

double dp[1001][1001];

double func(int t, int d)
{
    if (dp[t][d] >= 0) return dp[t][d];
    if (t == 0) return 1.0; 
    if (t % 2 == 1) return 0.0;

    int tot = t + d + 1;
    double lhs = 1.0;
    double rhs = (double) nC2(t) / nC2(tot) * func(t - 2, d);
    
    if (t >= 1 && d >= 1) rhs += (double) (t * d) / nC2(tot) * func(t, d - 1);
    if (d >= 2) lhs = 1.0 - (double) nC2(d) / nC2(tot);
    //if (d >= 1) rhs += (double) (d) / nC2(tot) * max(func(t, d), func(t, d - 1));

    double rhs2 = rhs, lhs2 = lhs;
    if (d >= 1) rhs += (double) (d) / nC2(tot) * func(t, d - 1);
    if (d >= 1) lhs2 = lhs - (double) (d) / nC2(tot);

    return dp[t][d] = max(rhs / lhs, rhs2 / lhs2);
}

void solve()
{
    ll t, d;
    cin >> t >> d;

    cout << fixed << setprecision(6) << func(t, d) << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    FOR(i, 0, 1001)
        FOR(j, 0, 1001)
            dp[i][j] = -1;

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}