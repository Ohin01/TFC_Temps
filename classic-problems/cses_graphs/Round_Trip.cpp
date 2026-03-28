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
const int MAX = 1e5 + 5;
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

vvi graph(MAX);
vb vis(MAX);
vi par(MAX);
vi forw, back;

void dfs(int node, int p)
{
    par[node] = p;
    vis[node] = true;

    for (auto ch: graph[node])
    {
        if (ch == p) continue;
        //cout << node << " " << ch << endl;

        if (vis[ch] && forw.empty() && back.empty())
        {
            //cout << par[1] << " " << par[3] << " " << par[5] << endl;
            ll cur = node;
            while (cur != 0)
            {
                forw.pb(cur);
                cur = par[cur];
            }

            cur = ch;

            while (cur != 0)
            {
                back.pb(cur);
                cur = par[cur];
            }
            return;
        }

        else if (vis[ch]) continue;

        else
        {
            par[ch] = node;
            dfs(ch, node);
        }
    }
}

void solve()
{
    ll n, m;
    cin >> n >> m;

    FOR(i, 0, m)
    {
        ll u, v;

        cin >> u >> v;

        graph[u].pb(v);
        graph[v].pb(u);
    }

    deque<int> dq;

    FOR(i, 1, n + 1)
    {
        if (!vis[i])
        {
            dfs(i, 0);

            if (!forw.empty())
            {
                reverse(forw.begin(), forw.end());
                
                FOR(j, 0, forw.size()) dq.pb(forw[j]);
                FOR(j, 0, back.size()) dq.pb(back[j]);
                break;
            }
        }
    }

    if (dq.empty()) 
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    ll st = 0;
    ll en = dq.size() - 1;

    while (st < en)
    {
        if (dq[st + 1] != dq[en - 1])
        {
            cout << en - st + 1 << endl;
            FOR(i, st, en + 1) cout << dq[i] << " ";
            cout << endl;
            return;
        }

        st++;
        en--;
    }




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