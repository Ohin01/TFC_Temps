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

int dp[1<<16];
vpi pnts;
ll n;
int line[16][16];

int func2(int mask)
{
    if (mask == 0) return 0;
    if (dp[mask] != -1) return dp[mask];

    int fir = 0;
    FOR(i, 0, n)
    {
        if ((mask & (1<<i)) != 0)
        {
            fir = i;
            break;
        }
    }

    int ans = INT_MAX;

    ans = min(ans, 1 + func2(mask ^ (1<<fir)));

    FOR(i, fir + 1, n)
    {
        if ((mask & (1<<i)) != 0)
        {
            ans = min(ans, 1 + func2(mask & ~line[fir][i]));
        }
    }

    return ans;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    memset(line, 0, sizeof(line));
    pnts.clear();

    cin >> n;
    
    FOR(i, 0, n)
    {
        int x, y;
        cin >> x >> y;

        pnts.pb({x, y});
    }

    FOR(i, 0, n)
    {
        FOR(j, i + 1, n)
        {
            line[i][j] |= (1<<i) | (1<<j);

            int prev = i, cur = j;

            int x1 = pnts[prev].ff, x2 = pnts[cur].ff;
            int y1 = pnts[prev].ss, y2 = pnts[cur].ss;

            FOR(k, 0, n)
            {
                if (k == i || k == j) continue;

                int x3 = pnts[k].ff, y3 = pnts[k].ss;

                if ((y3 - y2) * (x2 - x1) == (y2 - y1) * (x3 - x2)) line[i][j] |= (1<<k);
            }
        }
    }

    cout << func2((1<<n) - 1) << endl;
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