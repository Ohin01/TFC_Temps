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

const int mm = 500001;// int mm = 25000005;
int dp[2][mm];

void solve2()
{
    //memset(dp, -1, sizeof(dp));
    ll n;
    cin >> n;

    int a[n + 1];

    FOR(i, 1, n + 1) cin >> a[i];

    ll tot = 0;
    FOR(i, 1, n + 1) tot += a[i];

    FOR(i, 0, 2)
    {
        FOR(j, 0, tot + 1) dp[i][j] = -1;
    }
    dp[1][0] = 0;

    FOR(i, 1, n + 1)
    {
        int cur = i & 1;
        int nxt = cur ^ 1;

        FOR(j, 0, tot + 1) dp[nxt][j] = -1;

        FOR(j, 0, tot + 1)
        {
            if (dp[cur][j] != -1)
            {
                dp[nxt][j] = max(dp[nxt][j], dp[cur][j]);

                dp[nxt][j + a[i]] = max(dp[nxt][j + a[i]], dp[cur][j] + a[i]);

                int diff = abs(j - a[i]);

                if (j >= a[i]) dp[nxt][diff] = max(dp[nxt][diff], dp[cur][j]);
                else dp[nxt][diff] = max(dp[nxt][diff], dp[cur][j] + diff);

                // if (diff <= tot)
                // dp[nxt][diff] = max(dp[nxt][diff], dp[cur][j] + a[i]); 
            }
        }

        //FOR(j, 0, tot + 1) 
    }

    int cur = (n + 1) & 1;

    if (dp[cur][0] == 0 || dp[cur][0] == -1) cout << "impossible" << endl;
    else cout << dp[cur][0] << endl;;
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