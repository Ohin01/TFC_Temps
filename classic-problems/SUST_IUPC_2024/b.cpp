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

    ll a[n + 1][n + 1];
    FOR(i, 1, n + 1){
        FOR(j, 1, n + 1){
            a[i][j] = max(i, j) * 2 - 1;
        }
    }

    FOR(i, 1, n + 1){
        FOR(j, 1, n + 1){// cout << __gcd(a[i][j], lcm(i, j)) << " ";
            if (__gcd(a[i][j], i) != 1 || __gcd(a[i][j], j) != 1) {
                // if (i > j) {
                //     swap(a[i][j], a[i - 1][j]);
                // }
                // else swap(a[i][j], a[i][j - 1]);

                cout << i << " ";

                ll x = i, y = j;
                if (__gcd(a[i][j], lcm(i + 1, j + 1)) != 1) {
                    swap(a[x][y], a[x + 1][y + 1]);
                    x++, y++;
                }
                else {
                    swap(a[x][y], a[x - 1][y - 1]);
                    x--, y--;
                }

                // if (i > j) {
                //     while (__gcd(a[x][y], lcm(x, y)) != 1) {
                //         swap(a[x][y], a[x][y - 1]);
                //         y--;
                //     }
                // }
                // else {
                //     while (__gcd(a[x][y], lcm(x, y)) != 1) {
                //         swap(a[x][y], a[x - 1][y]);
                //         x--;
                //     }
                // }
                

                // while (__gcd(a[x][y], lcm(x, y)) != 1) {
                //     swap(a[x][y], a[x][y - 1]);
                //     y--;
                // }
            }
        }
    }

    FOR(i, 1, n + 1){
        FOR(j, 1, n + 1){
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    //for (int i = 1; i <= cases; i++)
    //{
        //cout << "Case " << i << ": ";
        solve();
    //}
}