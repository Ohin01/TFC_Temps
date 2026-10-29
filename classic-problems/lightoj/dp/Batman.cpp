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

void solve()
{
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    ll n, m, p;
    n = s1.size(); m = s2.size(); p = s3.size();

    s1 = "#" + s1;
    s2 = "!" + s2;
    s3 = "*" + s3;
 
    vector<vvll> dp(n + 1, vvll(m + 1, vll(p + 1, 0)));
 
    FOR(i, 1, n + 1)
    {
        FOR(j, 1, m + 1)
        {
            FOR(k, 1, p + 1)
            {
                if (s1[i] == s2[j] && s2[j] == s3[k])
                {
                    dp[i][j][k] = 1 + dp[i - 1][j - 1][k - 1];
                }

                else
                {
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                }
            }
        }
    }
 
    cout << dp[n][m][p] << endl;
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