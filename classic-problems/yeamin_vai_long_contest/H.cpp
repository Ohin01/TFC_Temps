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
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    template<typename T, typename U>
    size_t operator()(const pair<T, U>& x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();

        uint64_t h1 = splitmix64((uint64_t)x.first + FIXED_RANDOM);
        uint64_t h2 = splitmix64((uint64_t)x.second + FIXED_RANDOM);

        return h1 ^ (h2 >> 1);
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
const int MAX = 2e5 + 5;
const int MX = 1e6 + 5;
const int LOGN = 20;
const ld PI = acos((ld) -1);

int nxt[MAX];
int state[MAX];
vi color(MAX, -1);
int id = 1;

void dfs(int node)
{
    state[node] = 1;

    int v = nxt[node];

    if (state[v] == 0)
    {
        dfs(v);
    }

    else if (state[v] == 1)
    {
        int start = v;
        int cur = start;

        do {
            color[cur] = id;
            cur = nxt[cur];
        } while (cur != start);

        id++;
    }

    state[node] = 2;
}

void solve()
{
    ll n;
    cin >> n;

    vll a(n + 1), p(n + 1);
    
    FOR(i, 1, n + 1) cin >> p[i];
    FOR(i, 1, n + 1) cin >> a[i];

    vvi rev(n + 1);

    FOR(i, 1, n + 1)
    {
        nxt[p[i]] = i;
    }

    FOR(i, 1, n + 1)
    {
        if (state[i] == 0) dfs(i);
    }

    //FOR(i, 1, n + 1) cout << nxt[i] << " "; cout << endl;
    //FOR(i, 1, n + 1) cout << color[i] << " "; cout << endl;

    ll req = color[1];
    ll mn = INF;
    ll cur = -1;

    FOR(i, 1, n + 1) 
    {
        if (color[i] == req && a[i] < mn)
        {
            mn = a[i];
            cur = i;
        };
    }

    ll times = 0;

    while (cur != 1)
    {
        times++;
        cur = nxt[cur];
    }

    set<int> s;
    FOR(i, 1, n + 1) s.insert(color[i]);
    ll sz = s.size();

    vvi comp(sz + 1);
    vvi val(sz + 1);

    vb hoise(sz + 1);

    FOR(i, 1, n + 1)
    {
        if (hoise[color[i]]) continue;
        hoise[color[i]] = true;

        ll st = i;
        ll achi = i;
        
        do{
            val[color[i]].pb(a[achi]);
            comp[color[i]].pb(achi);
            achi = nxt[achi];
        } while(st != achi);
    }

    // FOR(i, 1, sz + 1)
    // {
    //     FOR(j, 0, val[i].size())
    //     {
    //         cout << val[i][j] << " ";
    //     }
    //     cout << endl;
    //     FOR(j, 0, val[i].size())
    //     {
    //         cout << comp[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << times << endl;
    //cout << val[1].size() << endl;

    vb vis(sz + 1);
    vll ans(n + 1);

    FOR(i, 1, n + 1)
    {
        if (vis[color[i]]) continue;

        vis[color[i]] = true;

        int achi = i;

        FOR(j, 0, times) achi = nxt[achi];

        FOR(j, 0, val[color[i]].size())
        {
            //cout << achi << endl;
            ans[achi] = val[color[i]][j];
            achi = nxt[achi];
        }

        //FOR(i, 1, n + 1) cout << ans[i] << " "; cout << endl;
    }

    FOR(i, 1, n + 1) cout << ans[i] << " "; cout << endl;

    //cout << times << endl;

}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int cases = 1;
    //cin >> cases;

    for (int i = 1; i <= cases; i++)
    {
        //cout << "Case " << i << ": ";
        solve();
    }
}