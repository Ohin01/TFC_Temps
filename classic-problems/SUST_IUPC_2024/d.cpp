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
    ll n;
    cin >> n;

    vpll pnts(n);
    map<ll, ll> cnt;

    FOR(i, 0, n)
    {
        ll x, y;
        cin >> x >> y;

        pnts[i] = {x, y};
        cnt[x]++;
    }

    vll all;

    for (auto &p: cnt)
    {
        all.pb(p.ss);
    }

    ll ans = 0;

    FOR(i, 0, all.size() - 1)
    {
        ll x = all[i];
        ll y = all[i + 1];

        if (x == y) ans += (2 * x - 1);
        else if (x < y)
        {
            ans += (2 * x - 1);
            ans += (y - x);
        }
        else 
        {
            ans += (2 * y - 1);
            ans += (x - y);
        }
    }

    cout << ans << endl;
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
        //cout << "Case " << i << ": ";
        solve();
    }
}