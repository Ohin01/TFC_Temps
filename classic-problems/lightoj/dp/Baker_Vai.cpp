#include<bits/stdc++.h>
using namespace std;

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

vpll mv = {{0, 1}, {1, 0}};

ll grid[105][105];
ll dp[101][101][101];
ll n, m;

bool valid(int x, int y)
{
    if (x < 1 || x > n) return false;
    if (y < 1 || y > m) return false;
    return true;
}

ll func(int r1, int c1, int r2)
{
    int c2 = r1 + c1 - r2;

    if (r1 == n && c1 == m) return grid[n][m];
    if (r1 == r2 && c1 == c2)
    {
        if (r1 == 1 && c1 == 1);
        else return 0;
    }

    if (dp[r1][c1][r2] != -1) return dp[r1][c1][r2];

    ll ans  = 0;
    
    for (auto p1: mv)
    {
        int nr1 = r1 + p1.ff;
        int nc1 = c1 + p1.ss;

        for (auto p2: mv)
        {
            int nr2 = r2 + p2.ff;
            int nc2 = c2 + p2.ss;

            if (valid(nr1, nc1) && valid(nr2, nc2))
            {
                ans = max(ans, grid[r1][c1] + grid[r2][c2] + func(nr1, nc1, nr2));
            }
        }
    }

    return dp[r1][c1][r2] = ans;
}

void solve()
{
    memset(grid, -1, sizeof(grid));
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1) cin >> grid[i][j];
    }

    cout << func(1, 1, 1) - grid[1][1] << endl;;   
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