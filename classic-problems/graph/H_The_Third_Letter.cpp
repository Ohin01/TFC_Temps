#include<bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename dataType>
using ordered_set = tree<dataType, null_type, less<dataType>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType1, typename dataType2>
using ordered_map = tree<dataType1, dataType2, less<dataType1>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename dataType>
using ordered_multiset = tree<dataType, null_type, less_equal<dataType>, rb_tree_tag, tree_order_statistics_node_update>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

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
#define YES             cout << "Yes\n"
#define NO              cout << "No\n"
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

ll fact[MX];
ll inv[MX];
vpll mv = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

void pre(){
    fact[0]=1;
    inv[0]=1;
    FOR(i, 1, MX){
        fact[i] = (i * fact[i - 1])% MOD;
        inv[i] = Bigmod(fact[i], MOD - 2LL, MOD);
    }
}

ll nCr(ll n, ll r, ll p) { 
    if(r > n || r < 0) return 0;
    if(n == r || r == 0) return 1;
    return (((fact[n] * inv[r]) % p ) * inv[n - r]) % p;
}

vll par(MAX);
vll siz(MAX);
vll path(MAX);

void spawn(ll node)
{
    par[node] = node;
    siz[node] = 1;
}

ll find(ll node, ll wt)
{
    if (node == par[node])
    {
        path[node] = 0;
        return node;
    }

    else
    {
        path[node] = path[par[node]] + wt;
        //cout << node << " " << path[node] << endl;
        return par[node] = find(par[node], path[par[node]]);
    }
}

void merge(ll n1, ll n2)
{
    ll p1 = par[n1];
    ll p2 = par[n2];

    if (p1 == p2)
    return;

    if (siz[p1] <= siz[p2])
    {
        par[p1] = p2;
        siz[p2] += siz[p1];
    }

    else
    {
        par[p2] = p1;
        siz[p1] += siz[p2];
    }
}


void solve()
{
    ll n, m;
    cin >> n >> m;

    FOR(i, 1, n + 1)
    {
        par[i] = -1;
        siz[i] = 0;
        path[i] = 0;
    }
    
    ll a[m + 1], b[m + 1], d[m + 1];

    FOR(i, 1, m + 1)
    cin >> a[i] >> b[i] >> d[i];

    vb vis(n + 1, false);

    FOR(i, 1, n + 1)
    spawn(i);

    FOR(i, 1, m + 1)
    {
        if (vis[a[i]] && vis[b[i]])
        {
            if (par[a[i]] != par[b[i]])
            {
                par[b[i]] = a[i];

                find(b[i], d[i]);

                continue;
            }

            find(a[i], path[a[i]]);
            find(b[i], path[b[i]]);

            ll path1 = path[a[i]];
            ll path2 = path[b[i]];

            if (path2 - path1 != d[i])
            {
                NO;
                return;
            }           
        }

        else
        {
            //cout << i << endl;
            par[b[i]] = a[i];

            find(b[i], d[i]);

            vis[b[i]] = true;
            vis[a[i]] = true;
        }
    }

    YES;
}

void solve2()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<pll>> graph(n + 1);

    FOR(i, 0, m)
    {
        ll n1, n2, wt;
        cin >> n1 >> n2 >> wt;

        graph[n1].pb({n2, wt});
        graph[n2].pb({n1, -wt});
    }

    vll level(n + 1, 0);
    vb vis(n + 1, false);

    FOR(i, 1, n + 1)
    {
        if (vis[i])
        continue;

        queue<ll> q;
        q.push(i);

        while (!q.empty())
        {
            ll node = q.front();
            q.pop();

            vis[node] = true;

            for (auto child: graph[node])
            {
                ll ch = child.ff;
                ll wt = child.ss;

                if (vis[ch])
                {
                    if (level[node] + wt != level[ch])
                    {
                        NO;
                        return;
                    }
                }

                else
                {
                    level[ch] = level[node] + wt;
                    q.push(ch);
                }
            }
        }
    }

    // FOR(i, 1, n + 1)
    // cout << level[i] << " ";
    // cout << endl;

    YES;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
   // cin >> cases;

    while (cases--)
    {
        solve2();
    }
}