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

ll e[25], d[25], t[25];
ll dp[25][200];
ll n, h;

ll func(ll ind, ll left)
{
    if (ind >= n) return 0;
    if (left <= 0) return 0;
    if (dp[ind][left] != -1) return dp[ind][left];

    ll ans = func(ind + 1, left - t[ind]);

    ll tot = 0;
    ll cur = e[ind];

    FOR(i, 1, left + 1)
    {
        //if (cur == 0) break;

        tot += cur;
        cur -= d[ind];

        cur = max(0LL, cur);

        ans = max(ans, func(ind + 1, left - i - t[ind]) + tot);
    }

    return dp[ind][left] = ans;
}

vll all(25);
ll baki;

void print(ll ind, ll left)
{
    if (ind >= n) return;
    if (left <= 0) return;
    if (baki <= 0) return;

    ll mx = dp[ind][left];

    ll tot = 0;
    ll cur = e[ind];
    ll lst = 0;

    FOR(i, 1, left + 1)
    {
        //if (cur == 0) break;

        tot += cur;
        cur -= d[ind];

        cur = max(0LL, cur);

        //if (ind == 0) cout << i << " " << tot << endl;

        if (func(ind + 1, left - i - t[ind]) + tot == mx) lst = i;
    }

    //cout << "ind: " << mx << endl;

    all[ind] = lst * 5;
    baki -= lst;
    baki -= t[ind];

    print(ind + 1, left - lst - t[ind]);
}

void solve()
{
    FOR(i, 0, n) all[i] = 0;
    memset(dp, -1, sizeof(dp));
    cin >> n >> h;
    h *= 12;
    FOR(i, 0, n) cin >> e[i];
    FOR(i, 0, n) cin >> d[i];
    FOR(i, 0, n - 1) cin >> t[i];
    t[n - 1] = 0;

    ll exp = func(0, h);

    baki = h;

    // FOR(i, 0, n)
    // {
    //     FOR(j, 0, h + 1)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    print(0, h);
    
    FOR(i, 0, n - 1)
    {
        // if (i == 0)
        // {
        //     if (baki >= 0)
        //     cout << all[i] + baki * 5 << ", ";

        //     else cout << all[i] << ", ";
        // }
        // else 
        cout << all[i] << ", ";
    }
    cout << all[n - 1] << endl;

    cout << "Number of fish expected: " << exp << endl;
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
        cout << "Case " << i << ": " << endl;;
        solve();
    }
}