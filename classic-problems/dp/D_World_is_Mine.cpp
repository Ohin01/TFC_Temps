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

ll dp[5005][5005];

ll func(int alice, int bob, vpll &all)
{
    int sz = all.size();

    if (alice >= sz || bob >= sz) return 0; 

    if (dp[alice][bob] != -1) return dp[alice][bob];

    ll ans = INF;

    //not take
    if (bob != sz - 1)
    ans = func(alice, bob + 1, all);

    //take
    if (alice == bob)
    {
        if (all[bob].ss == 1)
        {
            ans = min(ans, 1 + func(alice + 2, alice + 2, all));
        }

        else
        {
            ans = min(ans, 1 + func(alice + 1, alice + 1, all));
        }
    }

    else
    {
        alice = alice + all[bob].ss;

        if (alice < bob - 1) ans = min(ans, all[bob].ss + func(alice + 1, bob + 1, all));
    }

    

    if (alice >= bob)
    alice++;

    if (alice > sz - 1)
    return dp[alice][bob] = min(ans, all[bob].ss);

    ans = min(ans, func(alice, alice, all) + all[bob].ss);

    return dp[alice][bob] = ans;
}

void solve()
{
    ll n;
    cin >> n;

    vll a(n);

    FOR(i, 0, n) cin >> a[i];
    sort(a.begin(), a.end());

    FOR(i, 0, n + 1)
    {
        FOR(j, 0, n + 1)
        dp[i][j] = 0;
    }

    map<ll, ll> cnt;

    FOR(i, 0, n) cnt[a[i]]++;

    vpll all(cnt.begin(), cnt.end());

    vll arr;

    FOR(i, 0, all.size()) arr.pb(all[i].ss);

    ll sz = arr.size();

    // FOR(i, 0, sz) cout << arr[i] << " ";
    // cout << endl;
    
    //2 3 3 2 5 2
    FORR(i, sz - 1, 0)
    {
        FOR(j, 0, sz)
        {
            if (j > i) dp[i][j] = dp[i + 1][j];
            else
            {
                if (j >= arr[i])
                dp[i][j] = max(dp[i + 1][j + 1], 1 + dp[i + 1][j - arr[i]]);

                else
                dp[i][j] = dp[i + 1][j + 1];
            }

            //cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }

    ll ans = 0;

    FOR(i, 0, sz)
    {
        ans = max(ans, dp[0][i]);
    }

    cout << sz - ans << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}