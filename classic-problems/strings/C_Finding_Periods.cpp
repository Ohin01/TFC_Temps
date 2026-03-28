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


vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
        z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        ++z[i];
    if (i + z[i] - 1 > r)
        l = i, r = i + z[i] - 1;
    }
    return z;
}

void solve()
{
    string s;
    cin >> s;

    vi z = z_function(s);

    vll ans;

    FOR(i, 1, s.size())
    {
        bool pu = true;

        if (i + i > s.size() - 1)
        {
            if (z[i] == s.size() - i) ans.pb(i);
            continue;
        }

        if (z[i] < i) continue;

        for (int j = i; j < s.size(); j += i)
        {
            if (z[j] >= i) continue;

            else
            {
                if (j + i > s.size() - 1)
                {
                    if (z[j] == s.size() - j) continue;
                    pu = false;
                }

                pu = false;
            }
        }

        if (pu) ans.pb(i);
    }

    ans.pb(s.size());

    FOR(i, 0, ans.size()) cout << ans[i] << " ";
    cout << endl;
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