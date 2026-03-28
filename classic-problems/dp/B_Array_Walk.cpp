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

vector<vector<int>> buildSparseTable(vector<int> &arr) {
    int n = arr.size();

    vector<vector<int>> lookup(n + 1,
                vector<int>(log2(n) + 1));

    for (int i = 0; i < n; i++)
        lookup[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; (i + (1 << j) - 1) < n; i++) {

            if (lookup[i][j - 1] < 
                lookup[i + (1 << (j - 1))][j - 1])
                lookup[i][j] = lookup[i][j - 1];
            else
                lookup[i][j] = 
                lookup[i + (1 << (j - 1))][j - 1];
        }
    }

    return lookup;
}

int query(int L, int R, vector<vector<int>> &lookup)  {
    int j = (int)log2(R - L + 1);

    if (lookup[L][j] <= lookup[R - (1 << j) + 1][j])
        return lookup[L][j];
    else
        return lookup[R - (1 << j) + 1][j];
}

void solve()
{
    ll n, k, z;
    cin >> n >> k >> z;

    vll arr(n + 1);

    FOR(i, 1, n + 1)
    cin >> arr[i];

    ll mx = -1;

    // vll mxpair(n + 1);

    // FOR(i, 1, n)
    // {
    //     if (arr[i] + arr[i + 1] > mx)
    //     mx = arr[i] + arr[i + 1];

    //     mxpair[i] = mx;
    // }

    vi allpair;

    FOR(i, 1, n)
    {
        allpair.pb(-1 * (arr[i] + arr[i + 1]));
    }

    allpair.pb(0);

    vector<vector<int>> lookup = buildSparseTable(allpair);

    //cout << query(1, 2, lookup) << endl;;

    vll pref(n + 1, 0);

    FOR(i, 1, n+ 1)
    pref[i] = pref[i - 1] + arr[i];

    ll siz = min(z, 5LL);

    vvll dp(n + 1, vll(min(z, 5LL) + 1, 0));

    FOR(i, 0, siz + 1)
    {
        FOR(j, 1, n)
        {
            ll lastind = j + k - i * 2;

            if (lastind > n)
            {
                dp[j][i] = 0;
                continue;
            }

            else if (lastind < j)
            {
                dp[j][i] = 0;
                continue;
            }

            if (i == 0)
            dp[j][i] = pref[min(n, j + k)] - pref[j - 1];

            else
            dp[j][i] = abs(query(j - 1, lastind - 1, lookup)) * i + pref[lastind] - pref[j - 1];
        }
    }

    ll ans = -1;

    FOR(i, 0, siz + 1)
    {
        FOR(j, 1, n)
        {
            //cout << dp[1][i] << " ";
            ans = max(ans, dp[1][i]);
        }
        //cout << endl;
    }

    cout << ans << endl;


}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}