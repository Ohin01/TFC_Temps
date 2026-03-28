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

vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

ll dp[2][(1<<19)];

vll hashh(71);
vll primes;

ll convert(ll num)
{
    if (num == 0) return 0;

    ll ans = 0;

    FOR(i, 0, primes.size())
    {
        ll cnt = 0;

        while (num % primes[i] == 0)
        {
            num /= primes[i];
            cnt++;
        }

        if (cnt % 2 == 1)
        {
            ans += (1<<hashh[primes[i]]);
        }

        if (num == 1) break;
    }

    return ans;
}

ll twopow[100005];

void solve()
{
    twopow[0] = 1;

    FOR(i, 1, 100005)
    {
        twopow[i] = twopow[i - 1] * 2;
        twopow[i] %= MOD;
    }

    ll n;
    cin >> n;

    vll count(75);

    FOR(i, 0, n)
    {
        ll num;
        cin >> num;

        count[num]++;
    }

    ll cnt = 0;

    for (int i = 2; i < 71; i++)
    {
        bool prime = true;

        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                prime = false;
                break;
            }
        }

        if (prime)
        {
            hashh[i] = cnt;
            primes.pb(i);
            cnt++;
        }
    }

    dp[0][0] = 1;

    FOR(i, 1, 71)
    {
        ll cur = i % 2;
        ll prev = cur ^ 1;

        memset(dp[cur], 0, sizeof(dp[cur]));
        ll hh = convert(i);

        FOR(mask, 0, (1<<19))
        {
            if (count[i] > 0)
            {
                dp[cur][mask ^ hh] += ((ll)dp[prev][mask] * (twopow[count[i] - 1]) % MOD);
                dp[cur][mask ^ hh] %= MOD;

                //dp[i][mask] += dp[i - 1][mask];
                dp[cur][mask] += ((ll)dp[prev][mask] * (twopow[count[i] - 1]) % MOD);
                dp[cur][mask] %= MOD;
            }

            else
            {
                dp[cur][mask] = dp[prev][mask];
            }
            
        }
    }

    //cout << dp[1][0] << endl;
 
    cout << ((ll)dp[(70%2)][0] - 1 + MOD) % MOD << endl;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    while (cases--)
    {
        solve();
    }
}