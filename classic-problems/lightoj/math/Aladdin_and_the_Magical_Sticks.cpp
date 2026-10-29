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

ll ta, tb;
//double dp[5001][5001];
int same[5005], diff[5005];
double avg;
double dp[2][5001];

// double func(ll a, ll b)
// {
//     if (dp[a][b] >= 0) return dp[a][b];
//     if (a == 0 && b == 0) return 0;

//     double rhs = 0;

//     if (a >= 1) rhs += (double) a / ((ta + b) * 1.0) * (same[a] + func(a - 1, b));
//     if (b >= 1) rhs += (double) b / ((ta + b) * 1.0) * (diff[b] + func(a, b - 1));

//     //if (a == ta) return dp[a][b] = rhs;
    
//     rhs += (double) (ta - a) / ((ta + b) * 1.0) * avg;

//     double lhs = (double) (1.0 - (ta - a) / ((ta + b) * 1.0));
    
//     //cout << " " << a << " " << b << " " << lhs << " " << rhs << endl;

//     return dp[a][b] = rhs / lhs;
// }

void solve()
{
    ll n;
    cin >> n;

    FOR(i, 0, n + 1)
    {
        same[i] = diff[i] = 0;
    }

    ll x = 1, y = 1;

    FOR(i, 1, n + 1)
    {
        ll w, t;
        cin >> w >> t;

        if (t == 2)
        {
            same[x] = w;
            x++;
        }

        else
        {
            diff[y] = w;
            y++;
        }
    }

    ta = x - 1;
    tb = y - 1;

    vll suf(ta + 10);
    FORR(i, ta, 1) suf[i] = suf[i + 1] + same[i];
    
    if (ta >= 1)
    avg = (double) suf[1] / ((ta - 1 + 1) * 1.0);

    else 
    avg = 0;

    FOR(i, 0, 2)
        FOR(j, 0, tb + 1)
            dp[i][j] = 0;

    FOR(a, 0, ta + 1)
    {
        int cur = a & 1;
        int prev = cur ^ 1;

        FOR(b, 0, tb + 1)
        {
            if (a == 0 && b == 0) continue;;

            double rhs = 0;

            if (a >= 1) rhs += (double) a / ((ta + b) * 1.0) * (same[a] + dp[prev][b]);
            if (b >= 1) rhs += (double) b / ((ta + b) * 1.0) * (diff[b] + dp[cur][b - 1]);
            
            rhs += (double) (ta - a) / ((ta + b) * 1.0) * avg;

            double lhs = (double) (1.0 - (ta - a) / ((ta + b) * 1.0));
            
            //cout << " " << a << " " << b << " " << lhs << " " << rhs << endl;

            dp[cur][b] = rhs / lhs;
        }
    }

    // cout << fixed << setprecision(6) << func(ta, tb) << endl;
    cout << fixed << setprecision(6) << dp[ta & 1][tb] << endl;
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