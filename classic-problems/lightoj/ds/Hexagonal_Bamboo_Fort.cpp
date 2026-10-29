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
const int MAX = 1e5 + 5;
const int MX = 100 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

vvll dp(6, vll(MAX));
ll n;

ll nC5(ll n)
{
    ll ans = 1;
    FOR(i, 0, 5)
    {
        ans *= (n - i);
    }

    FOR(i, 1, 6)
    {
        ans /= i;
    }

    return ans;
}

void solve()
{
    FOR(i, 0, 6)
    {
        FOR(j, 0, MAX) dp[i][j] = 0;
    }

    cin >> n;

    vll a(n + 1);

    FOR(i, 1, n + 1) cin >> a[i];
    sort(a.begin(), a.end());

    dp[0][0] = 1;
    ll ans = 0;

    FOR(i, 1, n)
    {
        FORR(j, MAX - 1, 0)
        {
            //cout << j << " " << a[i] << endl;
            FORR(k, 5, 1)
            {
                if (j - a[i] >= 0)
                {
                    dp[k][j] += dp[k - 1][j - a[i]];
                }
            }
        }

        if (i >= 5)
        {
            ll temp = 0;

            FOR(s, 0, a[i + 1] + 1)
            {
                temp += dp[5][s];
            }

            ans += (nC5(i) - temp); 
        }
    }

    //cout << nC5(5) << endl;

    cout << ans << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    //pre();

    for (int i = 1; i <= cases; i++)
    {
        cout << "Case " << i << ": ";
        solve();
    }
}