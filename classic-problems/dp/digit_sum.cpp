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

ll dp[10][10005][105][2];
string s;
ll d;
ll n;

ll func(ll dig, ll ind, ll mod, ll tight)
{
    if (ind < 0) return 0;

    if (dp[dig][ind][mod][tight] != -1) return dp[dig][ind][mod][tight];

    ll ans = 0;

    ll till = s[ind - 1] - '0';

    FOR(j, 0, till)
    {
        ans += dp[j][ind - 1][(mod - dig + d) % d][0]; 
        ans %= MOD;
    }

    ans += func(till, ind - 1, (mod - dig + d) % d, 1);
    ans %= MOD;

    return dp[dig][ind][mod][tight] = ans;
}

void solve()
{
    memset(dp, 0, sizeof(dp));
    cin >> s;
    cin >> d;

    if (s.size() == 1)
    {
        cout << (s[0] - '0') / d << endl;
        return;
    }

    n = s.size();

    reverse(s.begin(), s.end());

    FOR(i, 0, 10)
    {
        FOR(mod, 0, d)
        {
            dp[i][0][mod][1] = 0;
        }

        dp[i][0][(i) % d][0] = dp[i][0][(i) % d][1] = 1; 
    }

    FOR(i, 1, s.size())
    {
        FOR(dig, 0, 10)
        {
            FOR(mod, 0, d)
            {
                FOR(j, 0, 10)
                {
                    dp[dig][i][mod][0] += dp[j][i - 1][(mod - dig + 100 * d) % d][0]; 
                    dp[dig][i][mod][0] %= MOD;
                }

                dp[dig][i][mod][1] = -1;
            }
        }
    }
    //cout << dp[1][0][1][0] << endl;

    ll ans = 0;

    ll f = s[n - 1] - '0';

    FOR(i, 0, f)
    {

        //cout << i << " " << dp[i][n-1][0][0] << endl;
        ans += dp[i][n - 1][0][0];
        ans %= MOD;
    }

    ans += func(f, n - 1, 0, 1);
    ans %= MOD;


    cout << (ans - 1 + MOD) % MOD << endl;




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