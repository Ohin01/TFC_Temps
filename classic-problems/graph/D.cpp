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

vll curcomp;
vll cyccomp;

void dfs(ll node, vvll&graph, vb &vis)
{
    vis[node] = true;

    curcomp.pb(node);

    for (auto child: graph[node])
    {
        if (vis[child])
        {
            FOR(i, 0, curcomp.size())
            {
                if (curcomp[i] == child)
                {
                    FOR(j, i, curcomp.size())
                    {
                        cyccomp.pb(curcomp[j]);
                    }
                }
            }

            return;
        }

        dfs(child, graph, vis);
    }
}

void solve()
{
    ll n, k;
    cin >> n >>k ;

    vvll graph(n + 1);
    vvll inv(n + 1);
    ll a[n + 1];

    FOR(i, 1, n + 1)
    {
        ll num;
        cin >> num;

        a[i] = num;

        graph[i].pb(num);
        inv[num].pb(i);
    }

    if (k == 1)
    {
        FOR(i, 1, n + 1)
        {
            if (a[i] != i)
            {
                NO;
                return;
            }
        }
        YES;
        return;
    }

    FOR(i, 1, n + 1)
    {
        if (a[i] == i)
        {
            NO;
            return;
        }
    }


    vvll allcomp;

    vb vis(n + 1, false);

    FOR(i, 1, n + 1)
    {
        if (vis[i])
        continue;

        dfs(i, graph, vis);

        if (!cyccomp.empty())
        allcomp.pb(cyccomp);

        curcomp.clear();
        cyccomp.clear();
    }

    queue<ll> q;
    vb incycle(n + 1, false);

    FOR(i, 0, allcomp.size())
    {
        if (allcomp[i].size() != k)
        {
            NO;
            return;
        }
        
        FOR(j, 0, allcomp[i].size())
        {
            //cout << allcomp[i][j] << " ";
            q.push(allcomp[i][j]);
            incycle[allcomp[i][j]] = true;
        }
        //cout << endl;
    }

    vll level(n + 1);

    while (!q.empty())
    {
        ll node = q.front();
        q.pop();

        incycle[node] = true;

        for (auto child: inv[node])
        {
            if (incycle[child])
            continue;

            level[child] = level[node] + 1;
            q.push(child);
        }
    }

    FOR(i, 1, n + 1)
    {
        if (!incycle[i])
        {
            NO;
            return;
        }
    }

    YES;
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    cin >> cases;

    while (cases--)
    {
        solve();
    }
}