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

ll Bigmod(ll a, ll b, ll m){
    if(b == 0) return 1 % m;
    ll x = Bigmod(a, b / 2LL, m);
    x = (x * x) % m;
    if(b % 2 == 1) x = (x * a) % m;
    return x;
}

ll poww[12];
ll n, k;
ll dp[12][1<<12][20];
ll sz;
string s;

int value(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    else return (c - 'A') + 10;
}

int func(int ind, int mask, int mod)
{
    if (ind >= sz)
    {
        if (mod == 0) return 1;
        else return 0;
    } 
    //if (mask == 0) return 1;

    if (dp[ind][mask][mod] != -1) return dp[ind][mask][mod];

    int ans = 0;

    FOR(i, 0, sz)
    {
        if ((mask & (1<<i)) != 0)
        {
            int val = value(s[i]);
            int md = (mod + (val * poww[ind]) % k) % k;

            ans += func(ind + 1, (mask) ^ (1<<i), md);
        }
    }

    return dp[ind][mask][mod] = ans;
}

void solve()
{
    memset(dp, -1, sizeof(dp));
    cin >> n >> k;
    cin >> s;
    sz = s.size();

    FOR(i, 0, sz)
    {
        poww[i] = Bigmod(n, i, k);
    }

    int ans = 0;

    cout << func(0, (1<<sz) - 1, 0) << endl;
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