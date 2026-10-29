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
const int MX = 1e3 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

vector<ll> spf(MX);

void sieve()
{
    for (int i = 0; i < MX; i++) spf[i] = i;

    for (int i = 2; i * i < MX; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MX; j += i) {
                if (spf[j]== j)
                    spf[j] = i;
            }
        }
    }
}

vll primes;

void fill()
{
    primes.pb(1);
    FOR(i, 2, MX)
    {
        if (spf[i] == i) primes.pb(i);
    }
}


void solve()
{
    ll n;
    cin >> n;

    vvll ans(n + 1, vll(n + 1));

    // if (n == 3)
    // {
    //     cout << "4 5 4 " << endl;
    //     cout << "5 5 5 " << endl;
    //     cout << "4 5 4 " << endl;
    //     return;
    // }

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    ll cells = n * n;
    ll val;
    ll cnt = 0;

    FORR(i, n, 1)
    {
        if (cnt == 0)
        {
            auto it = lower_bound(primes.begin(), primes.end(), cells);
            if (it == primes.end() || (*it) > cells)
            {
                it--;
            }
            val = (*it);
            cnt = val;
        }
        
        FOR(r, 1, i + 1)
        {
            ans[r][i] = val;
            cnt--;
            cells--;

            if (cnt == 0)
            {
                auto it = lower_bound(primes.begin(), primes.end(), cells);
                if (it == primes.end() || (*it) > cells)
                {
                    it--;
                }
                val = (*it);
                cnt = val;
            }
        }

        FOR(c, 1, i)
        {
            ans[i][c] = val;
            cnt--;
            cells--;

            if (cnt == 0)
            {
                auto it = lower_bound(primes.begin(), primes.end(), cells);
                if (it == primes.end() || (*it) > cells)
                {
                    it--;
                }
                val = (*it);
                cnt = val;
            }
        }
    }

    if (ans[2][1] == 2)
    {
        ll ind = n;
        if (n % 2 == 0) ind--;
        swap(ans[2][1], ans[ind][ind]);
    }

    FOR(i, 1, n + 1)
    {
        FOR(j, 1, n + 1)
        {
            if (j == n) cout << ans[i][j]; 
            else cout << ans[i][j] << " ";
        }
        if (i != n) cout << endl;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    sieve();
    fill();

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}