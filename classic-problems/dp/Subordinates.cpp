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

vvi graph(MAX);
vll sum(MAX);
ll n;

void dfs(ll node, ll par)
{
    sum[node] = 1;

    for (auto child: graph[node])
    {
        if (child == par) continue;

        dfs(child, node);

        sum[node] += sum[child];
    }
}

void solve()
{
    cin >> n;

    FOR(i, 2, n + 1)
    {
        ll num;
        cin >> num;

        //graph[i].pb(num);
        graph[num].pb(i);
    }

    dfs(1, 0);

    //YES;

    //func(1, 0);

    FOR(i, 1, n + 1) cout << sum[i] - 1 << " ";
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