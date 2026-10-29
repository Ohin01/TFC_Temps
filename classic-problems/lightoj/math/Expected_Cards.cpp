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

double dp[14][3][14][3][14][3][14][3];
bool vis[14][3][14][3][14][3][14][3];
int A, B, C, D;

double func(int a, int ja, int b, int jb, int c, int jc, int d, int jd)
{
    if (a + ja >= A && b + jb >= B && c + jc >= C && d + jd >= D) return 0;
    if (vis[a][ja][b][jb][c][jc][d][jd] == true) return dp[a][ja][b][jb][c][jc][d][jd];
    vis[a][ja][b][jb][c][jc][d][jd] = true;

    int j = ja + jb + jc + jd;

    double tot = 54.0 - (a + b + c + d + j);

    double rhs = 0;

    if (a < 13)
    rhs += (13.0 - a) / tot * (1.0 + func(a + 1, ja, b, jb, c, jc, d, jd));

    if (b < 13)
    rhs += (13.0 - b) / tot * (1.0 + func(a, ja, b + 1, jb, c, jc, d, jd));

    if (c < 13)
    rhs += (13.0 - c) / tot * (1.0 + func(a, ja, b, jb, c + 1, jc, d, jd));

    if (d < 13)
    rhs += (13.0 - d) / tot * (1.0 + func(a, ja, b, jb, c, jc, d + 1, jd));

    if (j < 2)
    rhs += (2.0 - j) / tot * (1.0 + min({func(a, ja + 1, b, jb, c, jc, d, jd),
                                        func(a, ja, b, jb + 1, c, jc, d, jd),
                                        func(a, ja, b, jb, c, jc + 1, d, jd),
                                        func(a, ja, b, jb, c, jc, d, jd + 1)}));

    //cout << a << " " << ja << " " << b << " " << jb << " " << c << " " << jc << " " << d << " " << jd << " " << j << endl;
    
    //cout << tot << " " << rhs << endl;

    return dp[a][ja][b][jb][c][jc][d][jd] = rhs;
}

void solve()
{
    memset(vis, false, sizeof(vis));
    cin >> A >> B >> C >> D;

    int cnt = 0;
    if (A > 13) cnt += A - 13;
    if (B > 13) cnt += B - 13;
    if (C > 13) cnt += C - 13;
    if (D > 13) cnt += D - 13;

    if (cnt > 2)
    {
        cout << -1 << endl;
        return;
    }

    cout << fixed << setprecision(6) << func(0, 0, 0, 0, 0, 0, 0, 0) << endl;
    
    //cout << fixed << setprecision(6) << func(13, 0, 13, 0, 13, 0, 13, 0, 0) << endl;
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